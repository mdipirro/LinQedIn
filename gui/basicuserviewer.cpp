#include "basicuserviewer.h"
#include "plandialog.h"
#include "controller/linqedinuser.h"
#include "user/profile.h"
#include "user/userdata.h"
#include "guistyle.h"
#include "user/profileinformations/personal.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>

BasicUserViewer::BasicUserViewer(const LinQedInUser& user,QWidget* parent):QFrame(parent){
    setAttribute(Qt::WA_DeleteOnClose);
    mainHorizontalLayout=new QHBoxLayout;

    image=new QLabel;
    image->setPixmap(QPixmap(user.getImagePath()));
    image->setScaledContents(true);
    image->setMaximumSize(130,100);
    mainHorizontalLayout->addWidget(image);

    infosLayout=new QVBoxLayout;
    username=new QLabel(user.getLoginInfo().getEmailAddress());
    username->setStyleSheet("font-weight:bold;");
    infosLayout->addWidget(username);

    name=new QLabel(user.getProfile().getPersonalInformations().getName()+" "+
                    user.getProfile().getPersonalInformations().getSurname());
    infosLayout->addWidget(name);

    plan=new QLabel(user.getUserPlan());
    infosLayout->addWidget(plan);

    QDate ed=user.getEspireDate();
    espireDate=new QLabel("In scadenza il: "+((ed.isValid())?ed.toString("d/M/yyyy"):tr("mai")));
    infosLayout->addWidget(espireDate);

    deleteUser=new QPushButton(tr("Elimina Utente"));
    deleteUser->setCursor(QCursor(Qt::PointingHandCursor));
    infosLayout->addWidget(deleteUser);
    connect(deleteUser,SIGNAL(clicked()),this,SLOT(emitDeleteRequest()));
    changePlan=new QPushButton(tr("Cambia Piano"));
    changePlan->setCursor(QCursor(Qt::PointingHandCursor));
    infosLayout->addWidget(changePlan);
    connect(changePlan,SIGNAL(clicked()),this,SLOT(openPlanDialog()));

    mainHorizontalLayout->addLayout(infosLayout);
    setLayout(mainHorizontalLayout);
    setMinimumSize(270,200);
    setMaximumSize(370,200);
}//BasicUserViewer

void BasicUserViewer::emitDeleteRequest() const{emit deleteRequest(username->text());}

void BasicUserViewer::openPlanDialog() const{
    PlanDialog* pd=new PlanDialog(const_cast<BasicUserViewer*>(this)); //const_cast per perché so che il parent non verrà modificato
    connect(pd,SIGNAL(planSelected(int)),this,SLOT(emitChangePlanRequest(int)));
    pd->open();
}//openPlanDialog

void BasicUserViewer::emitChangePlanRequest(int p) const{emit changePlanRequest(username->text(),p);}
