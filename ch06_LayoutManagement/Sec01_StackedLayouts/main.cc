#include <QtWidgets/QApplication>

#include "PreferenceDialog.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    PreferenceDialog *preferenceDialog = new PreferenceDialog(nullptr);
    preferenceDialog->show();
    return app.exec();
}