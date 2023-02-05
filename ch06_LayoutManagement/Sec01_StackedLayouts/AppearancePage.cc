#include "AppearancePage.h"

#include <QtWidgets/QLabel>

AppearancePage::AppearancePage(QWidget *parent /* = 0 */) : QWidget(parent) {
    QLabel *textLabel = new QLabel(tr("Appearance Page"), this);
}