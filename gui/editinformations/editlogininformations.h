#ifndef EDITLOGININFORMATIONS_H
#define EDITLOGININFORMATIONS_H

#include "user/userdata.h"
#include "editinfoswidget.h"
#include <QString>

class QWidget;
class QLineEdit;
class QFormLayout;
class QButton;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;

class EditLoginInformations:public EditInfosWidget{
    Q_OBJECT
private:
    UserData login;
    QLineEdit *mail,*oldPwd,*newPwd1,*newPwd2;
    QWidget *formWidget;
    QFormLayout *formLayout;
    QLabel *error;

    static QString unchangedStr;

public:
    explicit EditLoginInformations(const UserData&,QWidget* parent=0);

protected slots:
    void saveRequest();
    void writeDefaultValues() const;
};

#endif // EDITLOGININFORMATIONS_H
