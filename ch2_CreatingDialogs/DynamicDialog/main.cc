#include <iostream>

#include <QtWidgets/QApplication>
#include <QtUiTools/QUiLoader>
#include <QtCore/QFile>
#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLayout>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  //Use QFile and QUiLoader to load ui file convert to C++ class
  QUiLoader uiLoader;
  QFile uiFile("./forms/SortDialog.ui");
  QWidget *sortDialog = uiLoader.load(&uiFile);

  if (sortDialog) {
    //sortDialog->layout()->setSizeConstraint(QLayout::SetFixedSize);

    auto mainLayout = sortDialog->findChild<QGridLayout *>("gridLayout_4");
    if (mainLayout) {
      mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    }
    //sortDialog->setSizePolicy(QSizePolicy::Fixed);
    sortDialog->show();
  }
  return app.exec();
}