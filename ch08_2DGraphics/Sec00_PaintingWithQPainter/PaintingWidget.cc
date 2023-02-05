#include "PaintingWidget.h"

#include <QtWidgets>
#include <QtGui>

PaintingWidget::PaintingWidget(QWidget *parent)
  : QWidget(parent) {

}

void PaintingWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QBrush noneBrush(Qt::NoBrush);
  QPen rectangleOutLinesPen(Qt::red, 2, Qt::SolidLine);
  painter.setRenderHint(QPainter::Antialiasing, false);
  //Draw an ellipse using DashDotLine style pen
  painter.setPen(QPen(Qt::black, 12, Qt::DashDotDotLine, Qt::RoundCap));
  painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));

  painter.drawEllipse(220, 0, 400, 240);
  painter.setBrush(noneBrush);
  painter.setPen(rectangleOutLinesPen);
  painter.drawRect(220, 0, 400, 240);
  //Draw pie
  QPen pieOutLinesPen1(Qt::black, 20, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
  QBrush pieFillBrush(Qt::blue, Qt::DiagCrossPattern);


  painter.setPen(pieOutLinesPen1);
  painter.setBrush(pieFillBrush);
  painter.drawPie(0, 0, 200, 120, 0, 60 * 16);
  painter.setPen(rectangleOutLinesPen);
  painter.setBrush(noneBrush);
  painter.drawRect(0, 0, 200, 120);
  
  painter.setRenderHint(QPainter::Antialiasing);
  QPen pieOutLinesPen2(Qt::black, 20, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);
  painter.setPen(pieOutLinesPen2);
  painter.setBrush(pieFillBrush);
  painter.drawPie(0, 120, 200, 120, 60 * 16, 60 * 16);
  painter.setPen(rectangleOutLinesPen);
  painter.setBrush(noneBrush);
  painter.drawRect(0, 120, 200, 120);

  QPen pieOutLinesPen3(Qt::black, 20, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
  painter.setPen(pieOutLinesPen3);
  painter.setBrush(pieFillBrush);
  painter.drawPie(0, 240, 200, 120, -60 * 16, 60 * 16);
  painter.setPen(rectangleOutLinesPen);
  painter.setBrush(noneBrush);
  painter.drawRect(0, 240, 200, 120);

  QPen pieOutLinesPen4(Qt::black, 20, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
  painter.setPen(pieOutLinesPen4);
  painter.setBrush(pieFillBrush);
  painter.drawPie(0, 360, 200, 120, 60 * 16, -60 * 16);
  painter.setPen(rectangleOutLinesPen);
  painter.setBrush(noneBrush);
  painter.drawRect(0, 360, 200, 120);

  QPen pieOutLinesPen5(Qt::black, 20, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin);
  painter.setPen(pieOutLinesPen5);
  painter.setBrush(pieFillBrush);
  painter.drawPie(0, 480, 200, 120, -60 * 16, -60 * 16);
  painter.setPen(rectangleOutLinesPen);
  painter.setBrush(noneBrush);
  painter.drawRect(0, 480, 200, 120);

  //Draw cubic Bezier curve
  QPainterPath path;
  path.moveTo(220, 420);
  path.cubicTo(340, 260, 460, 260, 580, 420);
  painter.setPen(QPen(Qt::black, 8));
  painter.drawPath(path);

  QPainterPath path2;
  path2.moveTo(220, 420);
  path2.cubicTo(340, 220, 460, 220, 580, 420);
  painter.setPen(QPen(Qt::green, 8));
  painter.setBrush(pieFillBrush);
  painter.drawPath(path2);

  painter.setPen(QPen(Qt::red, 8,Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  painter.drawPoint(220, 420);
  painter.drawPoint(340, 260);
  painter.drawPoint(460, 260);
  painter.drawPoint(580, 420);

  painter.drawPoint(340, 220);
  painter.drawPoint(460, 220);

  //Gradient start point[630,0]
  QLinearGradient linearGradient(630, 0, 880, 250);
  linearGradient.setColorAt(0.0, Qt::white);
  linearGradient.setColorAt(0.8, Qt::green);
  linearGradient.setColorAt(1.0, Qt::black);
  QBrush linearGradientBrush(linearGradient);
  painter.setPen(Qt::NoPen);
  painter.setBrush(linearGradientBrush);
  painter.drawRect(630, 0, 250, 250);

  QRadialGradient radialGradient(QPointF(750, 370), 120, QPointF(810, 430));
  QBrush radialBrush(radialGradient);
  radialGradient.setColorAt(0.0, Qt::white);
  radialGradient.setColorAt(0.9, Qt::green);
  radialGradient.setColorAt(1.0, Qt::black);
  painter.setPen(Qt::NoPen);
  painter.setBrush(radialGradient);
  painter.drawRect(630, 250, 250, 250);

  //颜色渐变方向为逆时针方向
  QConicalGradient conicalGradient(750, 620, 120);
  conicalGradient.setColorAt(0.0, Qt::white);
  conicalGradient.setColorAt(0.8, Qt::green);
  conicalGradient.setColorAt(1.0, Qt::black);
  painter.setPen(Qt::NoPen);
  painter.setBrush(conicalGradient);
  painter.drawRect(630, 500, 250, 250);
}

QSize PaintingWidget::sizeHint() const {
  return QSize(880, 600);
}