#include <QtWidgets/QApplication>
#include <QtWidgets/QSplashScreen>

#include "mainwindow.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QSplashScreen *splash = new QSplashScreen;
  splash->setPixmap(QPixmap(QObject::tr(":/images/splash.png")));
  splash->show();

  Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
  splash->showMessage(QObject::tr("Setting up the main window..."),
    topRight, Qt::white);

  MainWindow mainWin;

  splash->showMessage(QObject::tr("Establishing connections..."),
    topRight, Qt::white);
  
 
  mainWin.show();
  splash->finish(&mainWin);
  delete splash;

  return app.exec();
}