#include "WebBrowserPage.h"

#include <QtWidgets/QLabel>

WebBrowserPage::WebBrowserPage(QWidget *parent /* = 0 */) : QWidget(parent) {
    QLabel *textLabel = new QLabel(tr("Web Browser Page"), this);
}