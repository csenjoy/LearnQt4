#ifndef ICONEDITOR_H
#define ICONEDITOR_H

#include <QtGui/QColor>
#include <QtGui/QImage>
#include <QtWidgets/QWidget>

class IconEditor : public QWidget {
  /**
   * 1)���ڶ������ԣ�Q_PROPERTY�����࣬Q_OBJECT���Ǳ���Ҫ��
   * 2)Qt Designer��ʹ�ú����Widgetʱ��Qt Designer������ʾ��Щ�Զ�������
  */
  Q_OBJECT
  Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
  Q_PROPERTY(QImage iconImage READ iconImage WRITE setIconImage)
  Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor)

 public:
  IconEditor(QWidget *parent = 0);
   
  void setPenColor(const QColor &newColor);
  QColor penColor() const { return curColor; }
  void setZoomFactor(int newZoom);
  int zoomFactor() const { return zoom; }
  void setIconImage(const QImage &newImage);
  QImage iconImage() const { return image; }
  QSize sizeHint() const;

 protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void paintEvent(QPaintEvent *event) override;

 private:
  void setImagePixel(const QPoint &pos, bool opaque);
  QRect pixelRect(int i, int j) const;

  QColor curColor;
  QImage image;
  int zoom;
};//class IconEditor

#endif