#include <QtWidgets/QApplication>

#include "Plotter.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    Plotter *plotter = new Plotter;

    QVector<QPointF> curve1 = { {1.0,1.0}, {2.0,2.0}, {3.0,3.0}, {4.0,4.0} };

    plotter->setCurveData(1, curve1);

    plotter->show();
    return app.exec();
}