#include "basiccontactviewer.h"
#include "clientprofilewidget.h"
#include "clientwindow.h"
#include "guistyle.h"
#include "controller/linqedinuser.h"
#include "user/user.h"
#include "user/userdata.h"
#include "user/profileinformations/personal.h"
#include "user/profileinformations/occupations.h"
#include "user/profileinformations/job.h"
#include "controller/linqedinclient.h"
#include "exceptions/noinfoexception.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

BasicContactViewer::BasicContactViewer(const LinQedInUser& us,QWidget* parent):QFrame(parent),user(us){
    setFrameShape(QFrame::Box);
    setStyleSheet("QFrame, QFrame * {font:15px;background:"+GUIStyle::lightGold()+";font-weight:bold;}"+
                  GUIStyle::popupButtonStyle());
    mainVerticalLayout=new QVBoxLayout;
    name=new QLabel(user.getProfile().getPersonalInformations().getName()+' '+
                    user.getProfile().getPersonalInformations().getSurname(),this);
    mainVerticalLayout->addWidget(name,0,Qt::AlignTop | Qt::AlignCenter);
    email=new QLabel(user.getLoginInfo().getEmailAddress(),this);
    mainVerticalLayout->addWidget(email,0,Qt::AlignTop | Qt::AlignCenter);
    try{
        const Occupations& o=dynamic_cast<const Occupations&>(us.getProfile().getInformationsBySectionName(Occupations::getIDString()));
        actualJob=new QLabel(o.getActualJob().getCompany()+" come "+o.getActualJob().getEmployment(),this);
    }catch(const NoInfoException&){actualJob=new QLabel(tr("Nessuna informazione sul lavoro"),this);}

    mainVerticalLayout->addWidget(actualJob,0,Qt::AlignTop | Qt::AlignCenter);

    ClientProfileWidget* cpw=dynamic_cast<ClientProfileWidget*>(parent);
    buttonsLayout=new QHBoxLayout;
    viewProfile=new QPushButton("Visualizza profilo");
    viewProfile->setCursor(QCursor(Qt::PointingHandCursor));
    if(cpw && ((!cpw->equals && cpw->client->getPermits().getVisibleInfos()) || cpw->equals))
        buttonsLayout->addWidget(viewProfile);

    removeContact=new QPushButton("Rimuovi contatto");
    removeContact->setCursor(QCursor(Qt::PointingHandCursor));
    addContact=new QPushButton("Aggiungi Contatto");
    addContact->setCursor(QCursor(Qt::PointingHandCursor));
    if(cpw->client->getLoginInfo().getEmailAddress()!=user.getLoginInfo().getEmailAddress()){
        if(cpw && cpw->client->getContactsNetwork().findUser(user.getLoginInfo().getEmailAddress())){
            buttonsLayout->addWidget(removeContact);
            addContact->setVisible(false);
        }//if
        else{
            buttonsLayout->addWidget(addContact);
            removeContact->setVisible(false);
        }//else
    }//if
    mainVerticalLayout->addLayout(buttonsLayout);
    setLayout(mainVerticalLayout);
    connect(removeContact,SIGNAL(clicked()),this,SLOT(sendRemovalRequest()));
    connect(viewProfile,SIGNAL(clicked()),this,SLOT(sendViewRequest()));
    connect(addContact,SIGNAL(clicked()),this,SLOT(sendAddingRequest()));
}//BasicContactViewer

void BasicContactViewer::leaveEvent(QEvent*){close();}

void BasicContactViewer::sendRemovalRequest() const{emit removalRequest(user.getLoginInfo().getEmailAddress());}

void BasicContactViewer::sendViewRequest() const{emit viewRequest(user);}

void BasicContactViewer::sendAddingRequest() const{emit addingRequest(user.getLoginInfo().getEmailAddress());}
