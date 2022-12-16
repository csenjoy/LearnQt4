#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidgetSelectionRange>

class Spreadsheet : public QTabWidget {
 public:
  Spreadsheet(QWidget *parent = 0);

  QTableWidgetSelectionRange selectedRange();
};//class Spreadsheet

#endif