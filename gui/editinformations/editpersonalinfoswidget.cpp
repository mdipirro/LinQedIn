#include "editpersonalinfoswidget.h"
#include "gui/guistyle.h"
#include "user/profileinformations/personal.h"
#include "user/profile.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QCalendarWidget>

EditPersonalInfosWidget::EditPersonalInfosWidget(QWidget* parent,const LinQedInClient* cl):EditInfosWidget(parent,
                                                                                                    tr("Modifica informazioni personali"),
                                                                                                    cl),
    infos(getProfile().getPersonalInformations()){
    setAttribute(Qt::WA_DeleteOnClose,true);
    formWidget=new QWidget;
    infosLayout=new QFormLayout;
    name=new QLineEdit; surname=new QLineEdit; birthplace=new QLineEdit; birthState=new QLineEdit;
    connect(name,SIGNAL(returnPressed()),this,SLOT(saveRequest()));
    connect(surname,SIGNAL(returnPressed()),this,SLOT(saveRequest()));
    connect(birthplace,SIGNAL(returnPressed()),this,SLOT(saveRequest()));
    connect(birthState,SIGNAL(returnPressed()),this,SLOT(saveRequest()));
    infosLayout->addRow(tr("Nome: "),name); infosLayout->setAlignment(name,Qt::AlignCenter);
    infosLayout->addRow(tr("Cognome: "),surname); infosLayout->setAlignment(surname,Qt::AlignCenter);
    infosLayout->addRow(tr("Luogo di Nascita: "),birthplace); infosLayout->setAlignment(birthplace,Qt::AlignCenter);
    infosLayout->addRow(tr("Paese di Nascita: "),birthState); infosLayout->setAlignment(birthState,Qt::AlignCenter);
    initRadioButtons();
    infosLayout->addRow(tr("Sesso: "),genderBox); infosLayout->setAlignment(genderBox,Qt::AlignCenter);
    calendar=new QCalendarWidget;
    calendar->setGridVisible(true);
    calendar->setMinimumDate(QDate(1950,1,1));
    calendar->setMaximumDate(QDate::currentDate().addYears(-16)); //dai 16 anni in su
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    infosLayout->addRow(tr("Data di Nascita"),calendar);
    formWidget->setObjectName("form");
    formWidget->setStyleSheet("#form{"+GUIStyle::borderStyle()+"}");
    formWidget->setContentsMargins(10,10,10,10);
    formWidget->setLayout(infosLayout);
    addWidgetToMainLayout(formWidget,Qt::AlignCenter);
    initButtons();

    writeDefaultValues();
}//EditPersonalInfosWidget

void EditPersonalInfosWidget::initRadioButtons(){
    genderBox=new QGroupBox;
    genderBox->setStyleSheet("QGroupBox{"+GUIStyle::formBorderStyle()+"}");
    male=new QRadioButton(tr("Uomo"));
    female=new QRadioButton(tr("Donna"));
    genderLayout=new QHBoxLayout;
    genderLayout->addWidget(male);
    genderLayout->addWidget(female);
    genderLayout->addStretch(1);
    genderBox->setLayout(genderLayout);
}//initRadioButtons

void EditPersonalInfosWidget::writeDefaultValues() const{
    name->setText(""); name->setPlaceholderText(infos.getName());
    surname->setText(""); surname->setPlaceholderText(infos.getSurname());
    birthplace->setText(""); birthplace->setPlaceholderText(infos.getBirthplace());
    birthState->setText(""); birthState->setPlaceholderText(infos.getBirthState());
    (infos.getGender()==Personal::M)?male->setChecked(true):female->setChecked(true);
    calendar->setSelectedDate(infos.getBirthdate());
}//writeDefaultValues

void EditPersonalInfosWidget::saveRequest(){
    Personal p((name->text()=="")?name->placeholderText():name->text(),
               (surname->text()=="")?surname->placeholderText():surname->text(),
               getInformationText(birthplace),
               getInformationText(birthState),
               calendar->selectedDate(),
               (male->isChecked())?Personal::M:Personal::F);
    Profile prof=getProfile();
    prof.updateInformationsBySectionName(Personal::getIDString(),p);
    emit save(prof);
}//saveRequest
