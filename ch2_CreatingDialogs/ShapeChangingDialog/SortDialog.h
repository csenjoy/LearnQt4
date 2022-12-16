#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <memory>//Using std::unique_ptr

#include <QDialog>//Inherit QDialog

namespace Ui {
class SortDialog;//Predeclare Ui::SortDialog which is genrated by uic using forms/SortDialog.ui
}

class SortDialog : public QDialog {
 public:
  SortDialog(QWidget *parent = nullptr);
  ~SortDialog() = default;
 private slots:
  /**
   * @brief Connect to signal textChanged(const QString &) from lineEdit.
   *        It is correct that connects one parameter function to none parameter function
   */
  void on_lineEdit_textChanged();
 private:
  std::unique_ptr<Ui::SortDialog> ui;//Comboine with ui component object
};//class SortDialog

#endif /* SORTDIALOG_H */
