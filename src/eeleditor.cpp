#include "eeleditor.h"
#include "ui_eeleditor.h"

#include "widgets/findreplaceform.h"
#include "widgets/projectview.h"
#include "widgets/consoleoutput.h"

#include <QFile>
#include <QMap>
#include <QListWidgetItem>
#include <QSyntaxStyle.hpp>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QDateTime>

#include <DockAreaTitleBar.h>
#include <DockAreaTabBar.h>
#include <FloatingDockContainer.h>
#include <DockComponentsFactory.h>

using namespace ads;

EELEditor::EELEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EELEditor)
{
    QFontDatabase::addApplicationFont(":/fonts/CONSOLA.ttf");
    QFontDatabase::addApplicationFont(":/fonts/CONSOLAB.ttf");

    ui->setupUi(this);
    this->layout()->setMenuBar(ui->menuBar);

    CDockManager::setConfigFlag(CDockManager::OpaqueSplitterResize, true);
    CDockManager::setConfigFlag(CDockManager::XmlCompressionEnabled, false);
    CDockManager::setConfigFlag(CDockManager::FocusHighlighting, true);
    DockManager = new CDockManager(this);

    codeEdit = new CodeEditor(this);
    findReplaceForm = new FindReplaceForm(this);
    projectView = new ProjectView(this);
    codeOutline = new CodeOutline(this);
    consoleOutput = new ConsoleOutput(this);

    codeWidget = new QWidget(this);
    auto* codeLayout = new QVBoxLayout(codeWidget);
    codeLayout->setContentsMargins(0, 0, 0, 0);
    codeLayout->setMargin(0);
    codeLayout->addWidget(codeEdit);
    codeLayout->addWidget(findReplaceForm);

    CDockWidget* CentralDockWidget = new CDockWidget("CentralWidget");
    CentralDockWidget->setMinimumSize(0,0);
    CentralDockWidget->setWidget(codeWidget);
    auto* CentralDockArea = DockManager->setCentralWidget(CentralDockWidget);
    CentralDockWidget->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromContent);
    CentralDockArea->setAllowedAreas(DockWidgetArea::OuterDockAreas);


    CDockWidget* projectsDock = new CDockWidget("Loaded projects");
    projectsDock->setWidget(projectView);
    projectsDock->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromDockWidget);
    projectsDock->resize(250, 50);
    projectsDock->setMinimumSize(200,50);
    projectsDock->setGeometry(0,0,0,400);

    auto* leftArea = DockManager->addDockWidget(DockWidgetArea::LeftDockWidgetArea, projectsDock);
    ui->menuView->addAction(projectsDock->toggleViewAction());

    projectsDock = new CDockWidget("Code outline");
    projectsDock->setWidget(codeOutline);
    projectsDock->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromDockWidget);
    projectsDock->resize(250, 150);
    projectsDock->setMinimumSize(200,150);
    DockManager->addDockWidget(DockWidgetArea::BottomDockWidgetArea, projectsDock, leftArea);
    ui->menuView->addAction(projectsDock->toggleViewAction());

    auto* consoleDock = new CDockWidget("Console output");
    consoleDock->setWidget(consoleOutput);
    consoleDock->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromDockWidget);
    consoleDock->resize(250, 150);
    consoleDock->setMinimumSize(200,150);
    DockManager->addDockWidget(DockWidgetArea::BottomDockWidgetArea, consoleDock);
    ui->menuView->addAction(consoleDock->toggleViewAction());

    findReplaceForm->setTextEdit(codeEdit);
    findReplaceForm->hide();
    connect(findReplaceForm,&FindReplaceForm::closedPressed,[this]{
        findReplaceForm->hide();
    });

    completer = new EELCompleter();
    highlighter = new EELHighlighter();
    symbolProvider = new CustomSymbolProvider();

    symbolProvider->setLanguageSpecs(completer,highlighter);
    symbolProvider->setCodeEditorModule(codeEdit);
    symbolProvider->setCodeOutlineModule(codeOutline);
    symbolProvider->connectSignals();

    codeEdit->setCompleter(completer);
    codeEdit->setHighlighter(highlighter);

    connect(ui->actionOpen_file,&QAction::triggered,[this]{
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open EEL script"), "", tr("EEL Script (*.eel)"));
        if(fileName.isEmpty())
            return;

        projectView->addFile(fileName);
    });
    connect(ui->actionClose_filw,&QAction::triggered,[this]{
        projectView->closeCurrentFile();
    });
    connect(ui->actionSave,&QAction::triggered,[this]{
        projectView->getCurrentFile()->code = codeEdit->toPlainText();
        projectView->getCurrentFile()->save();
        emit scriptSaved(projectView->getCurrentFile()->path);
    });
    connect(projectView,&ProjectView::currentFileUpdated,[this](CodeContainer* prev, CodeContainer* code){
        if(code == nullptr)
            codeEdit->setText("//No code is loaded. Please create or open a file first.");
        else{
            if(prev != nullptr)

            codeEdit->loadCode(code);
        }
        codeEdit->setEnabled(code != nullptr);
    });

    symbolProvider->reloadSymbols();

    codeEdit->setUndoRedoEnabled(true);
    connect(ui->actionUndo,&QAction::triggered,codeEdit,&QCodeEditor::undo);
    connect(ui->actionRedo,&QAction::triggered,codeEdit,&QCodeEditor::redo);
    connect(ui->actionFind_Replace,&QAction::triggered,[this]{
        findReplaceForm->setVisible(!findReplaceForm->isVisible());
    });
    connect(ui->actionGo_to_line,&QAction::triggered,[this]{
        bool ok;
        int line = QInputDialog::getInt(this, "Go to Line...",
                             "Enter line number:", codeEdit->getCurrentLine()
                                        ,1,2147483647,1,&ok);
        if (ok && line >= 0)
            codeEdit->goToLine(line);
    });
    connect(ui->actionGo_to_init,&QAction::triggered,[this]{
        codeOutline->goToAnnotation("@init");
    });
    connect(ui->actionGo_to_sample,&QAction::triggered,[this]{
        codeOutline->goToAnnotation("@sample");
    });
    connect(ui->actionJump_to_function,&QAction::triggered,[this]{
        bool ok;
        QString name = QInputDialog::getText(this, "Jump to Function...",
                             "Enter function name:", QLineEdit::Normal, "", &ok);
        if (ok && !name.isEmpty())
            codeOutline->goToFunction(name);
    });
    connect(ui->actionEEL2_documentation, &QAction::triggered, []{
        QDesktopServices::openUrl(QUrl("https://github.com/james34602/EEL_VM"));
    });


    QFont font;
    font.setFamily("Consolas");
    font.setPointSize(10);
    codeEdit->setFont(font);

    changeSyntaxStyle(":/definitions/drakula.xml");

    // TODO remove
    openNewScript(":/definitions/demo.eel");
}

EELEditor::~EELEditor()
{
    delete ui;
}

void EELEditor::openNewScript(QString path){
    projectView->addFile(path);
}

void EELEditor::changeSyntaxStyle(QString def)
{
    // Workaround to solve stylesheet conflicts
    DockManager->setStyleSheet("");
    codeEdit->loadStyle(def);

    QString Result;
    QString FileName = ":ads/stylesheets/";
    FileName += CDockManager::testConfigFlag(CDockManager::FocusHighlighting)
        ? "focus_highlighting" : "default";
#ifdef Q_OS_LINUX
    FileName += "_linux";
#endif
    FileName += ".css";
    QFile StyleSheetFile(FileName);
    StyleSheetFile.open(QIODevice::ReadOnly);
    QTextStream StyleSheetStream(&StyleSheetFile);
    Result = StyleSheetStream.readAll();
    StyleSheetFile.close();
    DockManager->setStyleSheet(Result);
}
