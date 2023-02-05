#include "MainWindow.h"

#include <QtWidgets/QDockWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QAction>
#include <QtWidgets/QScrollArea>
#include <QtCore/QSettings>

#include "IconEditor.h"

MainWindow::MainWindow() {
  QDockWidget *shapesDockWidget = new QDockWidget(tr("Shapes"));
  shapesDockWidget->setObjectName("shapesDockWidget");

  QTreeWidget *treeWidget = new QTreeWidget;
  shapesDockWidget->setWidget(treeWidget);

  shapesDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
  addDockWidget(Qt::RightDockWidgetArea, shapesDockWidget);
 
  QToolBar *fontToolBar = new QToolBar(tr("Font"));
  fontToolBar->setObjectName("fontToolBar");

  QComboBox *familyComboBox = new QComboBox;
  fontToolBar->addWidget(familyComboBox);
  QSpinBox *sizeSpinBox = new QSpinBox;
  fontToolBar->addWidget(sizeSpinBox);

  QAction *boldAction = new QAction(tr("bold"), this);
  fontToolBar->addAction(boldAction);
  QAction *italicAction = new QAction(tr("italic"), this);
  fontToolBar->addAction(italicAction);
  QAction *underlineAction = new QAction(tr("underline"), this);
  fontToolBar->addAction(underlineAction);
  fontToolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
  addToolBar(fontToolBar);
  //shapesDockWidget->setWidget(tr)

  IconEditor *iconEdit = new IconEditor;
  iconEdit->setIconImage(QImage(":/images/save.png"));

  QScrollArea *scrollArea = new QScrollArea;
  scrollArea->setWidget(iconEdit);

  scrollArea->viewport()->setBackgroundRole(QPalette::Dark);
  scrollArea->viewport()->setAutoFillBackground(true);
  scrollArea->setWidgetResizable(true);

  setCentralWidget(scrollArea);

  setWindowTitle(tr("Icon Editor"));
  readSettings();
}

void MainWindow::closeEvent(QCloseEvent *event) {
  writeSettings();
  QMainWindow::closeEvent(event);
}

void MainWindow::readSettings() {
  QSettings settings("Software Inc.", "Icon Editor");

  settings.beginGroup("mainWindow");
  restoreGeometry(settings.value("geometry").toByteArray());
  restoreState(settings.value("state").toByteArray());
  settings.endGroup();
}

void MainWindow::writeSettings() {
  QSettings settings("Software Inc.", "Icon Editor");

  settings.beginGroup("mainWindow");
  settings.setValue("geometry", saveGeometry());
  settings.setValue("state", saveState());
  settings.endGroup();
}