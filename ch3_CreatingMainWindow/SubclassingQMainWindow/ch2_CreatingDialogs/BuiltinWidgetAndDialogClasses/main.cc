#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtCore/QObject>
#include <QtGui/QIcon>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QToolBox>

#include <assert.h>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QWidget *mainWidget = new QWidget;
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainWidget->setLayout(mainLayout);
  
  //Using QPushButton
  QPushButton *pshButton = new QPushButton(QObject::tr("Ok"));
  mainLayout->addWidget(pshButton);
  ///////////////////////////////////////////////////

  //Using QToolButton
  QToolButton *toolButton = new QToolButton();
  //Using QPixmap to get size of image
  QPixmap pixmap;
  pixmap.load(QObject::tr("image/tool.png"));
  QSize pixmapSize = pixmap.size();

  //Setting icon of QToolButton
  QIcon icon(pixmap);
  toolButton->setIcon(icon);
  toolButton->setIconSize(pixmapSize);
  mainLayout->addWidget(toolButton);
  ///////////////////////////////////////////////////

  //Using QCheckBox
  QHBoxLayout *checkBoxLayout = new QHBoxLayout;
  QCheckBox *cbMatchCase = new QCheckBox(QObject::tr("Match &case"));
  QCheckBox *cbSearchBackward = new QCheckBox(QObject::tr("Search &backward"));
  QCheckBox *cbWildcards = new QCheckBox(QObject::tr("&Wildcards"));
  checkBoxLayout->addWidget(cbMatchCase);
  checkBoxLayout->addWidget(cbSearchBackward);
  checkBoxLayout->addWidget(cbWildcards);
  mainLayout->addLayout(checkBoxLayout);
  /////////////////////////////////////////////////////////////

  //Using QRadioButton
  QHBoxLayout *radioLayout = new QHBoxLayout;
  QRadioButton *rbAscending = new QRadioButton(QObject::tr("&Ascending"));
  QRadioButton *rbDescending = new QRadioButton(QObject::tr("&Descending"));
  QRadioButton *rbUnordered = new QRadioButton(QObject::tr("&Unordered"));
  radioLayout->addWidget(rbAscending);
  radioLayout->addWidget(rbDescending);
  radioLayout->addWidget(rbUnordered);
  mainLayout->addLayout(radioLayout);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Qt's single-page container widgets
  //Using QGroupBox
  QGroupBox *grpBox = new QGroupBox(QObject::tr("Indent"));
  QRadioButton *rbDefIndentStyle = new QRadioButton(QObject::tr("&Default indent style"));
  QRadioButton *rbNoAutoStyle = new QRadioButton(QObject::tr("&No automatic style"));
  QRadioButton *rbAutoIndent = new QRadioButton(QObject::tr("&Auto-indent"));
  QRadioButton *rbSmartIndent = new QRadioButton(QObject::tr("&Smart-indent"));

  QVBoxLayout *grpMainLayout = new QVBoxLayout(grpBox);
  grpMainLayout->addWidget(rbDefIndentStyle);
  grpMainLayout->addWidget(rbNoAutoStyle);
  grpMainLayout->addWidget(rbAutoIndent);
  grpMainLayout->addWidget(rbSmartIndent); 
  assert(grpMainLayout == grpBox->layout());
  mainLayout->addWidget(grpBox);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Qt's single-page container widgets
  //Using QFrame
  QFrame *frame = new QFrame;
  QVBoxLayout *frmLayout = new QVBoxLayout(frame);
  
  QTextEdit *frmTextEdit = new QTextEdit(QObject::tr("According to Times magazine, \"the average Yaleman, Class of '24, makes $25,111 a year.\""));
  frmTextEdit->setAcceptRichText(true);
  frmLayout->addWidget(frmTextEdit);
  QCheckBox *frmCheckBox = new QCheckBox(QObject::tr("&Rich text"));
  frmLayout->addWidget(frmCheckBox);
  mainLayout->addWidget(frame);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //QTabWidget
  QTabWidget *tabWidget = new QTabWidget;
  QWidget *wdgtProperties = new QWidget;
  QWidget *wdgtAdvanced = new QWidget;
  tabWidget->setTabPosition(QTabWidget::South);
  tabWidget->addTab(wdgtProperties, QObject::tr("&Properties"));
  QVBoxLayout *propertiesLayout = new QVBoxLayout(wdgtProperties);
  QHBoxLayout *ownerLayout = new QHBoxLayout;
  propertiesLayout->addLayout(ownerLayout);

  QLabel *ownerLabel = new QLabel(QObject::tr("&Owner:"));
  QComboBox *ownerCombox = new QComboBox;
  ownerLabel->setBuddy(ownerCombox);
  
  ownerLabel->setAutoFillBackground(true);
  auto palette = ownerLabel->palette();
  palette.setColor(QPalette::Window, Qt::red);
  ownerLabel->setPalette(palette);
  ownerCombox->addItem(QObject::tr("Administrator"));
  ownerLayout->addWidget(ownerLabel);
  //ownerLabel->setSizePolicy(QSizePolicy::)
  ownerLayout->addWidget(ownerCombox);
  ownerLayout->addStretch();
  QCheckBox *cbReadOnly = new QCheckBox(QObject::tr("&Read-only"));
  QCheckBox *cbHidden = new QCheckBox(QObject::tr("&Hidden"));
  propertiesLayout->addWidget(cbReadOnly);
  propertiesLayout->addWidget(cbHidden);

  tabWidget->addTab(wdgtAdvanced, QObject::tr("&Advanced"));
  QVBoxLayout *advancedLayout = new QVBoxLayout(wdgtAdvanced);
  //tabWidget->addTab()
  mainLayout->addWidget(tabWidget);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //QToolBox
  QToolBox *toolBox = new QToolBox;
  mainLayout->addWidget(toolBox);



  mainWidget->show();
  return app.exec();
}
