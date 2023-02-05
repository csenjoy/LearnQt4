#include "IconEditor.h"

#include <QtGui>

IconEditor::IconEditor(QWidget *parent /* = 0 */) : QWidget(parent) {
  setAttribute(Qt::WA_StaticContents);

  /**
   * ���ߴ��ڲ�������sizeHint()��Ϊ������ڲ�������С�ߴ磬Ҳ��˵���������ŵ���sizeHint��ҪС
  */
  setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

  /**
   * zoom factor������������Ϊ8��˵��ͼ���е�ÿһ�����ض�����ʾ��Ϊ8x8��������
  */
  curColor = Qt::black;
  zoom = 8;
  
  /**
   * image����ʼ��Ϊ16x16�����ش�С��32λ��ARGB��ɫ��ʽ��������ɫ��ʽ����֧�ְ�͸��Ч��
   * ͨ�����һ��͸������ɫ�Ϳ������image�е�����
   * 
   * Qt�ṩ���ִ洢��ɫ������: QRgb��QColor
   */
  image = QImage(16, 16, QImage::Format_ARGB32);
  image.fill(qRgba(0, 0, 0, 0));
}

/**
 * sizeHint() ��С��ʾ
*/
QSize IconEditor::sizeHint() const {
  QSize size = zoom * image.size();
  if (zoom >= 3) {
    size += QSize(1, 1);
  }
  return size;
}

void IconEditor::setPenColor(const QColor &newColor) {
  curColor = newColor;
}

void IconEditor::setIconImage(const QImage &newImage) {
  if (newImage != image) {
    image = newImage.convertToFormat(QImage::Format_ARGB32);
    //֪ͨ���Widget��Ҫ�ػ�
    update();
    //֪ͨ���Widget�Ĳ��֣����Widget�Ĵ�С�����仯
    updateGeometry();
  }
}

void IconEditor::setZoomFactor(int newZoom) {
  if (newZoom < 1) newZoom = 1;

  if (newZoom != zoom) {
    zoom = newZoom;
    update();
    updateGeometry();
  }
}

/**
 * paint Event��������paintEvent()����������
 * 1�� Widget��һ����ʾʱ��ϵͳ���Զ�����һ�������¼����Ӷ�ǿ�ƻ������Widget
 * 2�� ���µ���Widget��Сʱ��ϵͳҲ�����һ�������¼�
 * 3�� Widget������widget�ڵ���Ȼ�����ٴ���ʾ������ʱ�򣬾ͻ����Щ���ص��������һ�������¼������Ǵ���ϵͳ�洢����������
 * 4�� ʹ��QWidget::update����QWidget::repaint��ǿ�Ʋ���һ�������¼�����������
       repaint()������ǿ�Ʋ���һ����ʱ���ػ��¼�����update()������ֻ����Qt��һ�δ����¼�ʱ�Ż�򵥵ص���һ�������¼�
       update()������ε��ã�Qt�ͻ��������εĻ����¼�ѹ����һ����һ�����¼����Ա�����˸����
       ��widget���ɼ�ʱ��Both functions do nothing
*/
void IconEditor::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  if (zoom >= 3) {
    QElapsedTimer elapsedTimer;
    elapsedTimer.start();
    painter.setPen(palette().foreground().color());
    for (int i = 0; i < image.width(); ++i) {
      painter.drawLine(zoom * i, 0,
                       zoom * i, zoom * image.height());
      for (int j = 0; j <= image.height(); ++j) {
        painter.drawLine(0, zoom * j, zoom * image.width(), zoom * j);
      }
    }
    qDebug()<<tr("elapsed: ")<<elapsedTimer.elapsed()<<tr("ms");
  }//if (zoom >= 3)

  for (int i = 0; i < image.width(); ++i) {
    for (int j = 0; j < image.height(); ++j) {
      QRect rect = pixelRect(i, j);
      if (!event->region().intersected(rect).isEmpty()) {
        QColor color = QColor::fromRgba(image.pixel(i, j));
        if (color.alpha() < 255) {
          painter.fillRect(rect, Qt::white);
        }
        painter.fillRect(rect, color);
      }
    }
  }
}

QRect IconEditor::pixelRect(int i, int j) const {
  if (zoom >= 3) {
    return QRect(zoom * i + 1, zoom * j + 1, zoom - 1, zoom - 1);
  }
  else {
    return QRect(zoom * i, zoom *j, zoom, zoom);
  }
}

void IconEditor::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    setImagePixel(event->pos(), true);
  }
  else if (event->button() == Qt::RightButton) {
    setImagePixel(event->pos(), false);
  }
}

void IconEditor::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() & Qt::LeftButton) {
    setImagePixel(event->pos(), true);
  }
  else if (event->buttons() & Qt::RightButton) {
    setImagePixel(event->pos(), false);
  }
}

void IconEditor::setImagePixel(const QPoint &pos, bool opaque) {
  int i = pos.x() / zoom;
  int j = pos.y() / zoom;

  if (image.rect().contains(i, j)) {
    if (opaque) {
      image.setPixel(i, j, penColor().rgba());
    }
    else {
      image.setPixel(i, j, qRgba(0, 0, 0, 0));
    }
    update(pixelRect(i, j));
  }
}