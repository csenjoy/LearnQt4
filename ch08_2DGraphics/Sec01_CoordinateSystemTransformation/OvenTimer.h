#ifndef OVENTIMER_H
#define OVENTIMER_H

#include <qdatetime.h>
#include <qevent.h>
#include <qwidget.h>
#include <QtWidgets>

class OvenTimer : public QWidget {
  Q_OBJECT
 public:
  OvenTimer(QWidget *parent = 0);

  void setDuration(int secs);
  int duration() const;

  void draw(QPainter *painter);
 signals:
  void timeout();

 protected:
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);

 private:
  QDateTime finishTime;
  QTimer *updateTimer;
  QTimer *finishTimer;
};//class OvenTimer

#endif /* OVENTIMER_H */
