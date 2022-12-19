#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QtWidgets/QDialog>

class QLabel;
class QLineEdit;
class QCheckBox;
class QPushButton;

class FindDialog : public QDialog {
  Q_OBJECT
 public:
  FindDialog(QWidget *parent = nullptr);
  ~FindDialog() = default;
 signals:
  void findPrevious(const QString &str, Qt::CaseSensitivity cs);
  void findNext(const QString &str, Qt::CaseSensitivity cs);

 private slots:
  void findClicked();
  void enableFindButton(const QString &text);
 private:
  QLabel *label;
  QLineEdit *lineEdit;
  QCheckBox *caseCheckBox;
  QCheckBox *backwardCheckBox;
  QPushButton *findButton;
  QPushButton *closeButton;
};//class FindDialog

#endif /* FINDDIALOG_H */
