#ifndef EELEDITOR_H
#define EELEDITOR_H

#include <QMainWindow>
#include "model/functiondefinition.h"
#include "model/annotationdefinition.h"
#include "model/customsymbolprovider.h"

#include "model/eelcompleter.h"
#include "model/eelhighlighter.h"

#include <DockManager.h>
#include <DockAreaWidget.h>
#include <DockWidget.h>

class ProjectView;
class FindReplaceForm;
class ConsoleOutput;

QT_BEGIN_NAMESPACE
namespace Ui { class EELEditor; }
QT_END_NAMESPACE

class EELEditor : public QMainWindow
{
    Q_OBJECT

public:
    EELEditor(QWidget *parent = nullptr);
    ~EELEditor();
    void openNewScript(QString path);

signals:
    void scriptSaved(QString path);

private:
    Ui::EELEditor *ui;

    CodeEditor* codeEdit;
    FindReplaceForm* findReplaceForm;
    QWidget* codeWidget;

    ProjectView* projectView;
    CodeOutline* codeOutline;
    ConsoleOutput* consoleOutput;

    CustomSymbolProvider* symbolProvider;
    EELHighlighter* highlighter;
    EELCompleter* completer;

    ads::CDockManager* DockManager;
    ads::CDockAreaWidget* StatusDockArea;
    ads::CDockWidget* TimelineDockWidget;


    void changeSyntaxStyle(QString def);
};
#endif // EELEDITOR_H
