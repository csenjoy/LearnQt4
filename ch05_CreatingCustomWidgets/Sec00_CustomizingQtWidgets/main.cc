#include <QtWidgets/QApplication>

#include "HexSpinBox.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  HexSpinBox *hexSpinBox = new HexSpinBox;
  hexSpinBox->show();
  return app.exec();
}