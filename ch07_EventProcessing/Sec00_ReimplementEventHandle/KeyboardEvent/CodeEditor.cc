#include "CodeEditor.h"

#include <QtWidgets>
#include <QtGui>
#include <QtCore>

CodeEditor::CodeEditor(QWidget *parent /* = 0 */) 
#if defined(__PUBLIC_QWIDGET__)
  : QWidget(parent)
#else
  : QTextEdit(parent)
#endif
{

}

bool CodeEditor::event(QEvent *e) {
  if (e->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);
    if (keyEvent->key() == Qt::Key_Tab) {
      insertAtCurrentPosition('\t');
      return true;//表示CodeEditor已经处理了此QEvent, false则交由parent Widget处理
    }
  }
  return __super::event(e);
}

#if !defined(__QACTION_KEYBINDINGS__)
void CodeEditor::keyPressEvent(QKeyEvent *e) {
  switch (e->key())
  {
  case Qt::Key_Home:
    if (e->modifiers() & Qt::ControlModifier) {
      goToBeginningOfDocument();
    }
    else {
      goToBeginningOfLine();
    }
    break;
  default:
    __super::keyPressEvent(e);
    break;
  }
}
#else 
void CodeEditor::keyPressEvent(QKeyEvent *e) {
  __super::keyPressEvent(e);
}
#endif

void CodeEditor::goToBeginningOfDocument() {
  qDebug() << tr("%1").arg(__FUNCTION__);
}

void CodeEditor::goToBeginningOfLine() {
  qDebug() << tr("%1").arg(__FUNCTION__);
}

void CodeEditor::insertAtCurrentPosition(QChar ch) {
  qDebug() << tr("%1 ch: %2").arg(__FUNCTION__).arg(ch);
}