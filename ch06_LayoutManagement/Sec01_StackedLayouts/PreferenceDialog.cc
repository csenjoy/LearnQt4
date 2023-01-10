#include "PreferenceDialog.h"

#include "AppearancePage.h"
#include "WebBrowserPage.h"
#include "MailAndNewsPage.h"
#include "AdvancePage.h"

#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QHBoxLayout>


PreferenceDialog::PreferenceDialog(QWidget *parent /* = 0 */)
    : QDialog(parent)
{
    QListWidget *listWidget = new QListWidget;
    listWidget->addItem(tr("Appearance"));
    listWidget->addItem(tr("Web Browser"));
    listWidget->addItem(tr("Mail & News"));
    listWidget->addItem(tr("Advanced"));

    QStackedLayout *stackedLayout = new QStackedLayout;
    //stackedLayout->addWidget(ap)
    stackedLayout->addWidget(new AppearancePage);
    stackedLayout->addWidget(new WebBrowserPage);
    stackedLayout->addWidget(new MailAndNewsPage);
    stackedLayout->addWidget(new AdvancePage);

    connect(listWidget, SIGNAL(currentRowChanged(int)), 
            stackedLayout, SLOT(setCurrentIndex(int)));

    listWidget->setCurrentRow(0);

    QHBoxLayout *mainLayout = new QHBoxLayout;

    mainLayout->addWidget(listWidget);
    mainLayout->addLayout(stackedLayout);

    listWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    stackedLayout->widget(3)->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    setLayout(mainLayout);

    setWindowTitle(tr("Preference Dialog"));
}

