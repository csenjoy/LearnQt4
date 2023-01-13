#include <QtWidgets/QApplication>

#include "Ticker.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  Ticker *ticker = new Ticker;

  ticker->setText(QObject::tr("this is a message from scroll##"));
  ticker->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  ticker->show();
  return app.exec();
}