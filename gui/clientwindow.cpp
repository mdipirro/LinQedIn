#include "clientwindow.h"
#include "loginwindow.h"
#include "clientprofilewidget.h"
#include "guistyle.h"
#include "editinformations/editpersonalinfoswidget.h"
#include "editinformations/editstudiesinfoswidget.h"
#include "editinformations/editoccupationsinfoswidget.h"
#include "editinformations/editlogininformations.h"
#include "search/namesurnamesearchwidget.h"
#include "search/usernamesearchwidget.h"
#include "user/profileinformations/information.h"
#include "user/research/permissions.h"
#include "exceptions/invalidimageexception.h"
#include "exceptions/exception.h"
#include "controller/linqedinclient.h"
#include "controller/linqedinuser.h"
#include <QTabWidget>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QShortcut>
#include <QDate>

int ClientWindow::tabTypes=5;
int ClientWindow::maxWidth=1250;
int ClientWindow::maxHeight=600;

ClientWindow::Tab::Tab(bool open,short tabI):isOpen(open),tabIndex(tabI){}

ClientWindow::ClientWindow(LinQedInClient* cl,QMainWindow* parent):QMainWindow(parent),openTabs(QVector<Tab>(tabTypes+1,Tab())),client(cl){
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowIcon(QIcon(GUIStyle::iconPath()));
    tabPane=new QTabWidget;
    tabPane->setTabsClosable(true);
    connect(tabPane,SIGNAL(tabCloseRequested(int)),this,SLOT(tabClosing(int)));

    cpw=new ClientProfileWidget(client);
    tabPane->addTab(cpw,tr("Profilo Personale"));
    setCentralWidget(tabPane);
    createActions();
    createMenus();
    setMinimumSize(maxWidth,maxHeight);

    QShortcut *quit=new QShortcut(QKeySequence("Ctrl+Q"),this);
    connect(quit,SIGNAL(activated()),this,SLOT(logout()));
}//ClientWindow

ClientWindow::~ClientWindow(){delete client;}

void ClientWindow::createActions(){
    editPersonal=new QAction(tr("Modifica Profilo"),this);
    editPersonal->setShortcut(QKeySequence("Ctrl+P"));
    connect(editPersonal,SIGNAL(triggered()),this,SLOT(editPersonalInformations()));

    editImage=new QAction(tr("Modifica l'immagine di profilo"),this);
    editImage->setShortcut(QKeySequence("Ctrl+I"));
    connect(editImage,SIGNAL(triggered()),this,SLOT(editProfileImage()));

    editStudies=new QAction(tr("Modifica Titoli di Studio"),this);
    editStudies->setShortcut(QKeySequence("Ctrl+S"));
    connect(editStudies,SIGNAL(triggered()),this,SLOT(editStudiesInformations()));

    editOccupations=new QAction(tr("Modifica Esperienze Lavorative"),this);
    editOccupations->setShortcut(QKeySequence("Ctrl+O"));
    connect(editOccupations,SIGNAL(triggered()),this,SLOT(editOccupationalInformations()));

    editLogin=new QAction(tr("Modifica informazioni di accesso"),this);
    editLogin->setShortcut(QKeySequence("Ctrl+L"));
    connect(editLogin,SIGNAL(triggered()),this,SLOT(editLoginInfo()));

    searchByUsernameA=new QAction(tr("Cerca per username"),this);
    searchByUsernameA->setShortcut(QKeySequence("Ctrl+U"));
    connect(searchByUsernameA,SIGNAL(triggered()),this,SLOT(searchByUsername()));

    searchByNameA=new QAction(tr("Cerca per nome e cognome"),this);
    searchByNameA->setShortcut(QKeySequence("Ctrl+N"));
    connect(searchByNameA,SIGNAL(triggered()),this,SLOT(searchByName()));

    aboutA=new QAction(tr("Informazioni su LinQedIn"),this);
    aboutA->setShortcut(QKeySequence("Ctrl+A"));
    connect(aboutA,SIGNAL(triggered()),this,SLOT(about()));

    logoutA=new QAction(tr("Logout"),this);
    connect(logoutA,SIGNAL(triggered()),this,SLOT(logout()));

    subscriptionA=new QAction(tr("Informazioni sull'abbonamento"),this);
    subscriptionA->setShortcut(QKeySequence("Ctrl+T"));
    connect(subscriptionA,SIGNAL(triggered()),this,SLOT(subscription()));
}//createActions

void ClientWindow::createMenus(){
    menuBar()->setStyleSheet("QMenu{color:white;background-color:"+GUIStyle::brown()+";border:1px solid black;}"
                           "QMenu::item{background-color:transparent;}"
                           "QMenu::item:selected{color:black;background-color:"+GUIStyle::lightGold()+";}");
    editMenu=menuBar()->addMenu("Modifica");
    editMenu->addAction(editImage);
    editMenu->addAction(editPersonal);
    editMenu->addAction(editStudies);
    editMenu->addAction(editOccupations);
    editMenu->addAction(editLogin);

    searchMenu=menuBar()->addMenu("Cerca");
    searchMenu->addAction(searchByNameA);
    if(client->getPermits().username()) searchMenu->addAction(searchByUsernameA);

    menuBar()->addAction(logoutA);
    menuBar()->addAction(subscriptionA);
    menuBar()->addAction(aboutA);
}//createMenus

void ClientWindow::repaintCPW(){
    tabClosing(tabPane->currentIndex());
    cpw->setupGui();
}//repaintCPW

void ClientWindow::paintProfile(const LinQedInUser& user) const{
    tabPane->setCurrentIndex(tabPane->addTab(new ClientProfileWidget(client,new LinQedInUser(user)),
                                             tr("Profilo Personale")));
}//paintProfile

void ClientWindow::updateProfile(const Profile& prof){
    client->updateProfile(prof);
    repaintCPW();
}//updateProfile

void ClientWindow::editProfileImage(){
    QString fileName=QFileDialog::getOpenFileName(this,tr("Scegli l'immagine"),QDir::currentPath(),"Immagini (*.png *.jpg)");
    try{cpw->changeUserImage(fileName); cpw->setupGui();}
    catch(const InvalidImageException& exc){
        QMessageBox::information(this,tr("LinQedIn"),fileName+": "+exc.what());
    }//catch
}//editProfileImage

void ClientWindow::editPersonalInformations(){
    if(!openTabs[Tab::editPersonalsTab].isOpen){
        EditPersonalInfosWidget* epiw=new EditPersonalInfosWidget(this,client);
        tabPane->setCurrentIndex(tabPane->addTab(epiw,tr("Modifica Profilo")));
        openTabs[Tab::editPersonalsTab].isOpen=true;
        openTabs[Tab::editPersonalsTab].tabIndex=tabPane->currentIndex();
        connect(epiw,SIGNAL(cancelled()),this,SLOT(repaintCPW()));
        connect(epiw,SIGNAL(save(Profile)),this,SLOT(updateProfile(Profile)));
    }//if
    else tabPane->setCurrentIndex(openTabs[Tab::editPersonalsTab].tabIndex);
}//editPersonalInformations

void ClientWindow::editStudiesInformations(){
    if(!openTabs[Tab::editStudiesTab].isOpen){
        EditStudiesInfosWidget* esiw=new EditStudiesInfosWidget(client,this);
        tabPane->setCurrentIndex(tabPane->addTab(esiw,tr("Modifica Titoli di Studio")));
        openTabs[Tab::editStudiesTab].isOpen=true;
        openTabs[Tab::editStudiesTab].tabIndex=tabPane->currentIndex();
        connect(esiw,SIGNAL(cancelled()),this,SLOT(repaintCPW()));
        connect(esiw,SIGNAL(save(Profile)),this,SLOT(updateProfile(Profile)));
    }//if
    else tabPane->setCurrentIndex(openTabs[Tab::editStudiesTab].tabIndex);
}//editStudiesInformations

void ClientWindow::editOccupationalInformations(){
    if(!openTabs[Tab::editOccupationsTab].isOpen){
        EditOccupationsInfosWidget* eoiw=new EditOccupationsInfosWidget(client,this);
        tabPane->setCurrentIndex(tabPane->addTab(eoiw,tr("Modifica Esperienze Lavorative")));
        openTabs[Tab::editOccupationsTab].isOpen=true;
        openTabs[Tab::editOccupationsTab].tabIndex=tabPane->currentIndex();
        connect(eoiw,SIGNAL(cancelled()),this,SLOT(repaintCPW()));
        connect(eoiw,SIGNAL(save(Profile)),this,SLOT(updateProfile(Profile)));
    }//if
    else tabPane->setCurrentIndex(openTabs[Tab::editOccupationsTab].tabIndex);
}//editOccupationalInformations

void ClientWindow::editLoginInfo(){
    if(!openTabs[Tab::editLoginTab].isOpen){
        EditLoginInformations* eoiw=new EditLoginInformations(client->getLoginInfo(),this);
        tabPane->setCurrentIndex(tabPane->addTab(eoiw,tr("Modifica Informazioni di Accesso")));
        openTabs[Tab::editLoginTab].isOpen=true;
        openTabs[Tab::editLoginTab].tabIndex=tabPane->currentIndex();
        connect(eoiw,SIGNAL(cancelled()),this,SLOT(repaintCPW()));
        connect(eoiw,SIGNAL(save(UserData)),this,SLOT(updateLogin(UserData)));
    }//if
    else tabPane->setCurrentIndex(openTabs[Tab::editLoginTab].tabIndex);
}//editOccupationalInformations

void ClientWindow::about(){
    QMessageBox msg(this);
    msg.setWindowIcon(QIcon(GUIStyle::iconPath()));
    msg.setStyleSheet(GUIStyle::popupStyle());
    msg.setText("LinQed in è una grande rete sociale con moltissimi membri in svariati Paesi."
                " La nostra missione è semplice: collegare i professionisti nel mondo per aumentare la loro produttività "
                "e il loro successo.\nDopo esserti iscritto a LinQedIn, avrai accesso a persone, aggiornamenti e informazioni "
                "che ti aiuteranno a dare il massimo."
                );
    msg.exec();
}//about

void ClientWindow::searchByUsername(){
    if(!openTabs[Tab::searchByUsernameTab].isOpen){
        UsernameSearchWidget* usw=new UsernameSearchWidget(client);
        tabPane->setCurrentIndex(tabPane->addTab(usw,tr("Cerca per username")));
        usw->focus(); //altrimenti il focus è sull'etichetta della scheda
        openTabs[Tab::searchByUsernameTab].isOpen=true;
        openTabs[Tab::searchByUsernameTab].tabIndex=tabPane->currentIndex();
        connect(usw,SIGNAL(selectUser(LinQedInUser)),this,SLOT(paintProfile(LinQedInUser)));
        connect(usw,SIGNAL(networkOperationDone()),this,SLOT(networkOperation()));
    }//if
    else tabPane->setCurrentIndex(openTabs[Tab::searchByUsernameTab].tabIndex);
}//searchByUsername

void ClientWindow::searchByName(){
    if(!openTabs[Tab::searchByNameTab].isOpen){
        NameSurnameSearchWidget* nssw=new NameSurnameSearchWidget(client);
        tabPane->setCurrentIndex(tabPane->addTab(nssw,tr("Cerca per nome e cognome")));
        nssw->focus();
        openTabs[Tab::searchByNameTab].isOpen=true;
        openTabs[Tab::searchByNameTab].tabIndex=tabPane->currentIndex();
        connect(nssw,SIGNAL(selectUser(LinQedInUser)),this,SLOT(paintProfile(LinQedInUser)));
        connect(nssw,SIGNAL(networkOperationDone()),this,SLOT(networkOperation()));
    }//if
    else tabPane->setCurrentIndex(openTabs[Tab::searchByNameTab].tabIndex);
}//searchByName

void ClientWindow::tabClosing(int index){
    if(tabPane->indexOf(cpw)!=index){
        //cerco la scheda che è appena stata chiusa per mantenere coerente l'array
        bool found=false;
        int i=0;
        for(;i<tabTypes && !found;i++) found=(openTabs[i].tabIndex==tabPane->currentIndex());
        openTabs[i-1].isOpen=false;
        openTabs[i-1].tabIndex=-1;
        tabPane->removeTab(index);
    }//if
}//tabClosing

void ClientWindow::networkOperation()const{cpw->setupGui();}

void ClientWindow::logout(){
    (new LoginWindow)->show();
    close();
}//logout

void ClientWindow::updateLogin(const UserData& ud){
    try{
        client->updateLogin(ud);
        repaintCPW();
    }catch(const Exception& exc){
        QMessageBox msg(this);
        msg.setWindowIcon(QIcon(GUIStyle::iconPath()));
        msg.setStyleSheet(GUIStyle::popupStyle());
        msg.setText(exc.what());
        msg.exec();
    }//catch
}//updateLogin

void ClientWindow::subscription(){
    QMessageBox msg(this);
    msg.setWindowIcon(QIcon(GUIStyle::iconPath()));
    msg.setStyleSheet(GUIStyle::popupStyle());
    QDate date=client->getEspireDate();
    msg.setText(client->getUserPlan()+" con scadenza il: "+((date.isValid())?date.toString("dd/MM/yyyy"):"mai"));
    msg.exec();
}//subscription
