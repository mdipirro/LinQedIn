#ifndef USERINSERTIONWIDGET_H
#define USERINSERTIONWIDGET_H

#include <QFrame>
#include <QString>
#include "user/profileinformations/personal.h"

class QFormLayout;
class QVBoxLayout;
class QHBoxLayout;
class QLineEdit;
class QPushButton;
class QLabel;
class QGroupBox;
class QRadioButton;

class UserInsertionWidget:public QFrame{
    Q_OBJECT
private:
    QVBoxLayout* mainVerticalLayout;
    QHBoxLayout *buttonsLayout,*genderLayout;
    QFormLayout* formLayout;
    QLabel *logo,*title,*error;
    QLineEdit *name,*surname,*email;
    QGroupBox *genderBox;
    QRadioButton *male,*female;
    QPushButton *plan,*insert,*cancel,*reset;
    int planS;

    static QString nameStr,surnameStr,emailStr,planStr;
    static int buttonsMaxWidth;

    void initRadioButtons();
    bool checkFields() const;

public:
    explicit UserInsertionWidget(QWidget* =0);

signals:
    void insertion(const QString&,const QString&,const QString&,int,Personal::Genders) const;
    void closeSignal(int) const;

private slots:
    void userInsertion() const;
    void resetFormFields() const;
    void planSelection() const;
    void planSelected(int,const QString&);
    void closeRequest() const;
};

#endif // USERINSERTIONWIDGET_H
