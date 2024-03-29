#ifndef TIMEREVENT_TICKER_H
#define TIMEREVENT_TICKER_H

#include <QtWidgets/QWidget>

class Ticker : public QWidget {
  Q_OBJECT
  Q_PROPERTY(QString text READ text WRITE setText)
 public:
  Ticker(QWidget *parent = 0);

  void setText(const QString &newText);
  QString text() const { return myText; }
  QSize sizeHint() const;
 protected:
  void paintEvent(QPaintEvent *event);
  void timerEvent(QTimerEvent *event);
  void showEvent(QShowEvent *event);
  void hideEvent(QHideEvent *event);
 private:
  QString myText;
  int offset;
  int myTimerId;
};//class Ticker

#endif