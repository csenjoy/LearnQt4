#include "MainWindow.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  MainWindow *mainWindow = new MainWindow;
  mainWindow->show();

  return app.exec();
}