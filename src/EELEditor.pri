include(../3rdparty/QCodeEditor/QCodeEditor.pri)

SOURCES += \
    $$PWD/eeleditor.cpp \
    $$PWD/main.cpp \
    $$PWD/utils/FontUtils.cpp \
    $$PWD/utils/stringutils.cpp \
    $$PWD/model/completerdelegate.cpp \
    $$PWD/model/customsymbolprovider.cpp \
    $$PWD/model/eelcompleter.cpp \
    $$PWD/model/eelhighlighter.cpp \
    $$PWD/widgets/ActionButton.cpp \
    $$PWD/widgets/EmptyView.cpp \
    $$PWD/widgets/codeeditor.cpp \
    $$PWD/widgets/codeoutline.cpp \
    $$PWD/widgets/consoleoutput.cpp \
    $$PWD/widgets/dialog/newfilewizard.cpp \
    $$PWD/widgets/findreplaceform.cpp \
    $$PWD/widgets/projectview.cpp

HEADERS += \
    $$PWD/eeleditor.h \
    $$PWD/model/abstractdefinition.h \
    $$PWD/utils/FontUtils.h \
    $$PWD/utils/stringutils.h \
    $$PWD/model/annotationdefinition.h \
    $$PWD/model/codecontainer.h \
    $$PWD/model/completerdelegate.h \
    $$PWD/model/customsymbolprovider.h \
    $$PWD/model/eelcompleter.h \
    $$PWD/model/eelhighlighter.h \
    $$PWD/model/functiondefinition.h \
    $$PWD/utils/templateextension.h \
    $$PWD/widgets/ActionButton.h \
    $$PWD/widgets/EmptyView.h \
    $$PWD/widgets/codeeditor.h \
    $$PWD/widgets/codeoutline.h \
    $$PWD/widgets/consoleoutput.h \
    $$PWD/widgets/dialog/newfilewizard.h \
    $$PWD/widgets/findreplaceform.h \
    $$PWD/widgets/projectview.h \
    $$PWD/widgets/proxystyle.h

FORMS += \
    $$PWD/eeleditor.ui \
    $$PWD/widgets/EmptyView.ui \
    $$PWD/widgets/dialog/newfilewizard.ui \
    $$PWD/widgets/findreplaceform.ui

INCLUDEPATH += $$PWD

RESOURCES += \
    $$PWD/editorresources.qrc \
    $$PWD/editorresources.qrc

SUBDIRS += \
    $$PWD/src.pro

DISTFILES += \
    $$PWD/EELEditor-Linker.pri \
    $$PWD/definitions/demo.eel \
    $$PWD/definitions/drakula.xml \
    $$PWD/definitions/eelang.xml \
    $$PWD/fonts/CONSOLA.TTF \
    $$PWD/fonts/CONSOLAB.TTF \
    $$PWD/icons/ClassFriend_16x.svg \
    $$PWD/icons/Class_16x.svg \
    $$PWD/icons/ConstantInternal_16x.svg \
    $$PWD/icons/Constant_16x.svg \
    $$PWD/icons/DelegateFriend_16x.svg \
    $$PWD/icons/Delegate_16x.svg \
    $$PWD/icons/EnumFriend_16x.svg \
    $$PWD/icons/EnumItemFriend_16x.svg \
    $$PWD/icons/EnumItemSnippet_16x.svg \
    $$PWD/icons/EnumItem_16x.svg \
    $$PWD/icons/EnumSnippet_16x.svg \
    $$PWD/icons/Enumerator_16x.svg \
    $$PWD/icons/EventInternal_16x.svg \
    $$PWD/icons/Event_16x.svg \
    $$PWD/icons/ExceptionFriend_16x.svg \
    $$PWD/icons/Exception_16x.svg \
    $$PWD/icons/FieldInternal_16x.svg \
    $$PWD/icons/FieldSnippet_16x.svg \
    $$PWD/icons/Field_16x.svg \
    $$PWD/icons/FindInFile_16x.svg \
    $$PWD/icons/FindNext_16x.svg \
    $$PWD/icons/FindPrevious_16x.svg \
    $$PWD/icons/InterfaceFriend_16x.svg \
    $$PWD/icons/InterfaceSnippet_16x.svg \
    $$PWD/icons/Interface_16x.svg \
    $$PWD/icons/MethodFriend_16x.svg \
    $$PWD/icons/MethodInstance_16x.svg \
    $$PWD/icons/MethodSnippet_16x.svg \
    $$PWD/icons/Method_16x.svg \
    $$PWD/icons/ModuleFirend_16x.svg \
    $$PWD/icons/Module_16x.svg \
    $$PWD/icons/NamespaceFriend_16x.svg \
    $$PWD/icons/NamespaceSnippet_16x.svg \
    $$PWD/icons/Namespace_16x.svg \
    $$PWD/icons/NewFile_16x.svg \
    $$PWD/icons/ObjectFriend_16x.svg \
    $$PWD/icons/Object_16x.svg \
    $$PWD/icons/OperatorFriend_16x.svg \
    $$PWD/icons/Operator_16x.svg \
    $$PWD/icons/Procedure_16x.svg \
    $$PWD/icons/Property_16x.svg \
    $$PWD/icons/Run_16x.svg \
    $$PWD/icons/StatusRunOutline_cyan_16x.svg \
    $$PWD/icons/StatusRun_16x.svg \
    $$PWD/icons/StructureFriend_16x.svg \
    $$PWD/icons/Structure_16x.svg \
    $$PWD/icons/TemplateFriend_16x.svg \
    $$PWD/icons/Template_16x.svg \
    $$PWD/icons/TypeDefinitionFriend_16x.svg \
    $$PWD/icons/TypeDefinition_16x.svg \
    $$PWD/icons/TypeFriend_16x.svg \
    $$PWD/icons/Type_16x.svg \
    $$PWD/icons/UnionFriend_16x.svg \
    $$PWD/icons/Union_16x.svg \
    $$PWD/icons/ValueTypeFriend_16x.svg \
    $$PWD/icons/ValueType_16x.svg \
    $$PWD/icons/close.svg \
    $$PWD/icons/critical.svg \
    $$PWD/icons/help.svg \
    $$PWD/icons/open_folder.svg \
    $$PWD/icons/redo.svg \
    $$PWD/icons/save.svg \
    $$PWD/icons/saveas.svg \
    $$PWD/icons/success.svg \
    $$PWD/icons/undo.svg \
    $$PWD/icons/warning.svg
