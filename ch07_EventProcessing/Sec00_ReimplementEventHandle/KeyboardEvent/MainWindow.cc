#include "MainWindow.h"

#include <QtWidgets>

#include "CodeEditor.h"

MainWindow::MainWindow() {
  codeEditor = new CodeEditor;
  setCentralWidget(codeEditor);

#if defined(__QACTION_KEYBINDINGS__)
  goToBeginningOfLineAction = new QAction(tr("Go to beginning of Line"), this);
  goToBeginningOfLineAction->setShortcut(tr("Home"));
  goToBeginningOfLineAction->setStatusTip(tr("Go to beginning of line"));
  connect(goToBeginningOfLineAction, SIGNAL(triggered()), codeEditor, SLOT(goToBeginningOfLine()));

  goToBeginningOfDocumentAction = new QAction(tr("Goto beginning of Document"), this);
  goToBeginningOfDocumentAction->setShortcut(tr("Ctrl+Home"));
  goToBeginningOfDocumentAction->setStatusTip(tr("Goto beginning of line"));
  connect(goToBeginningOfDocumentAction, SIGNAL(triggered()), codeEditor, SLOT(goToBeginningOfDocument()));

  auto fileMenu = menuBar()->addMenu(tr("&Go to"));
  fileMenu->addAction(goToBeginningOfLineAction);
  fileMenu->addAction(goToBeginningOfDocumentAction);
#endif
}