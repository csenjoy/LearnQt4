#include <QApplication>

#include "GoToCellDialog.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  GoToCellDialog *goToCellDialog = new GoToCellDialog();
  goToCellDialog->show();

  return app.exec();
}