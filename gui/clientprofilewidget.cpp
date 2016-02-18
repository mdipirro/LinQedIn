#include "clientprofilewidget.h"
#include "basiccontactviewer.h"
#include "clientwindow.h"
#include "guistyle.h"
#include "controller/linqedinclient.h"
#include "controller/linqedinuser.h"
#include "user/profileinformations/personal.h"
#include "user/profileinformations/studies.h"
#include "user/profileinformations/occupations.h"
#include "user/profileinformations/job.h"
#include "user/research/searchbyusername.h"
#include "user/profile.h"
#include "user/userdata.h"
#include "exceptions/noinfoexception.h"
#include <QFile>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>
#include <QScrollArea>
#include <QListView>
#include <QVector>
#include <QStringListModel>
#include <QResizeEvent>
#include <QKeyEvent>

QString ClientProfileWidget::noInformations=tr("Nessuna Informazione");

ClientProfileWidget::ClientProfileWidget(LinQedInClient* c,LinQedInUser* u,QWidget* parent):
    QFrame(parent),client(c),user(u),basicViewer(0){
    setStyleSheet(GUIStyle::generalStyle());
    setAttribute(Qt::WA_DeleteOnClose,true);
    if(!user) user=new LinQedInUser(client->getLoginInfo().getEmailAddress());
    equals=client->getLoginInfo().getEmailAddress()==user->getLoginInfo().getEmailAddress();
    mainVerticalLayout=new QVBoxLayout;
    mainVerticalLayout->setContentsMargins(0,0,0,0);
    mainVerticalLayout->setSpacing(0);
    initPersonalInformations(); //informazioni personali
    initNetworkAndInfos();
    setLayout(mainVerticalLayout);
    setupGui();
}//ClientProfileWidget

void ClientProfileWidget::initPersonalInformations(){
    personal=new QHBoxLayout;
    //foto
    image=new QLabel;
    image->setScaledContents(true);
    image->resize(175,200);
    image->setMaximumSize(175,200);
    personal->addWidget(image,0,Qt::AlignTop | Qt::AlignLeft);

    personalInfosGroupBox=new QGroupBox;
    personalInfosGroupBox->setStyleSheet("border:none;font-size:20px;");
    gridLayout=new QGridLayout;
    name=new QLabel;
    name->setStyleSheet("font-weight:bold;");
    name->setMargin(20);
    gender=new QLabel(tr("Sesso:"));
    genderV=new QLabel;
    birthdate=new QLabel(tr("Data di nascita:"));
    birthdateV=new QLabel;
    birthplace=new QLabel(tr("Nato a:"));
    birthplaceV=new QLabel;
    email=new QLabel(tr("Indirizzo email:"));
    emailV=new QLabel;

    gridLayout->addWidget(name,0,0);
    gridLayout->addWidget(gender,1,0);
    gridLayout->addWidget(genderV,1,1);
    gridLayout->addWidget(birthdate,2,0);
    gridLayout->addWidget(birthdateV,2,1);
    gridLayout->addWidget(birthplace,3,0);
    gridLayout->addWidget(birthplaceV,3,1);
    gridLayout->addWidget(email,4,0);
    gridLayout->addWidget(emailV,4,1);
    gridLayout->setColumnStretch(0,2);
    gridLayout->setColumnStretch(1,8);
    gridLayout->setMargin(20);
    personalInfosGroupBox->setMaximumHeight(250);
    personalInfosGroupBox->setLayout(gridLayout);
    personal->addWidget(personalInfosGroupBox,0,Qt::AlignTop);
    personal->setStretch(0,2);
    personal->setStretch(1,8);

    logo=new QPushButton;
    GUIStyle::initLogo(logo);
    logo->setStyleSheet(logo->styleSheet()+"background:"+GUIStyle::lightBeige()+";");
    personal->addWidget(logo,0,Qt::AlignTop | Qt::AlignRight);
    connect(logo,SIGNAL(clicked()),this,SLOT(goHome()));

    mainVerticalLayout->addLayout(personal);
    mainVerticalLayout->setStretch(0,3);
}//initPersonalInformations

void ClientProfileWidget::initStudiesInformations(){
    studiesLayout=new QVBoxLayout();
    studies=new QLabel(Studies::getIDString(),this);
    studies->setStyleSheet("font-size:25px;font-weight:bold;color:"+GUIStyle::brown()+";");
    studiesLayout->addWidget(studies,0,Qt::AlignVCenter | Qt::AlignHCenter);
    highSchool=new QLabel;
    qualification=new QLabel;
    degree=new QLabel;
    degrees=new QListView;
    degreesModel=new QStringListModel;
    degrees->setModel(degreesModel);
    degrees->setEditTriggers(degrees->NoEditTriggers);
    degrees->setSelectionMode(QAbstractItemView::NoSelection);
    studiesLayout->addWidget(highSchool);
    studiesLayout->addWidget(qualification);
    studiesLayout->addWidget(degree,0,Qt::AlignCenter);
    studiesLayout->addWidget(degrees);
    scrollAreaLayout->addLayout(studiesLayout);
}//initStudiesInformations

void ClientProfileWidget::initOccupationsInformations(){
    occupationsLayout=new QVBoxLayout();
    occupations=new QLabel(Occupations::getIDString(),this);
    occupations->setStyleSheet("font-size:25px;font-weight:bold;margin-top:30px;margin-bottom:30px;color:"+GUIStyle::brown()+";");
    occupationsLayout->addWidget(occupations,0,Qt::AlignCenter);
    jobs=new QListView;
    jobsModel=new QStringListModel;
    jobs->setModel(jobsModel);
    jobs->setEditTriggers(jobs->NoEditTriggers);
    jobs->setSelectionMode(QAbstractItemView::NoSelection);
    occupationsLayout->addWidget(jobs,0,Qt::AlignTop);
    scrollAreaLayout->addLayout(occupationsLayout);
}//initOccuptionalInformation

void ClientProfileWidget::initNetworkAndInfos(){
    horizontalLayout=new QHBoxLayout;
    scrollArea=new QScrollArea;
    scrollAreaWidget=new QWidget;
    scrollAreaLayout=new QVBoxLayout;

    //Rete di contatti
    contactsWidget=new QWidget;
    contactsWidget->setStyleSheet(GUIStyle::borderStyle());
    contactsLayout=new QVBoxLayout;
    contactsL=new QLabel; contactsL->setStyleSheet("border:none;");
    contactsL->setMaximumSize(100,50);
    contactsL->resize(100,50);
    contactsLayout->addWidget(contactsL,0,Qt::AlignTop | Qt::AlignCenter);
    contacts=new QListView;
    contactsModel=new QStringListModel;
    contacts->setModel(contactsModel);
    contacts->setEditTriggers(contacts->NoEditTriggers);
    contacts->setSelectionMode(QAbstractItemView::NoSelection);
    contacts->setStyleSheet("font-size:17px;border:none;margin-top:20px;color:black;");
    contacts->setCursor(QCursor(Qt::PointingHandCursor));
    contactsLayout->addWidget(contacts,8,Qt::AlignTop);
    contactsWidget->setLayout(contactsLayout);
    horizontalLayout->addWidget(contactsWidget);
    connect(contacts,SIGNAL(clicked(QModelIndex)),this,SLOT(viewContactProfile(QModelIndex)));

    //Informazioni Profilo
    initStudiesInformations(); //informazioni di studio
    initOccupationsInformations(); //informazioni di lavoro
    scrollAreaWidget->setLayout(scrollAreaLayout);
    scrollAreaWidget->setObjectName("scrollArea");
    scrollAreaWidget->setStyleSheet("#scrollArea{"+GUIStyle::borderStyle()+"} #scrollArea,#scrollArea * {font-size:17px;color:black;}");
    scrollAreaWidget->setContentsMargins(10,0,10,26);
    scrollArea->setWidget(scrollAreaWidget);
    scrollArea->setStyleSheet("border:none;");
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    horizontalLayout->addWidget(scrollArea,8,Qt::AlignCenter);
    mainVerticalLayout->addLayout(horizontalLayout);
}//initNetworkAndInfos

void ClientProfileWidget::resizeEvent(QResizeEvent* e){
    //calcolo l'altezza totale degli elementi della lista dei contatti
    int h=20; for(int r=0;r<contactsModel->rowCount();r++) h+=contacts->visualRect(contactsModel->index(r,0)).height();
    contacts->resize(contacts->width(),h);
    contacts->setMaximumHeight(h+contactsModel->rowCount()*2);
    contacts->setMinimumHeight(h);
    //calcolo l'altezza totale degli elementi della lista dei lavori
    h=25; for(int r=0;r<jobsModel->rowCount();r++) h+=jobs->visualRect(jobsModel->index(r,0)).height();
    scrollArea->setMinimumSize(850,2*e->size().height()/3);
    scrollAreaWidget->setMinimumSize(850,2*e->size().height()/3);
}//resizeEvent

void ClientProfileWidget::keyReleaseEvent(QKeyEvent* e){
    if(e->key()==Qt::Key_Backspace) goHome();
}//keyReleaseEvent

void ClientProfileWidget::viewContactProfile(const QModelIndex& index){
    QVector<LinQedInUser> con=user->getContactsList();
    bool e=false;
    if(basicViewer){
        e=user->getLoginInfo().getEmailAddress()==(*(con.begin()+index.row())).getLoginInfo().getEmailAddress();
        basicViewer->close();
    }//if

    if(e && basicViewer->isVisible()) basicViewer=0;
    else{
        basicViewer=new BasicContactViewer(*(con.begin()+index.row()),const_cast<ClientProfileWidget*>(this));
        basicViewer->setGeometry(125,mapFromGlobal(QCursor::pos()).y(),320,150);
        basicViewer->show();
        connect(basicViewer,SIGNAL(removalRequest(QString)),this,SLOT(removeFromNetwork(QString)));
        connect(basicViewer,SIGNAL(viewRequest(LinQedInUser)),this,SLOT(viewUserProfile(LinQedInUser)));
        connect(basicViewer,SIGNAL(addingRequest(QString)),this,SLOT(addInNetwork(QString)));
    }//else
}//viewContactProfile

void ClientProfileWidget::removeFromNetwork(const QString& username) const{
    client->removeFromContactsNetwork(username);
    QStringList list;
    foreach(LinQedInUser us,user->getContactsList()) list<<us.getProfile().getPersonalInformations().getName()+' '+
                                                            us.getProfile().getPersonalInformations().getSurname();
    contactsModel->setStringList(list);
}//removeFromNetwork

void ClientProfileWidget::viewUserProfile(const LinQedInUser& other){
    if(basicViewer) basicViewer->close();
    *user=other;
    equals=(client->getLoginInfo().getEmailAddress()==user->getLoginInfo().getEmailAddress());
    setupGui();
    resize(width(),height());
}//viewUserProfile

void ClientProfileWidget::goHome(){if(!equals) viewUserProfile(LinQedInUser(client->getLoginInfo().getEmailAddress()));}

void ClientProfileWidget::addInNetwork(const QString& username) const{
    client->addToContactsNetwork(username);
}//addInNetwork

void ClientProfileWidget::setupGui() const{
    image->setPixmap(QPixmap(user->getImagePath()));

    //personali
    const Personal* pInfos=&user->getProfile().getPersonalInformations();
    if(pInfos){
        name->setText(pInfos->getName()+" "+pInfos->getSurname());
        genderV->setText(QString(QChar(pInfos->getGender())));
        birthdateV->setText((pInfos->getBirthdate().isNull())?"Nessuna informazione sulla data di nascita":pInfos->getBirthdate().toString("d/M/yyyy"));
        birthplaceV->setText(((pInfos->getBirthplace()=="")?"Nessuna informazione sul luogo di nascita"
                               :(pInfos->getBirthplace())+" ("+((pInfos->getBirthState()=="")?
                                 "Nessuna informazione sullo stato di nascita"
                                 :(pInfos->getBirthState())+")")));
        emailV->setText(user->getLoginInfo().getEmailAddress());
    }//if

    //studio
    QStringList list;
    try{
        const Studies& s=dynamic_cast<const Studies&>(user->getProfile().getInformationsBySectionName(Studies::getIDString()));
        highSchool->setText("<span style='color:"+GUIStyle::brown()+";'>"+tr("Scuola Superiore")+"</span> "+s.getHighSchool());
        qualification->setText("<span style='color:"+GUIStyle::brown()+";'>"+tr("Qualifica Professionale ")+"</span> "+
                               "<b>"+s.getQualification()+"</b>");
        degree->setText("<span style='color:"+GUIStyle::brown()+";'>"+tr("Lauree:")+"</span> "+
                        ((s.getDegrees().size()==0)?tr(" Nessuna laurea."):""));
        foreach(Degree deg,s.getDegrees()) list<<"-) "+deg.toString();
    }catch(const NoInfoException&){
        highSchool->setText("<span style='color:"+GUIStyle::brown()+";'>"+tr("Scuola Superiore")+"</span> "+noInformations);
        qualification->setText("<span style='color:"+GUIStyle::brown()+";'>"+tr("Qualifica Professionale ")+"</span> "+
                               "<b>"+noInformations+"</b>");
        degree->setText("<span style='color:"+GUIStyle::brown()+";'>"+tr("Lauree:")+"</span> ");
        list<<noInformations;
    }//catch
    degreesModel->setStringList(list);

    //lavoro
    list.clear();
    try{
        const Occupations& o=dynamic_cast<const Occupations&>(user->getProfile().getInformationsBySectionName(Occupations::getIDString()));
        foreach(QString job,o.getInformationList(true)) list<<"-) "+job;
    }catch(const NoInfoException&){list<<noInformations;}
    jobsModel->setStringList(list);

    //contatti
    contactsL->setText("<span style=\"font-size:25px;font-weight:bold;margin-bottom:50px;\">Contatti</span>");
    if(equals || client->getPermits().getVisibleNetwork()){
        QStringList list;
        foreach(LinQedInUser us,user->getContactsList()) list<<us.getProfile().getPersonalInformations().getName()+' '+
                                                                us.getProfile().getPersonalInformations().getSurname();
        contactsModel->setStringList(list);
        int h=20; for(int r=0;r<contactsModel->rowCount();r++) h+=contacts->visualRect(contactsModel->index(r,0)).height();
        contacts->resize(contacts->width(),h);
        contacts->setMaximumHeight(h+contactsModel->rowCount()*2);
        contacts->setMinimumHeight(h);
    }//if
    else{
        contactsL->setText(QString("<span style=\"font-size:25px;font-weight:bold;margin-bottom:50px;\">Contatti</span><br/>")+
                            "<br/><br/><br/><br/>"+
                           "<span style=\"font-size:15px;\">Non hai il permesso di vedere i<br/> contatti di questo utente.</span>");
        contactsL->setMaximumSize(250,150);
        contactsL->resize(250,150);
        contactsModel->removeRows(0,contactsModel->rowCount());
    }//else

    image->setFocus();
}//setupGui

void ClientProfileWidget::changeUserImage(const QString& path) const{client->setImagePath(path);}
