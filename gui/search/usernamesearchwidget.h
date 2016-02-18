#ifndef USERNAMESEARCHWIDGET_H
#define USERNAMESEARCHWIDGET_H

#include "searchwidget.h"

class QLineEdit;

class UsernameSearchWidget:public SearchWidget{
    Q_OBJECT
private:
    QLineEdit *username;
public:
    UsernameSearchWidget(LinQedInClient*,QWidget* =0);
    void focus() const;

protected slots:
    void search();
};

#endif // USERNAMESEARCHWIDGET_H
