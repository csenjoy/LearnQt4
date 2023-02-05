#ifndef ADVANCEPAGE_H
#define ADVANCEPAGE_H

#include <QtWidgets/QWidget>

class AdvancePage : public QWidget 
{
public:
    AdvancePage(QWidget *parent = 0);
protected:
   QSize sizeHint() const override;
};//class AdvancePage

#endif