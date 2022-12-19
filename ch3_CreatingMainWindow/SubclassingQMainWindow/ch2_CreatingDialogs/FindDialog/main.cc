#include <QApplication>

#include "FindDialog.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  FindDialog *findDialog = new FindDialog();
  findDialog->show();

  return app.exec();
}