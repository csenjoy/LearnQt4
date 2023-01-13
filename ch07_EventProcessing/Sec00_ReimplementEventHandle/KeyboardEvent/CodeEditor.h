#ifndef KEYBOARDEVENT_CODEEDITOR_H
#define KEYBOARDEVENT_CODEEDITOR_H

#include <QtWidgets/QTextEdit>

#define __QACTION_KEYBINDINGS__
//#define __PUBLIC_QWIDGET__
/**
 * 1������Home Ctrl+Home������Ϣ
 * 2��ʵ��Tab indent����(TabĬ��������next the widget focus in focus chain)
 * 3��ʹ��QActionʵ��key bindings
 * ����ʹ��QTextEdit QTextEdit�޷�����QAction
 * ʹ��QTextEditʱ��__QACTION_KEYBINDINGS__����������
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
