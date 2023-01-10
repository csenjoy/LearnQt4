#include "IconEditor.h"

#include <QtGui>

IconEditor::IconEditor(QWidget *parent /* = 0 */) : QWidget(parent) {
  setAttribute(Qt::WA_StaticContents);

  /**
   * 告诉窗口布局器，sizeHint()作为这个窗口部件的最小尺寸，也就说不可以缩放到比sizeHint还要小
  */
  setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

  /**
   * zoom factor缩放因子设置为8，说明图标中的每一个像素都会显示成为8x8的正方形
  */
  curColor = Qt::black;
  zoom = 8;
  
  /**
   * image被初始化为16x16的像素大小和32位的ARGB颜色格式，这种颜色格式可以支持半透明效果
   * 通过填充一种透明的颜色就可以清空image中的数据
   * 
   * Qt提供两种存储颜色的类型: QRgb和QColor
   */
  image = QImage(16, 16, QImage::Format_ARGB32);
  image.fill(qRgba(0, 0, 0, 0));
}

/**
 * sizeHint() 大小提示
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
    //通知这个Widget需要重绘
    update();
    //通知这个Widget的布局，这个Widget的大小发生变化
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
 * paint Event产生并且paintEvent()函数被调用
 * 1） Widget第一次显示时，系统会自动产生一个绘制事件，从而强制绘制这个Widget
 * 2） 重新调整Widget大小时，系统也会产生一个绘制事件
 * 3） Widget被其它widget遮挡，然后又再次显示出来的时候，就会对那些隐藏的区域产生一个绘制事件（除非窗口系统存储了整个区域）
 * 4） 使用QWidget::update或者QWidget::repaint来强制产生一个绘制事件，两者区别：
       repaint()函数会强制产生一个即时的重绘事件，而update()函数则只是在Qt下一次处理事件时才会简单地调用一个绘制事件
       update()函数多次调用，Qt就会把连续多次的绘制事件压缩成一个单一绘制事件，以避免闪烁现象
       当widget不可见时，Both functions do nothing
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