#include "GoToCellDialog.h"

#include <QRegExp>
#include <QRegExpValidator>

#include "ui_gotocelldialog.h"

GoToCellDialog::GoToCellDialog(QWidget *parent) : QDialog(parent), ui(new Ui::GoToCellDialog()) {
  ui->setupUi(this);

  //Add QRegExpValidator into lineEdit
  QRegExp regExp(tr("[A-Z][a-z][1-9][0-9]{0,2}"));
  ui->lineEdit->setValidator(new QRegExpValidator(regExp, this));

  //Connection signals and slots
  connect(ui->okButton, SIGNAL(clicked()),
          this, SLOT(accept()));
  connect(ui->cancelButton, SIGNAL(clicked()),
          this, SLOT(reject()));

  connect(ui->lineEdit, SIGNAL(textChanged(const QString &)),
          this, SLOT(on_lineEdit_textChanged()));

  QHBoxLayout *mainLayout = new QHBoxLayout(this);
  mainLayout->addWidget(ui->widget);
  setLayout(mainLayout);

  layout()->setSizeConstraint(QLayout::SetFixedSize);
  //ui->mainVerticalLayout->setSizeConstraint(QLayout::SetFixedSize);
}

GoToCellDialog::~GoToCellDialog() {

}

QLineEdit *GoToCellDialog::lineEdit() const {
  return ui->lineEdit;
}

void GoToCellDialog::on_lineEdit_textChanged() {
  ui->okButton->setEnabled(ui->lineEdit->hasAcceptableInput());
}