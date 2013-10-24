/****************************************************************************
** SASM - simple IDE for NASM development
** Copyright (C) 2013 Dmitriy Manushin
** Contact: site: http://dman95.github.io/SASM/
**          e-mail: Dman1095@gmail.com
**
** This file is part of SASM.
**
** SASM is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** SASM is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with SASM.  If not, see <http://www.gnu.org/licenses/>.
**
** Этот файл — часть SASM.
**
** SASM - свободная программа: вы можете перераспространять ее и/или
** изменять ее на условиях Стандартной общественной лицензии GNU в том виде,
** в каком она была опубликована Фондом свободного программного обеспечения;
** либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
** версии.
**
** SASM распространяется в надежде, что она будет полезной,
** но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
** или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Стандартной
** общественной лицензии GNU.
**
** Вы должны были получить копию Стандартной общественной лицензии GNU
** вместе с этой программой. Если это не так, см.
** <http://www.gnu.org/licenses/>.)
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTextBrowser>
#include <QTimer>
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QTime>
#include <QPointer>
#include "tab.h"
#include "highlighter.h"
#include "debugger.h"
#include "commanddebugwindow.h"
#include "finddialog.h"
#include "ruqtextedit.h"
#include "getstartedwidget.h"
#include "ui_settings.h"
#include "debugtablewidget.h"
#include "debuganycommandwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initUi();
    void createMenus();
    void createActions();
    void createButtons();
    void writeSettings();
    void setupEditor(int i);
    bool okToContinue(int index = -1);
    void setCurrentTabName(const QString &filePath, int index = -1);
    QString pathInTemp(QString path, bool forCygwin = false);
    bool removeDirRecuresively(const QString &dirName);
    QString applicationDataPath();

private:
    //ui
    GetStartedWidget *getStartedWidget;
    QStackedWidget *mainWidget;
    QSplitter *splitter;
    RuQTextEdit *compilerOut;
    QTabWidget *tabs;

    //menus and actions
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *debugMenu;
    QMenu *buildMenu;
    QMenu *settingsMenu;
    QMenu *helpMenu;
    QAction *newAction;
    QAction *openAction;
    QAction *closeAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *saveExeAction;
    QAction *exitAction;
    QAction *findAction;
    QAction *commentAction;
    QAction *uncommentAction;
    QAction *undoAction;
    QAction *redoAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *deleteAction;
    QAction *selectAllAction;
    QAction *putTabAction;
    QAction *deleteTabAction;
    QAction *buildAction;
    QAction *runAction;
    QAction *runExeAction;
    QAction *stopAction;
    QAction *debugAction;
    QAction *debugContinueAction;
    QAction *debugNextAction;
    QAction *debugNextNiAction;
    QAction *debugExitAction;
    QAction *debugShowRegistersAction;
    QAction *debugShowMemoryAction;
    QAction *settingsAction;
    QAction *helpAction;
    QAction *aboutAction;

    //builder and debugger and all that concern to them
    QProcess *runProcess;
    CodeEditor *prevCodeEditor;
    QTimer *timer;
    Debugger *debugger;
    bool programIsBuilded;
    bool ioIncIncluded;
    QPointer<DebugTableWidget> registersWindow;
    QPointer<DebugTableWidget> memoryWindow;
    QList<RuQPlainTextEdit::Watch> watches;
    DebugAnyCommandWidget *debugAnyCommandWidget;

    //highlighters
    Highlighter *highlighter;
    Highlighter *settingsHighlighter;

    //search
    QPointer<FindDialog> findDialog;
    Qt::CaseSensitivity prevCs;

    //settings and help
    QPointer<QWidget> settingsWindow;
    Ui::SettingsWindow settingsUi;
    QString startText;
    CodeEditor *settingsStartTextEditor;
    QString saveOpenDirectory; //save and open
    QByteArray tabSplitterState;
    QPointer<QTextBrowser> help;

    //about close
    bool closeFromCloseAll;
    void closeEvent(QCloseEvent *e);


public slots:
    //actions and menus
    void newFile();
    void openFile();
    void closeFile();
    bool saveFile(int index = -1);
    bool saveAsFile(int index = -1);
    void saveExe();
    bool closeApp();
    void refreshEditMenu();
    void changeCurrentSavedState(bool changed);

    //build
    void buildProgram(bool debugMode = false);
    void runProgram();
    void runExeProgram();
    void stopProgram();
    void testStopOfProgram();
    void setProgramBuildedFlagToFalse();
    void changeCurrentTab(int index);
    void printLog(const QString & message, const QColor &color);
    void printLogWithTime(const QString & message, const QColor &color);

    //debug
    void debug();
    void debugContinue();
    void enableDebugActions();
    void disableDebugActions();
    void debugNext();
    void debugNextNi();
    void debugExit();
    void debugShowRegisters();
    void debugShowMemory();
    void debugRunCommand(QString command, bool print);
    void saveWatches(DebugTableWidget *table);
    void setShowRegistersToUnchecked();
    void setShowMemoryToUnchecked();
    void setShowMemoryToChecked(const RuQPlainTextEdit::Watch &variable);
    void showAnyCommandWidget();
    void closeAnyCommandWidget();

    //search
    void find();
    void findNext(const QString &pattern, Qt::CaseSensitivity cs, bool all, bool replace,
                  const QString &replaceText = 0);

    //settings
    void restorePrevSession(bool notNotify = false);
    void openSettings();
    void saveSettings();
    void exitSettings();
    void changeActionsState(int widgetIndex);
    void saveTabSplitterState();
    void resetAllSettings();

    //closing
    bool deleteTab(int index, bool saveFileName = false);
    void closeAllChildWindows();

    //other windows
    void openHelp();
    void openAbout();
};

#endif // MAINWINDOW_H
