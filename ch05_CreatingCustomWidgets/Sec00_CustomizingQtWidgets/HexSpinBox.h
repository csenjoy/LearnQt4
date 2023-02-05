#ifndef HEXSPINBOX_H
#define HEXSPINBOX_H

#include <QtWidgets/QSpinBox>

class QRegExpValidator;

class HexSpinBox : public QSpinBox {
  Q_OBJECT
 public:
  HexSpinBox(QWidget *parent = nullptr);

 protected:
  QValidator::State validate(QString &text, int &pos) const override;
  int valueFromText(const QString &text) const override;
  QString textFromValue(int value) const override;
 private:
  QRegExpValidator *validator;
};//class HexSpinBox

#endif