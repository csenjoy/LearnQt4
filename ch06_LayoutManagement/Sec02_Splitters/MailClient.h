#ifndef MAILCLIENT_H
#define MAILCLIENT_H

#include <QtWidgets/QMainWindow>

class QSplitter;

class MailClient : public QMainWindow {
public:
    MailClient(QWidget *parent = 0);
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    void writeSettins();
    void readSettings();
private:
    QSplitter *mainSplitter;
    QSplitter *rightSplitter;
};

#endif