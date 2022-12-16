#include <qboxlayout.h>
#include <qchar.h>
#include <qcolor.h>
#include <qlayout.h>
#include <qnamespace.h>
#include <qpalette.h>
#include <qwidget.h>
#include <QtGui>

#include "SortDialog.h"

#if defined(__USING_HASA__)
#include "ui_sortdialog.h"

SortDialog::SortDialog(QWidget *parent)
  : QDialog(parent), ui(new Ui::SortDialog()) {
  
  ui->setupUi(this);

  ui->secondaryGroupBox->hide();
  ui->tertiaryGroupBox->hide();


  ui->widget->layout()->setSizeConstraint(QLayout::SetFixedSize);

  setColumnRange('A', 'Z');
}

SortDialog::~SortDialog() {

}

void SortDialog::setColumnRange(QChar first, QChar last) {
  ui->primaryColumnCombo->clear();
  ui->secondaryColumnCombo->clear();
  ui->tertiaryColumnCombo->clear();

  ui->secondaryColumnCombo->addItem(tr("None"));
  ui->tertiaryColumnCombo->addItem(tr("None"));
  ui->primaryColumnCombo->setMinimumSize(
      ui->secondaryColumnCombo->sizeHint());
  
  QChar ch = first;
  while (ch <= last) {
    ui->primaryColumnCombo->addItem(QString(ch));
    ui->secondaryColumnCombo->addItem(QString(ch));
    ui->tertiaryColumnCombo->addItem(QString(ch));
    ch = ch.unicode() + 1;
  }
}
#else 
SortDialog::SortDialog(QWidget *parent)
  : QDialog(parent) {
  
  setupUi(this);
  secondaryGroupBox->hide();
  tertiaryGroupBox->hide();
  
  QHBoxLayout *mainLayout = new QHBoxLayout(this);
  mainLayout->addWidget(layoutWidget);
  setLayout(mainLayout);

  //layoutWidget->layout()->setSizeConstraint(QLayout::SetFixedSize); 
  setColumnRange('A', 'Z');

  //设置primaryGroupBox布局控件Constraint SetFixedSize
  gridLayout->setSizeConstraint(QLayout::SetFixedSize);
  primaryGroupBox->setAutoFillBackground(true);

  QPalette palette = primaryGroupBox->palette();
  palette.setColor(QPalette::Window, Qt::blue);
  primaryGroupBox->setPalette(palette);
  primaryGroupBox->update();

  QObject::connect(moreButton, SIGNAL(toggled(bool)), this, SLOT(on_moreButton_toggled(bool)));
  //connect(moreButton, SIGNAL(&QPushButton::clicked), this, SLOT(&on_moreButton_clicked));
#if 0
  layoutWidget->setAutoFillBackground(true);
  QPalette dlgPalette = layoutWidget->palette();
  dlgPalette.setColor(QPalette::Window, Qt::red);
  layoutWidget->setPalette(dlgPalette);
#endif
}

SortDialog::~SortDialog() {

}

void SortDialog::setColumnRange(QChar first, QChar last) {
  primaryColumnCombo->clear();
  secondaryColumnCombo->clear();
  tertiaryColumnCombo->clear();

  secondaryColumnCombo->addItem(tr("None"));
  tertiaryColumnCombo->addItem(tr("None"));
  primaryColumnCombo->setMinimumSize(
      secondaryColumnCombo->sizeHint());
  
  QChar ch = first;
  while (ch <= last) {
    primaryColumnCombo->addItem(QString(ch));
    secondaryColumnCombo->addItem(QString(ch));
    tertiaryColumnCombo->addItem(QString(ch));
    ch = ch.unicode() + 1;
  }
}

void SortDialog::on_moreButton_toggled(bool bClicked) {
}
#endif