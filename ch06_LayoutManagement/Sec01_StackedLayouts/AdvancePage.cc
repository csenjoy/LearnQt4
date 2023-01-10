#include "AdvancePage.h"

#include <QtWidgets/QLabel>

AdvancePage::AdvancePage(QWidget *parent /* = 0 */) : QWidget(parent) 
{
    QLabel *textLabel = new QLabel(tr("Advance Page"), this);
}

QSize AdvancePage::sizeHint() const {
    return QSize(400, 400);
}