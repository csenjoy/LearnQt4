#ifndef PAINTINGWIDGET_H
#define PAINTINGWIDGET_H

#include <QtWidgets/QWidget>

class PaintingWidget : public QWidget {
 public:
  PaintingWidget(QWidget *parent = 0);

  void paintEvent(QPaintEvent *event) override;

  QSize sizeHint() const override;
};//class PaintingWidget

#endif