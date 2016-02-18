#include "editlogininformations.h"
#include "gui/guistyle.h"
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>

QString EditLoginInformations::unchangedStr=tr("Invariata");

EditLoginInformations::EditLoginInformations(const UserData& ud,QWidget* parent):EditInfosWidget(parent,"Modifica informazioni di accesso"),
    login(ud){
    setAttribute(Qt::WA_DeleteOnClose);
    formWidget=new QWidget;
    formLayout=new QFormLayout;
    mail=new QLineEdit; mail->setPlaceholderText(login.getEmailAddress()); mail->setMinimumWidth(250);
    connect(mail,SIGNAL(returnPressed()),this,SLOT(saveRequest()));
    oldPwd=new QLineEdit; oldPwd->setEchoMode(QLineEdit::Password); oldPwd->setPlaceholderText(unchangedStr);
    connect(oldPwd,SIGNAL(returnPressed()),this,SLOT(saveRequest()));
    newPwd1=new QLineEdit; newPwd1->setEchoMode(QLineEdit::Password); newPwd1->setPlaceholderText(unchangedStr);
    connect(newPwd1,SIGNAL(returnPressed()),this,SLOT(saveRequest()));
    newPwd2=new QLineEdit; newPwd2->setEchoMode(QLineEdit::Password); newPwd2->setPlaceholderText(unchangedStr);
    connect(newPwd2,SIGNAL(returnPressed()),this,SLOT(saveRequest()));
    formLayout->addRow(tr("Indirizzo eMail"),mail);
    formLayout->addRow(tr("Vecchia Password"),oldPwd);
    formLayout->addRow(tr("Nuova Password"),newPwd1);
    formLayout->addRow(tr("Conferma la nuova password"),newPwd2);
    formWidget->setLayout(formLayout);
    addWidgetToMainLayout(formWidget,Qt::AlignCenter);
    formWidget->setContentsMargins(10,10,10,10);
    formWidget->setObjectName("form");
    formWidget->setStyleSheet("#form{"+GUIStyle::borderStyle()+"padding-left:10px;padding-top:10px;}");

    error=new QLabel;
    error->setVisible(false);
    error->setStyleSheet(GUIStyle::errorLabelStyle());
    addWidgetToMainLayout(error,Qt::AlignCenter);

    initButtons(true,true,true);
    writeDefaultValues();
}//EditLoginInformations

void EditLoginInformations::writeDefaultValues() const{
    mail->setText(login.getEmailAddress());
    oldPwd->setText(""); newPwd1->setText(""); newPwd2->setText("");
}//writeDefaultValues

void EditLoginInformations::saveRequest(){
    if(oldPwd->text()!=""){ //anche cambio pwd
        if(oldPwd->text()==login.getPassword()){
            if(newPwd1->text().length()>=8 && newPwd2->text().length()>=8){
                if(newPwd1->text()==newPwd2->text())
                    emit save(UserData(mail->text(),newPwd1->text()));
                else{
                    error->setVisible(true);
                    error->setText(tr("Password Diverse"));
                }//else
            }//if
            else{
                error->setVisible(true);
                error->setText(tr("Almeno 8 caratteri nella nuova password"));
            }//else
        }//if
        else{
            error->setVisible(true);
            error->setText(tr("Vecchia Password Sbagliata"));
        }//else
    }//if
    else emit save(UserData(mail->text(),login.getPassword())); //solo cambio username
}//saveRequest
