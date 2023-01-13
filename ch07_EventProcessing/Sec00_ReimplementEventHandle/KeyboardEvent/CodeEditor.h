#ifndef KEYBOARDEVENT_CODEEDITOR_H
#define KEYBOARDEVENT_CODEEDITOR_H

#include <QtWidgets/QTextEdit>

#define __QACTION_KEYBINDINGS__
//#define __PUBLIC_QWIDGET__
/**
 * 1）处理Home Ctrl+Home按键消息
 * 2）实现Tab indent语意(Tab默认语意是next the widget focus in focus chain)
 * 3）使用QAction实现key bindings
 * 不能使用QTextEdit QTextEdit无法触发QAction
 * 使用QTextEdit时，__QACTION_KEYBINDINGS__功能有问题
*/

class CodeEditor 
#if defined(__PUBLIC_QWIDGET__)
  : public /*QTextEdit*/QWidget
#else 
  : public QTextEdit
#endif
{
  Q_OBJECT
 public:
  CodeEditor(QWidget *parent = 0);

  bool event(QEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;
#if defined(__QACTION_KEYBINDINGS__)
 public slots:
#endif
  void goToBeginningOfLine();
  void goToBeginningOfDocument();
 private:
  void insertAtCurrentPosition(QChar ch);
};

#endif
