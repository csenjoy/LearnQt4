#include <QtWidgets/QApplication>

#include "IconEditor.h"


int main(int argc, char **argv) {
  QApplication app(argc, argv);

  IconEditor *iconEditor = new IconEditor;

  QImage iamge(QObject::tr("./icon.png"));
  
  iconEditor->setZoomFactor(8);
  iconEditor->setIconImage(iamge);
  iconEditor->show();
  return app.exec();
}