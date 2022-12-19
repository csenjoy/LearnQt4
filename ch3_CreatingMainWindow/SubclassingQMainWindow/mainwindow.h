#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

class QAction;
class QLabel;
class FindDialog;
class Spreadsheet;

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow();
 protected:
  void closeEvent(QCloseEvent * event) override;

 private slots:
  void newFile();
  void open();
  bool save();
  bool saveAs();
  void cut();
  void copy();
  void paste();
  void del();
  void find();
  void goToCell();
  void sort();
  void about();
 
  void openRecentFile();
  void updateStatusBar();
  void spreadsheetModified();
 private:
  void createActions();
  void createMenus();
  void createContextMenu();
  void createToolBars();
  void createStatusBar();
  void readSettings();
  void writeSettings();
  bool okToContinue();
  bool loadFile(const QString &fileName);
  bool saveFile(const QString &fileName);
  void setCurrentFile(const QString &fileName);
  void updateRecentFileActions();
  QString strippedName(const QString &fullFileName);

  Spreadsheet *spreadsheet;
  FindDialog *findDialog;
  QLabel *locationLabel;
  QLabel *formulaLabel;
  QStringList recentFiles;
  QString curFile;

  enum { MaxRecentFiles = 5 };
  QAction *recentFileActions[MaxRecentFiles];

  QMenu *fileMenu;
  QMenu *editMenu;
  QMenu *selectSubMenu;
  QMenu *toolsMenu;
  QMenu *optionsMenu;
  QMenu *helpMenu;

  QToolBar *fileTooBar;
  QToolBar *editToolBar;
  //file menu
  QAction *newAction;
  QAction *openAction;
  QAction *saveAction;
  QAction *saveAsAction;
  QAction *separatorAction;
  QAction *closeAction;
  QAction *exitAction;
  //edit menu
  QAction *cutAction;
  QAction *copyAction;
  QAction *pasteAction;
  QAction *deleteAction;
  //selectSubMenu sub menu of edit menu
  QAction *selectRowAction;
  QAction *selectColumnAction;
  QAction *selectAllAction;
  //end selectSubMenu
  QAction *findAction;
  QAction *goToCellAction;
  //tools menu items
  QAction *recalculateAction;
  QAction *sortAction;
  //options menu items
  QAction *showGridAction;
  QAction *autoRecalcAction;
  //help menu items
  QAction *aboutAction;
  QAction *aboutQtAction;
};//class MainWindow



#endif