#include <QtWidgets/QApplication>

#include "FindFileDialog.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    FindFileDialog *findFileDialog = new FindFileDialog(nullptr);
    findFileDialog->show();
    return app.exec();
}