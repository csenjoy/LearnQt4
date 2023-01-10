#include "MailAndNewsPage.h"

#include <QtWidgets/QLabel>

MailAndNewsPage::MailAndNewsPage(QWidget *parent /* = 0 */) : QWidget(parent) {
    QLabel *textLabel = new QLabel(tr("Mail & News Page"), this);
}