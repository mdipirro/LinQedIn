#ifndef NAMESURNAMESEARCHWIDGET_H
#define NAMESURNAMESEARCHWIDGET_H

#include "searchwidget.h"

class QLineEdit;

class NameSurnameSearchWidget:public SearchWidget{
    Q_OBJECT
private:
    QLineEdit *name,*surname;
public:
    NameSurnameSearchWidget(LinQedInClient*,QWidget* =0);
    void focus() const;

protected slots:
    void search();
};

#endif // NAMESURNAMESEARCHWIDGET_H
