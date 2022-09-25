#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <memory>//Using std::unique_ptr

#include <QDialog>//Inherit QDialog

namespace Ui {
class GoToCellDialog;//Predeclare Ui::GoToCellDialog which is genrated by uic using forms/GoToCellDialog.ui
}

class GoToCellDialog : public QDialog {
 public:
  GoToCellDialog(QWidget *parent = nullptr);
  ~GoToCellDialog() = default;
 private slots:
  /**
   * @brief Connect to signal textChanged(const QString &) from lineEdit.
   *        It is correct that connects one parameter function to none parameter function
   */
  void on_lineEdit_textChanged();
 private:
  std::unique_ptr<Ui::GoToCellDialog> ui;//Comboine with ui component object
};//class GoToCellDialog



#endif /* GOTOCELLDIALOG_H */
