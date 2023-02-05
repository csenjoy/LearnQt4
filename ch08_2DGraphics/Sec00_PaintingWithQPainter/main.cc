#include <QtWidgets/QApplication>

#include "PaintingWidget.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  PaintingWidget *painting = new PaintingWidget();
  painting->show();
  return app.exec();
}