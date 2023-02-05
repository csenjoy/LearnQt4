#include <QtWidgets/QApplication> 
#include <QtCore>
#include <QtWidgets>

class AppEventFilter : public QObject {
 public:
   bool eventFilter(QObject *target, QEvent *event) override {
     qDebug() << target->objectName() << "event: " << event->type();
     return QObject::eventFilter(target, event);
   }
};

int main(int argc, char **argv) {

  AppEventFilter appEventFilter;

  QApplication app(argc, argv);
  app.installEventFilter(&appEventFilter);

  QWidget *widget = new QWidget;
  widget->show();

  return app.exec();
}