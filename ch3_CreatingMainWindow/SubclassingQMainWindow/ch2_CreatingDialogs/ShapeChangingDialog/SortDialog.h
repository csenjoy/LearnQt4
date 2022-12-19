#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <memory>//Using std::unique_ptr

#include <QtWidgets/QDialog>//Inherit QDialog

#if defined(__USING_HASA__)
namespace Ui {
class SortDialog;//Predeclare Ui::SortDialog which is genrated by uic using forms/SortDialog.ui
}
#else 
#include "ui_sortdialog.h"
#endif
class SortDialog : public QDialog
#if !defined(__USING_HASA__)
  , public Ui::SortDialog 
#endif
{
  Q_OBJECT
 public:
  SortDialog(QWidget *parent = nullptr);
  ~SortDialog();

  void setColumnRange(QChar first, QChar last);

private slots:
  void on_moreButton_toggled(bool bClicked);
#if defined(__USING_HASA__)
  std::unique_ptr<Ui::SortDialog> ui;//Comboine with ui component object
#endif
};//class SortDialog

#endif /* SORTDIALOG_H */
