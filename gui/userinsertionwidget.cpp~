#include "userinsertionwidget.h"
#include "adminwindow.h"
#include "plandialog.h"
#include "guistyle.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QRadioButton>

QString UserInsertionWidget::nameStr=tr("Nome *");
QString UserInsertionWidget::surnameStr=tr("Cognome *");
QString UserInsertionWidget::emailStr=tr("Email *");
QString UserInsertionWidget::planStr=tr("Piano");
int UserInsertionWidget::buttonsMaxWidth=150;

UserInsertionWidget::UserInsertionWidget(QWidget* parent):QFrame(parent),planS(1){
    setAttribute(Qt::WA_DeleteOnClose);
    setStyleSheet(GUIStyle::generalStyle());
    mainVerticalLayout=new QVBoxLayout;

    logo=new QLabel;
    GUIStyle::initLogo(logo);
    mainVerticalLayout->addWidget(logo,0,Qt::AlignRight);

    title=new QLabel(tr("Inserimento di un nuovo utente"));
    title->setStyleSheet(GUIStyle::headerStyle());
    mainVerticalLayout->addWidget(title,0,Qt::AlignCenter);

    QWidget* formWidget=new QWidget;
    formLayout=new QFormLayout;
    name=new QLineEdit;
    name->setPlaceholderText(nameStr);
    connect(name,SIGNAL(returnPressed()),this,SLOT(userInsertion()));
    surname=new QLineEdit;
    surname->setPlaceholderText(surnameStr);
    connect(surname,SIGNAL(returnPressed()),this,SLOT(userInsertion()));
    email=new QLineEdit;
    email->setPlaceholderText(emailStr);
    connect(email,SIGNAL(returnPressed()),this,SLOT(userInsertion()));
    initRadioButtons();
    plan=new QPushButton(tr("Piano"));
    connect(plan,SIGNAL(clicked()),this,SLOT(planSelection()));
    formLayout->addRow(nameStr,name);
    formLayout->addRow(surnameStr,surname);
    formLayout->addRow(emailStr,email);
    formLayout->addRow(tr("Sesso"),genderBox);
    formLayout->setAlignment(genderBox,Qt::AlignCenter);
    formLayout->addRow(planStr,plan);

    formWidget->setLayout(formLayout);
    formWidget->setMinimumWidth(300);
    formWidget->setObjectName("form");
    formWidget->setStyleSheet("#form{"+GUIStyle::borderStyle()+"}");
    formWidget->setContentsMargins(10,10,10,10);
    mainVerticalLayout->addWidget(formWidget,0,Qt::AlignCenter);

    error=new QLabel;
    error->setStyleSheet(GUIStyle::errorLabelStyle());
    error->setVisible(false);
    mainVerticalLayout->addWidget(error,0,Qt::AlignCenter);

    buttonsLayout=new QHBoxLayout;
    insert=new QPushButton(tr("Inserisci"));
    insert->setCursor(QCursor(Qt::PointingHandCursor));
    insert->setMaximumWidth(buttonsMaxWidth);
    connect(insert,SIGNAL(clicked()),this,SLOT(userInsertion()));
    cancel=new QPushButton(tr("Annulla"));
    cancel->setCursor(QCursor(Qt::PointingHandCursor));
    cancel->setMaximumWidth(buttonsMaxWidth);
    reset=new QPushButton(tr("Azzera campi"));
    reset->setCursor(QCursor(Qt::PointingHandCursor));
    reset->setMaximumWidth(buttonsMaxWidth);
    connect(reset,SIGNAL(clicked()),this,SLOT(resetFormFields()));
    buttonsLayout->addWidget(insert);
    buttonsLayout->addWidget(cancel);
    buttonsLayout->addWidget(reset);
    mainVerticalLayout->addLayout(buttonsLayout);
    connect(cancel,SIGNAL(clicked()),this,SLOT(closeRequest()));

    setLayout(mainVerticalLayout);
    name->setFocus();
}//UserInsertionWidget

void UserInsertionWidget::initRadioButtons(){
    genderBox=new QGroupBox;
    male=new QRadioButton(tr("Uomo"));
    male->setChecked(true);
    female=new QRadioButton(tr("Donna"));
    genderBox->setStyleSheet("QGroupBox{"+GUIStyle::formBorderStyle()+"}");
    genderLayout=new QHBoxLayout;
    genderLayout->addWidget(male);
    genderLayout->addWidget(female);
    genderLayout->addStretch(1);
    genderBox->setLayout(genderLayout);
}//initRadioButtons

bool UserInsertionWidget::checkFields() const{
    bool ok=false;
    if(name->text()=="" ||surname->text()=="" || email->text()==""){
        error->setText(tr("I campi contrassegnati con * sono obbligatori."));
        error->setVisible(true);
    }//else
    else ok=true;
    return ok;
}//checkFields

void UserInsertionWidget::userInsertion() const{
    if(checkFields())
        emit insertion(name->text(),surname->text(),email->text(),planS,(male->isChecked())?Personal::M:Personal::F);
}//userInsertion

void UserInsertionWidget::resetFormFields() const{
    name->setText("");
    surname->setText("");
    email->setText("");
    plan->setText(tr("Seleziona un piano"));
}//resetFormFields

void UserInsertionWidget::planSelection() const{
    PlanDialog* pd=new PlanDialog(const_cast<UserInsertionWidget*>(this),PlanDialog::idAndDescription);
    connect(pd,SIGNAL(planSelected(int,const QString&)),this,SLOT(planSelected(int,const QString&)));
    pd->open();
}//planSelect

void UserInsertionWidget::planSelected(int planNo,const QString& descr){
    planS=planNo;
    plan->setText(descr);
}//planSelected

void UserInsertionWidget::closeRequest() const{emit closeSignal(-1);}
