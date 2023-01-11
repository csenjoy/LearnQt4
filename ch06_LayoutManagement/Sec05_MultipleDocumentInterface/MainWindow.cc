#include "MainWindow.h"

#include <QtWidgets/QMdiArea>
#include <QtWidgets/QAction>
#include <QtWidgets/QActionGroup>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QApplication>

#include <QtWidgets>
#include <QtCore/QTimer>
#include <QtCore/QStringList>

#include "Editor.h"


MainWindow::MainWindow() {
  mdiArea = new QMdiArea;
  setCentralWidget(mdiArea);

  connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)),
    this, SLOT(updateActions()));

  createActions();
  createMenus();
  createToolBars();
  createStatusBar();

  setWindowIcon(QIcon(":/images/icon.png"));
  setWindowTitle(tr("MDI Editor"));

  //避免构造函数中耗时载入文件, loadFiles加载文件在eventLoop中，此时窗口已经显示出来
  QTimer::singleShot(0, this, SLOT(loadFiles()));
}

void MainWindow::loadFiles() {
  QStringList args = QApplication::arguments();
  args.removeFirst();
  if (!args.isEmpty()) {
    foreach(QString arg, args)
      openFile(arg);
    mdiArea->cascadeSubWindows();
  }
  else {
    newFile();
  }
  mdiArea->activateNextSubWindow();
}

void MainWindow::openFile(const QString &filename) {
  
}

void MainWindow::newFile() {
  Editor *editor = new Editor;
  editor->newFile();
  addEditor(editor);
}

void MainWindow::open() {
  Editor *editor = Editor::open(this);
  if (editor) {
    addEditor(editor);
  }
}

void MainWindow::addEditor(Editor *editor) {
  //copyAvailable是否选中任意文本
  connect(editor, SIGNAL(copyAvailable(bool)), cutAction, SLOT(setEnabled(bool)));
  connect(editor, SIGNAL(copyAvailable(bool)), copyAction, SLOT(setEnabled(bool)));

  QMdiSubWindow *subWindow = mdiArea->addSubWindow(editor);
  windowMenu->addAction(editor->windowMenuAction());
  windowActionGroup->addAction(editor->windowMenuAction());
  subWindow->show();
}

void MainWindow::save() {
  if (activeEditor()) {
    activeEditor()->save();
  }
}

Editor *MainWindow::activeEditor() {
  QMdiSubWindow *subWindow = mdiArea->activeSubWindow();
  if (subWindow) {
    return qobject_cast<Editor *>(subWindow->widget());
  }
  return nullptr;
}

void MainWindow::cut() {
  if (activeEditor()) {
    activeEditor()->cut();
  }
}

void MainWindow::updateActions() {
  bool hasEditor = (activeEditor() != 0);
  bool hasSelection = activeEditor() &&
                      activeEditor()->textCursor().hasSelection();

  saveAction->setEnabled(hasEditor);
  saveAsAction->setEnabled(hasEditor);
  cutAction->setEnabled(hasSelection);
  copyAction->setEnabled(hasSelection);
  pasteAction->setEnabled(hasEditor);
  closeAction->setEnabled(hasEditor);
  closeAllAction->setEnabled(hasEditor);
  titleAction->setEnabled(hasEditor);
  cascadeAction->setEnabled(hasEditor);
  nextAction->setEnabled(hasEditor);
  previousAction->setEnabled(hasEditor);
  separatorAction->setVisible(hasEditor);

  if (activeEditor()) {
    activeEditor()->windowMenuAction()->setChecked(true);
  }
}

void MainWindow::closeEvent(QCloseEvent *event) {
  mdiArea->closeAllSubWindows();
  if (!mdiArea->subWindowList().isEmpty()) {
    event->ignore();
  }
  else {
    event->accept();
  }
}

void MainWindow::createActions() {
  newAction = new QAction(QIcon(tr(":/images/new.png")), tr("&New"), this);
  newAction->setShortcut(tr("Ctrl+N"));
  newAction->setStatusTip(tr("New a file"));
  connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

  openAction = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
  openAction->setShortcut(tr("Ctrl+O"));
  openAction->setStatusTip(tr("Open a file"));
  connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

  saveAction = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
  saveAction->setShortcut(tr("Ctrl+S"));
  saveAction->setStatusTip(tr("Save a file"));
  connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

  saveAsAction = new QAction(tr("Save &As..."), this);
  saveAsAction->setStatusTip(tr("Save as a file"));
  exitAction = new QAction(tr("E&xit"), this);
  exitAction->setShortcut(tr("Ctrl+Q"));

  cutAction = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
  cutAction->setShortcut(tr("Ctrl+X"));
  cutAction->setStatusTip(tr("cut"));
  connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));

  copyAction = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
  copyAction->setShortcut(tr("Ctrl+C"));
  copyAction->setStatusTip(tr("copy"));
  pasteAction = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
  pasteAction->setShortcut(tr("Ctrl+V"));
  pasteAction->setStatusTip(tr("paste"));

  closeAction = new QAction(tr("Cl&ose"), this);
  closeAction->setShortcut(tr("Ctrl+W"));
  closeAction->setStatusTip(tr("close window"));
  closeAllAction = new QAction(tr("Close &All"), this);
  closeAllAction->setStatusTip(tr("close window"));
  titleAction = new QAction(tr("&Title"), this);
  titleAction->setStatusTip(tr("title window"));
  cascadeAction = new QAction(tr("&Cascade"), this);
  cascadeAction->setStatusTip(tr("Cascade window"));
  nextAction = new QAction(tr("Ne&xt"), this);
  nextAction->setShortcut(tr("Ctrl+Tab"));
  nextAction->setStatusTip(tr("Next window"));
  previousAction = new QAction(tr("Pre&vious"), this);
  previousAction->setShortcut(tr("Ctrl+Shift+Tab"));
  previousAction->setStatusTip(tr("Previous window"));

  windowActionGroup = new QActionGroup(this);

  aboutAction = new QAction(tr("&About"), this);
  aboutQtAction = new QAction(tr("About &Qt"), this);
}

void MainWindow::createMenus() {
  fileMenu = menuBar()->addMenu(tr("&File"));

  fileMenu->addAction(newAction);
  fileMenu->addAction(openAction);
  fileMenu->addAction(saveAction);
  fileMenu->addAction(saveAsAction);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAction);

  editMenu = menuBar()->addMenu(tr("&Edit"));
  editMenu->addAction(cutAction);
  editMenu->addAction(copyAction);
  editMenu->addAction(pasteAction);

  windowMenu = menuBar()->addMenu(tr("&Window"));
  windowMenu->addAction(closeAction);
  windowMenu->addAction(closeAllAction);
  windowMenu->addSeparator();
  windowMenu->addAction(titleAction);
  windowMenu->addAction(cascadeAction);
  windowMenu->addSeparator();
  windowMenu->addAction(nextAction);
  windowMenu->addAction(previousAction);
  separatorAction = windowMenu->addSeparator();

  helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(aboutQtAction);
}

void MainWindow::createToolBars() {
  fileToolBar = addToolBar(tr("&File"));
  fileToolBar->addAction(newAction);
  fileToolBar->addAction(openAction);
}

void MainWindow::createStatusBar() {
  statusLabel = new QLabel(tr("Ready"), this);
  statusBar()->addWidget(statusLabel, 1);
}