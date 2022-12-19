#include <QApplication>

#include "SortDialog.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  SortDialog *sortDialog = new SortDialog();
  sortDialog->setColumnRange('C', 'F');
  sortDialog->show();

  return app.exec();
}