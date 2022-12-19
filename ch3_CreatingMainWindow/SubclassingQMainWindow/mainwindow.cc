#include "mainwindow.h"

#include <QtGui>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>

#include "FindDialog.h"
#include "GoToCellDialog.h"
#include "SortDialog.h"
#include "spreadsheet.h"

#define __WITH_MULTIPLE_WINDOW__ 1

MainWindow::MainWindow() {
  spreadsheet = new Spreadsheet;
  setCentralWidget(spreadsheet);

  createActions();
  createMenus();
  createContextMenu();
  createToolBars();
  createStatusBar();

  readSettings();

  findDialog = nullptr;

  setWindowIcon(QIcon(tr(":/images/icon.png")));
  setCurrentFile(tr(""));
}

void MainWindow::createActions() {
  //The New action has accelerator(New), a parent(the main window)
  newAction = new QAction(tr("&New"), this);
  //an icon
  newAction->setIcon(QIcon(tr(":/images/new.png")));
  //a shortcut key
  newAction->setShortcut(QKeySequence::New);
  //a status tip
  newAction->setStatusTip(tr("Create a new spreadsheet file"));
  //connect the action`s triggered() signal to the main window`s private newFile() slot
  connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));
  
  openAction = new QAction(tr("&Open"), this);
  openAction->setIcon(QIcon(tr(":/images/open.png")));
  openAction->setShortcut(QKeySequence::Open);
  openAction->setStatusTip(tr("Open a exist spreadsheet file"));
  connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

  saveAction = new QAction(tr("&Save"), this);
  saveAction->setIcon(QIcon(tr(":/images/save.png")));
  saveAction->setShortcut(QKeySequence::Save);
  saveAction->setStatusTip(tr("Save spreadsheet file"));
  connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

  saveAsAction = new QAction(tr("Save &As"), this);
  saveAsAction->setIcon(QIcon(tr(":/images/saveAs.png")));
  saveAsAction->setShortcut(QKeySequence::Save);
  saveAsAction->setStatusTip(tr("Save spreadsheet file"));
  connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

  //recently opened files
  for (int i = 0; i < MaxRecentFiles; ++i) {
    recentFileActions[i] = new QAction(this);
    //hidden 
    recentFileActions[i]->setVisible(false);
    connect(recentFileActions[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
  }

  closeAction = new QAction(tr("E&xit"), this);
  closeAction->setShortcut(tr("Ctrl+W"));
  closeAction->setStatusTip(tr("Exit the application"));
  connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

  exitAction = new QAction(tr("E&xit"), this);
  exitAction->setShortcut(tr("Ctrl+Q"));
  exitAction->setStatusTip(tr("Exit the application"));
  connect(exitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

  cutAction = new QAction(tr("&Cut"), this);
  cutAction->setIcon(QIcon(tr(":/images/cut.png")));
  cutAction->setShortcut(tr("Ctrl+X"));
  cutAction->setStatusTip(tr("Cut"));
  connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));

  copyAction = new QAction(tr("&Copy"), this);
  copyAction->setIcon(QIcon(tr(":/images/copy.png")));
  copyAction->setShortcut(tr("Ctrl+C"));
  copyAction->setStatusTip(tr("Copy"));
  connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));

  pasteAction = new QAction(tr("&Paste"), this);
  pasteAction->setIcon(QIcon(tr(":/images/paste.png")));
  pasteAction->setShortcut(tr("Ctrl+V"));
  pasteAction->setStatusTip(tr("Paste"));
  connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));

  deleteAction = new QAction(tr("&Delete"), this);
  deleteAction->setShortcut(tr("Del"));
  deleteAction->setStatusTip(tr("Delete"));
  connect(deleteAction, SIGNAL(triggered()), this, SLOT(del()));

  findAction = new QAction(tr("&Find"), this);
  findAction->setIcon(QIcon(tr(":/images/find.png")));
  findAction->setShortcut(tr("Ctrl+F"));
  findAction->setStatusTip(tr("Find"));
  connect(findAction, SIGNAL(triggered()), this, SLOT(find()));

  goToCellAction = new QAction(tr("&Go to Cell"), this);
  goToCellAction->setIcon(QIcon(tr(":/images/gotocell.png")));
  goToCellAction->setShortcut(tr("Ctrl+G"));
  goToCellAction->setStatusTip(tr("Go to Cell"));
  connect(goToCellAction, SIGNAL(triggered()), this, SLOT(goToCell()));

  selectRowAction = new QAction(tr("&Row"), this);
  selectRowAction->setStatusTip(tr("Select the row"));
 
  selectColumnAction = new QAction(tr("&Column"), this);
  selectColumnAction->setStatusTip(tr("Select the Column"));

  selectAllAction = new QAction(tr("&All"), this);
  selectAllAction->setShortcut(QKeySequence::SelectAll);
  selectAllAction->setStatusTip(tr("Select all the cells in the spreadsheet"));
  //connect(selectAllAction, SIGNAL(triggered()), spreadsheet, SLOT(selectAll()));

  recalculateAction = new QAction(tr("&Recalculate"), this);
  recalculateAction->setShortcut(tr("F9"));
  recalculateAction->setStatusTip(tr("Recalculate"));

  sortAction = new QAction(tr("&Sort..."), this);
  sortAction->setStatusTip(tr("Sort"));
  connect(sortAction, SIGNAL(triggered()), this, SLOT(sort()));

  showGridAction = new QAction(tr("&Show Grid"), this);
  showGridAction->setCheckable(true);
  showGridAction->setStatusTip(tr("Show Grid"));
  //connect(autoRecalcAction, SIGNAL(triggered()), this, SLOT(showGrid()));
  
  autoRecalcAction = new QAction(tr("&Auto-Recalculate"), this);
  autoRecalcAction->setCheckable(true);
  autoRecalcAction->setStatusTip(tr("Auto-Recalculate"));
  //connect(autoRecalcAction, SIGNAL(triggered()), this, SLOT(recalculate()));

  aboutAction = new QAction(tr("&About"), this);
  aboutAction->setStatusTip(tr("About the application"));
  connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

  aboutQtAction = new QAction(tr("About &Qt"), this);
  aboutQtAction->setStatusTip(tr("Show the Qt library`s About box"));
  connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus() {
  //file menu
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(newAction);
  fileMenu->addAction(openAction);
  fileMenu->addAction(saveAction);
  fileMenu->addAction(saveAsAction);
  separatorAction = fileMenu->addSeparator();
  for (int i = 0; i < MaxRecentFiles; ++i) {
    fileMenu->addAction(recentFileActions[i]);
  }
  fileMenu->addSeparator();
  fileMenu->addAction(exitAction);

  //edit menu
  editMenu = menuBar()->addMenu(tr("&Edit"));
  editMenu->addAction(cutAction);
  editMenu->addAction(copyAction);
  editMenu->addAction(pasteAction);
  editMenu->addAction(deleteAction);
  //create sub menu of edit menu
  selectSubMenu = editMenu->addMenu(tr("&Select"));
  selectSubMenu->addAction(selectRowAction);
  selectSubMenu->addAction(selectColumnAction);
  selectSubMenu->addAction(selectAllAction);
  editMenu->addSeparator();
  editMenu->addAction(findAction);
  editMenu->addAction(goToCellAction);
  
  toolsMenu = menuBar()->addMenu(tr("&Tools"));
  toolsMenu->addAction(recalculateAction);
  toolsMenu->addAction(sortAction);

  optionsMenu = menuBar()->addMenu(tr("&Options"));
  optionsMenu->addAction(showGridAction);
  optionsMenu->addAction(autoRecalcAction);

  menuBar()->addSeparator();

  helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(aboutQtAction);
}

void MainWindow::createContextMenu() {
  spreadsheet->addAction(cutAction);
  spreadsheet->addAction(copyAction);
  spreadsheet->addAction(pasteAction);
  spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createToolBars() {
  fileTooBar = addToolBar(tr("&File"));
  fileTooBar->addAction(newAction);
  fileTooBar->addAction(openAction);
  fileTooBar->addAction(saveAction);

  editToolBar = addToolBar(tr("&Edit"));
  editToolBar->addAction(cutAction);
  editToolBar->addAction(copyAction);
  editToolBar->addAction(pasteAction);
  editToolBar->addSeparator();
  editToolBar->addAction(findAction);
  editToolBar->addAction(goToCellAction);
}

void MainWindow::createStatusBar() {
  locationLabel = new QLabel(tr("W999"));
  locationLabel->setAlignment(Qt::AlignHCenter);
  locationLabel->setMinimumSize(locationLabel->sizeHint());

  formulaLabel = new QLabel();
  formulaLabel->setIndent(3);

  //The status bar is created the first time statusBar() is called
  statusBar()->addWidget(locationLabel);
  statusBar()->addWidget(formulaLabel, 1);

  connect(spreadsheet, SIGNAL(currentCellChanged(int, int, int, int)),
          this, SLOT(updateStatusBar()));
  
  updateStatusBar();
}

void MainWindow::updateStatusBar() {
  locationLabel->setText(spreadsheet->currentLocation());
  formulaLabel->setText(spreadsheet->currentFormula());
}

void MainWindow::spreadsheetModified() {
  setWindowModified(true);

  updateStatusBar();
}

void MainWindow::newFile() {
  if (okToContinue()) {
#if defined(__WITH_MULTIPLE_WINDOW__)
    MainWindow *mainWin = new MainWindow;
    mainWin->show();
#endif
    spreadsheet->clear();
    setCurrentFile("");
  }
}

bool MainWindow::okToContinue() {
  if (isWindowModified()) {
    int r = QMessageBox::warning(this, tr("Spreadsheet"),
                    tr("The document has been modified.\n"
                       "Do you want to save your changeds?"),
                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (r == QMessageBox::Yes) {
      return save();
    }
    else if (r == QMessageBox::Cancel) {
      return false;
    }
  }
  return true;
}

void MainWindow::open() {
  if (okToContinue()) {
    QString fileName = QFileDialog::getOpenFileName(this,
                               tr("Open Spreadsheet"), tr("."),
                               tr("Spreadsheet files (*.sp)"));
    if (!fileName.isEmpty()) {
      loadFile(fileName);
    }
  }
}

bool MainWindow::loadFile(const QString &fileName) {
  if (!spreadsheet->readFile(fileName)) {
    statusBar()->showMessage(tr("Loading canceled"), 2000);
    return false;
  }

  setCurrentFile(fileName);
  statusBar()->showMessage(tr("File loaded"), 2000);
  return true;
}

bool MainWindow::save() {
  if (curFile.isEmpty()) {
    return saveAs();
  }
  else {
    return saveFile(curFile);
  }
}

bool MainWindow::saveFile(const QString &fileName) {
  if (!spreadsheet->writeFile(fileName)) {
    statusBar()->showMessage(tr("Saving cancled"), 2000);
    return false;
  }

  setCurrentFile(fileName);
  statusBar()->showMessage(tr("File saved"), 2000);
  return true;
}

bool MainWindow::saveAs() {
  QString fileName = QFileDialog::getSaveFileName(this, 
                             tr("Save Spreadsheet"), tr("."),
                             tr("Spreadsheet files (*.sp)"));
  if (fileName.isEmpty())
    return false;
  return saveFile(fileName);
}

void MainWindow::cut() {

}

void MainWindow::copy() {
  
}

void MainWindow::paste() {

}

void MainWindow::del() {

}

void MainWindow::closeEvent(QCloseEvent *event) {
  if (okToContinue()) {
    writeSettings();
    event->accept();
  }
  else {
    event->ignore();
  }
}

void MainWindow::setCurrentFile(const QString &fileName) {
  curFile = fileName;
  setWindowModified(false);

  QString shownName = tr("Untitled");
  if (!curFile.isEmpty()) {
    shownName = strippedName(curFile);
    recentFiles.removeAll(curFile);
    recentFiles.prepend(curFile);
    updateRecentFileActions();
  }
  setWindowTitle(tr("%1[*]-%2").arg(shownName).arg(tr("Spreadsheet")));
}

QString MainWindow::strippedName(const QString &fullFileName) {
  return QFileInfo(fullFileName).fileName();
}

void MainWindow::updateRecentFileActions() {
  QMutableStringListIterator i(recentFiles);
  while (i.hasNext()) {
    if (!QFile::exists(i.next())) {
      i.remove();
    }
  }

  for (int j = 0; j < MaxRecentFiles; ++j) {
    if (j < recentFiles.count()) {
      QString text = tr("&%1 %2")
                     .arg(j + 1)
                     .arg(strippedName(recentFiles[j]));
      recentFileActions[j]->setText(text);
      recentFileActions[j]->setData(recentFiles[j]);
      recentFileActions[j]->setVisible(true);
    }
    else {
      recentFileActions[j]->setVisible(false);
    }

  }
  separatorAction->setVisible(!recentFiles.isEmpty());
}

void MainWindow::openRecentFile() {
  if (okToContinue()) {
    QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
      loadFile(action->data().toString());
    }
  }
}

void MainWindow::find() {
  if (!findDialog) {
    findDialog = new FindDialog(this);
    connect(findDialog, SIGNAL(findNext(const QString&, Qt::CaseSensitivity)),
            spreadsheet, SLOT(findNext(const QString&, Qt::CaseSensitivity)));
    connect(findDialog, SIGNAL(findPrevious(const QString&, Qt::CaseSensitivity)),
            spreadsheet, SLOT(findPrevious(const QString &, Qt::CaseSensitivity)));
  }
  
  findDialog->show();
  findDialog->raise();
  findDialog->activateWindow();
}

void MainWindow::goToCell() {
  GoToCellDialog dialog(this);
  if (dialog.exec()) {
    QString str = dialog.lineEdit()->text().toUpper();
    spreadsheet->setCurrentCell(str.mid(1).toInt() - 1, str[0].unicode() - 'A');
  }
}

void MainWindow::sort() {
  SortDialog dialog(this);
  QTableWidgetSelectionRange range = spreadsheet->selectedRange();
  dialog.setColumnRange('A' + range.leftColumn(),
                        'A' + range.rightColumn());
  if (dialog.exec()) {
    //spreadsheet->performSort(dialog.comparisonObject());
  }
}

void MainWindow::about() {
  QMessageBox::about(this, tr("About Spreadsheet"),
    tr("<h2>Spreadsheet 1.1</h2>"
    "<p>Copyright &copy; 2008 Software Inc."
    "<p>Spreadsheet is a small application that "
    "demonstrates QAction, QMainWindow, QMenuBar, "
    "QStatusBar, QTableWidget, QToolBar, and many other "
    "Qt classes."));
}

void MainWindow::writeSettings() {
  QSettings settings("Software Inc.", "Spreadsheet");

  settings.setValue("geometry", saveGeometry());
  settings.setValue("recentFiles", recentFiles);
  settings.setValue("showGrid", showGridAction->isCheckable());
  settings.setValue("autoRecalc", autoRecalcAction->isCheckable());
}

void MainWindow::readSettings() {
  QSettings settings("Software Inc.", "Spreadsheet");

  restoreGeometry(settings.value("geometry").toByteArray());
  recentFiles = settings.value("recentFiles").toStringList();
  updateRecentFileActions();

  bool showGrid = settings.value("showGrid", true).toBool();
  showGridAction->setChecked(showGrid);

  bool autoRecalc = settings.value("autoRecalc", true).toBool();
  autoRecalcAction->setChecked(autoRecalc);
}