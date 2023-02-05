#include <QtWidgets/QApplication>
#include <QtWidgets/QScrollArea>

#include "IconEditor.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  IconEditor *iconEditor = new IconEditor;
  iconEditor->setIconImage(QImage(":images/mouse.png"));

  QScrollArea scrollArea;
  scrollArea.setWidget(iconEditor);
  scrollArea.viewport()->setBackgroundRole(QPalette::Dark);
  scrollArea.viewport()->setAutoFillBackground(true);

  scrollArea.setWidgetResizable(true);
  scrollArea.setWindowTitle(QObject::tr("Icon Editor"));

  scrollArea.show();
  return app.exec();
}