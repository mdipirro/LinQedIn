#ifndef EDITPERSONALINFOSWIDGET_H
#define EDITPERSONALINFOSWIDGET_H

#include "editinfoswidget.h"
#include "user/profileinformations/personal.h"

class Profile;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QFormLayout;
class QLineEdit;
class QPushButton;
class QWidget;
class QGroupBox;
class QRadioButton;
class QCalendarWidget;

class EditPersonalInfosWidget:public EditInfosWidget{
    Q_OBJECT
private:
    Personal infos;
    QWidget *formWidget;
    QHBoxLayout *genderLayout;
    QFormLayout *infosLayout;
    QLineEdit *name,*surname,*birthplace,*birthState;
    QGroupBox *genderBox;
    QRadioButton *male,*female;
    QCalendarWidget *calendar;

    void initRadioButtons();

public:
    explicit EditPersonalInfosWidget(QWidget*,const LinQedInClient*);

protected slots:
    void saveRequest();
    void writeDefaultValues() const;
};

#endif // EDITPERSONALINFOSWIDGET_H
