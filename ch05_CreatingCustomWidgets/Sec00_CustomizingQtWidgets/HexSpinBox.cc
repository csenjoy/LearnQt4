#include "HexSpinBox.h"

#include <QtGui>

HexSpinBox::HexSpinBox(QWidget *parent /* = nullptr */) : QSpinBox(parent) {
  setRange(0, 255);
  validator = new QRegExpValidator(QRegExp(tr("[0-9A-Fa-f]{1,8}")), this);
}

QValidator::State HexSpinBox::validate(QString &text, int &pos) const {
  return validator->validate(text, pos);
}

QString HexSpinBox::textFromValue(int value) const {
  return QString::number(value, 16).toUpper();
}

int HexSpinBox::valueFromText(const QString &text) const {
  bool ok;
  return text.toInt(&ok, 16);
}