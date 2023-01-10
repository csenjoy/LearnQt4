#include "FindFileDialog.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QTreeWidget>


FindFileDialog::FindFileDialog(QWidget *parent /* = 0 */)
    : QDialog(parent)
{
    QLabel *nameLabel = new QLabel(tr("Named:"));
    QLineEdit *nameEdit = new QLineEdit();
    QLabel *lookInLabel = new QLabel(tr("Look in:"));
    QLineEdit *lookInEdit = new QLineEdit();

    QCheckBox *includeSubFoldersCheckBox = new QCheckBox(tr("Include subfolders"));
    QTreeWidget *filesTreeWidget = new QTreeWidget(this);
    QLabel *messageLabel = new QLabel(tr("0 files found"));

    QPushButton *findButton = new QPushButton(tr("Find"));
    QPushButton *StopButton = new QPushButton(tr("Stop"));
    QPushButton *CloseButton = new QPushButton(tr("Close"));
    QPushButton *helpButton = new QPushButton(tr("Help"));

    QGridLayout *leftLayout = new QGridLayout;

    leftLayout->addWidget(nameLabel, 0, 0);
    leftLayout->addWidget(nameEdit, 0, 1);
    leftLayout->addWidget(lookInLabel, 1, 0);
    leftLayout->addWidget(lookInEdit, 1, 1);
    leftLayout->addWidget(includeSubFoldersCheckBox, 2, 0, 1, 2);
    leftLayout->addWidget(filesTreeWidget, 3, 0, 1, 2);
    leftLayout->addWidget(messageLabel, 4, 0, 1, 2);

    //filesTreeWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    //messageLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    auto sizePolicy = filesTreeWidget->sizePolicy();
    //sizePolicy.setVerticalStretch(2);
    int stretchFactor = sizePolicy.verticalStretch();
    filesTreeWidget->setSizePolicy(sizePolicy);

    QSize size = filesTreeWidget->sizeHint();
    size = filesTreeWidget->minimumSizeHint();


    QVBoxLayout *rightLayout = new QVBoxLayout;

    rightLayout->addWidget(findButton);
    rightLayout->addWidget(StopButton);
    rightLayout->addWidget(CloseButton);
    rightLayout->addStretch();
    rightLayout->addWidget(helpButton);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Find Files or Folders"));
}

