#include <QtWidgets/QApplication>

#include "MailClient.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MailClient *mailClient = new MailClient;
    mailClient->show();
    return app.exec();
}