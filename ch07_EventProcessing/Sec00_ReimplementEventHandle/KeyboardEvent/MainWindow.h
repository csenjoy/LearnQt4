#ifndef KEYBOARDEVENT_MAINWINDOW_H
#define KEYBOARDEVENT_MAINWIDNOW_H

#include <QtWidgets/QMainWindow>

class CodeEditor;
class QAction;

class MainWindow : public QMainWindow {
 public:
  MainWindow();

 private:
  CodeEditor *codeEditor;
  QAction *goToBeginningOfLineAction;
  QAction *goToBeginningOfDocumentAction;
};//class MainWindow

#endif