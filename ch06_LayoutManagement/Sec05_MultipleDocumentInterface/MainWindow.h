#ifndef MDIEDITOR_MAINWINDOW_H
#define MDIEDITOR_MAINWINDOW_H

#include <QtWidgets/QMainWindow>

class QMdiArea;
class QLabel;
class Editor;
class QActionGroup;

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow();

  void closeEvent(QCloseEvent *event);
 private slots:
  void updateActions();
  void loadFiles();  
  void openFile(const QString &filename);
  void newFile();
  void open();
  void save();
  void cut();
 private:
  void createActions();
  void createMenus();
  void createToolBars();
  void createStatusBar();
  void addEditor(Editor *editor);
  Editor *activeEditor();

  QMdiArea *mdiArea;

  QMenu *fileMenu;
  QMenu *editMenu;
  QMenu *windowMenu;
  QMenu *helpMenu;

  QToolBar *fileToolBar;

  //File Actions
  QAction *newAction;
  QAction *openAction;
  QAction *saveAction;
  QAction *saveAsAction;
  QAction *exitAction;
  //Edit Actions
  QAction *cutAction;
  QAction *copyAction;
  QAction *pasteAction;
  //Window Actions
  QAction *closeAction;
  QAction *closeAllAction;
  QAction *titleAction;
  QAction *cascadeAction;
  QAction *nextAction;
  QAction *previousAction;
  QAction *separatorAction;
  QActionGroup *windowActionGroup;
  //Help Actions
  QAction *aboutAction;
  QAction *aboutQtAction;

  QLabel *statusLabel;
};//class MainWindow

#endif