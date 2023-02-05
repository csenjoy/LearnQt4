#include <QtWidgets/QMainWindow>

class MainWindow : public QMainWindow  {
 public:
   MainWindow();

  void closeEvent(QCloseEvent *) override;
 private:
  void readSettings();
  void writeSettings();
};