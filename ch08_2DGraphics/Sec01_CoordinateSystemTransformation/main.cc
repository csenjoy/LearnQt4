#include <qapplication.h>
#include "OvenTimer.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  OvenTimer *ovenTimer = new OvenTimer();

  ovenTimer->show();
  return app.exec();
}