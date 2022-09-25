#include <QApplication>
#include <QLabel>
#include <QString>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QLabel *label = new QLabel(QObject::tr("Hello world from Qt"));
  label->show();

  return app.exec();
}