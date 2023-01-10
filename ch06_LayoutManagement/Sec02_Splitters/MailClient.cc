#include "MailClient.h"

#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtCore/QSettings>

MailClient::MailClient(QWidget *parent /* = 0 */) 
    : QMainWindow(parent) {
    
    rightSplitter = new QSplitter(Qt::Vertical);
    QTreeWidget *messageTreeWidget = new QTreeWidget;
    rightSplitter->addWidget(messageTreeWidget);
    QTextEdit *textEdit = new QTextEdit;
    rightSplitter->addWidget(textEdit);
    //设置1号位置（也就是textEdit）stretch factor 1
    //textEdit在rightSplitter中尽可能多占用多余空间
    rightSplitter->setStretchFactor(1, 1);

    mainSplitter = new QSplitter(Qt::Horizontal);
    QTreeWidget *foldersTreeWidget = new QTreeWidget;
    mainSplitter->addWidget(foldersTreeWidget);
    mainSplitter->addWidget(rightSplitter);
    //设置rightSplitter尽可能多占用空间，最终效果是textEdit尽可能多占用多余空间
    mainSplitter->setStretchFactor(1, 1);
    setCentralWidget(mainSplitter);
    
    setWindowTitle(tr("Mail Client"));
    readSettings();
}

void MailClient::closeEvent(QCloseEvent *event) {
    writeSettins();
    QMainWindow::closeEvent(event);
}

void MailClient::writeSettins()
{
    QSettings settings(tr("Software Inc."), tr("Mail Client"));

    settings.beginGroup("mainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("mainSplitter", mainSplitter->saveState());
    settings.setValue("rightSplitter", rightSplitter->saveState());
    settings.endGroup();
}

void MailClient::readSettings()
{
    QSettings settings("Software Inc.", "Mail Client");
    settings.beginGroup("mainWindow");
    restoreGeometry(settings.value("geometry").toByteArray());
    mainSplitter->restoreState(settings.value("mainSplitter").toByteArray());
    rightSplitter->restoreState(settings.value("rightSplitter").toByteArray());
    settings.endGroup();
}
