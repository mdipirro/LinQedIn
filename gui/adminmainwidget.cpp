#include "adminmainwidget.h"
#include "adminwindow.h"
#include "basicuserviewer.h"
#include "guistyle.h"
#include "controller/linqedinadmin.h"
#include "controller/linqedinuser.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QSpacerItem>
#include <QShortcut>
#include <QPixmap>
#include <QString>

int AdminMainWidget::buttonsMaxWidth=250;

AdminMainWidget::AdminMainWidget(LinQedInAdmin* ad,QWidget* parent):QFrame(parent),admin(ad){
    setAttribute(Qt::WA_DeleteOnClose);
    setStyleSheet(GUIStyle::generalStyle());
    mainVerticalLayout=new QVBoxLayout;

    logo=new QLabel;
    GUIStyle::initLogo(logo);
    mainVerticalLayout->addWidget(logo,0,Qt::AlignRight);

    loggedAsAdmin=new QLabel(tr("Modalità amministratore"));
    loggedAsAdmin->setStyleSheet(GUIStyle::headerStyle());
    mainVerticalLayout->addWidget(loggedAsAdmin,0,Qt::AlignCenter);
    mainVerticalLayout->addSpacing(15);

    searchLayout=new QHBoxLayout;
    initUsernameSearch();
    users=new QListWidget;
    users->setHidden(true);
    users->setEditTriggers(users->NoEditTriggers);
    users->setSelectionMode(QAbstractItemView::NoSelection);
    users->setMinimumWidth(450);
    users->setMinimumHeight(430);
    users->setStyleSheet("QListWidget{"+GUIStyle::borderStyle()+"padding:20px;padding-top:5px;}");
    searchLayout->addWidget(users,5,Qt::AlignHCenter | Qt::AlignTop);
    initNameSurnameSearch();
    mainVerticalLayout->addLayout(searchLayout);

    noUsers=new QLabel(tr("Nessun utente nel DB"));
    noUsers->setStyleSheet(GUIStyle::errorLabelStyle());
    mainVerticalLayout->addWidget(noUsers,0,Qt::AlignCenter);

    buttonsLayout=new QHBoxLayout;
    save=new QPushButton(tr("Salva modifiche al DB"));
    save->setCursor(QCursor(Qt::PointingHandCursor));
    save->setMaximumWidth(buttonsMaxWidth);
    connect(save,SIGNAL(clicked()),this,SLOT(saveDB()));
    buttonsLayout->addWidget(save,0,Qt::AlignCenter);
    add=new QPushButton(tr("Aggiungi un nuovo utente"));
    add->setCursor(QCursor(Qt::PointingHandCursor));
    add->setMaximumWidth(buttonsMaxWidth);
    connect(add,SIGNAL(clicked()),this,SLOT(addUserRequest()));
    buttonsLayout->addWidget(add,0,Qt::AlignCenter);
    logout=new QPushButton(tr("Logout"));
    logout->setCursor(QCursor(Qt::PointingHandCursor));
    connect(logout,SIGNAL(clicked()),this,SLOT(logoutRequest()));
    logout->setMaximumWidth(buttonsMaxWidth);
    buttonsLayout->addWidget(logout,0,Qt::AlignCenter);
    mainVerticalLayout->addLayout(buttonsLayout);

    populateList(admin->allUsers());
    setLayout(mainVerticalLayout);

    QShortcut *save=new QShortcut(QKeySequence("Ctrl+S"),this);
    connect(save,SIGNAL(activated()),this,SLOT(saveDB()));
}//AdminMainWidget

void AdminMainWidget::initUsernameSearch(){
    QGroupBox* groupBox=new QGroupBox(tr("Ricerca per username:"));
    groupBox->setStyleSheet("QGroupBox{"+GUIStyle::formBorderStyle()+"margin-left:100px;}");
    groupBox->setMaximumWidth(300);
    groupBox->setMaximumHeight(150);
    searchULayout=new QFormLayout;
    searchULayout->addItem(new QSpacerItem(100,15));
    username=new QLineEdit;
    username->setPlaceholderText("Username");
    searchULayout->addRow(tr("Username"),username);
    searchULayout->addItem(new QSpacerItem(100,20));
    searchU=new QPushButton(tr("Cerca"));
    searchU->setCursor(QCursor(Qt::PointingHandCursor));
    connect(searchU,SIGNAL(clicked()),this,SLOT(usernameSearch()));
    connect(username,SIGNAL(returnPressed()),this,SLOT(usernameSearch()));
    searchULayout->addWidget(searchU);
    groupBox->setLayout(searchULayout);
    searchLayout->addWidget(groupBox);
}//initUsernameSearch

void AdminMainWidget::initNameSurnameSearch(){
    QGroupBox* groupBox=new QGroupBox(tr("Ricerca per nome e cognome:"));
    groupBox->setStyleSheet("QGroupBox{"+GUIStyle::formBorderStyle()+"margin-right:100px;} ");
    groupBox->setMaximumWidth(300);
    groupBox->setMaximumHeight(170);
    searchNSLayout=new QFormLayout;
    searchNSLayout->addItem(new QSpacerItem(100,15));
    name=new QLineEdit;
    name->setPlaceholderText(tr("Nome"));
    searchNSLayout->addRow(tr("Nome"),name);
    surname=new QLineEdit;
    surname->setPlaceholderText(tr("Cognome"));
    searchNSLayout->addRow(tr("Cognome"),surname);
    searchNSLayout->addItem(new QSpacerItem(100,10));
    searchNS=new QPushButton(tr("Cerca"));
    searchNS->setCursor(QCursor(Qt::PointingHandCursor));
    searchNSLayout->addWidget(searchNS);
    connect(searchNS,SIGNAL(clicked()),this,SLOT(nameSearch()));
    connect(name,SIGNAL(returnPressed()),this,SLOT(nameSearch()));
    connect(surname,SIGNAL(returnPressed()),this,SLOT(nameSearch()));
    groupBox->setLayout(searchNSLayout);
    searchLayout->addWidget(groupBox);
}//initNameSurnameSearch

void AdminMainWidget::populateList(const QVector<LinQedInUser>& results) const{
    users->clear();
    int height=0;
    foreach(LinQedInUser user,results){
        QListWidgetItem* item=new QListWidgetItem;
        BasicUserViewer* buv=new BasicUserViewer(user,dynamic_cast<QWidget*>(parent()));
        connect(buv,SIGNAL(deleteRequest(QString)),this,SLOT(deleteUser(QString)));
        connect(buv,SIGNAL(changePlanRequest(const QString&,int)),this,SLOT(changePlan(const QString&,int)));
        item->setSizeHint(buv->size());
        buv->setStyleSheet("BasicUserViewer{border-bottom:2px solid black;}");
        users->addItem(item);
        users->setItemWidget(item,buv);
        height+=buv->height();
    }//foreach
    users->setVisible(height>0); noUsers->setHidden(height>0);
}//populateList

void AdminMainWidget::addUserRequest() const{emit addUserSignal();}

void AdminMainWidget::logoutRequest() const{emit logoutSignal();}

void AdminMainWidget::deleteUser(const QString& username) const{
    admin->removeFromDB(username);
    populateList(admin->allUsers());
}//deleteUser

void AdminMainWidget::changePlan(const QString& username,int plan) const{
    admin->changeUserPlan(username,plan);
    populateList(admin->allUsers());
}//changePlan

void AdminMainWidget::saveDB() const{
    admin->saveDB();
    QMessageBox msg;
    msg.setText(tr("Le modifiche al database sono state salvate con successo!"));
    msg.setWindowIcon(QIcon(GUIStyle::iconPath()));
    msg.setStyleSheet("QMessageBox{background:"+GUIStyle::lightGold()+";font-size:13px;}"+
                      GUIStyle::popupButtonStyle());
    msg.exec();
}//saveDB

void AdminMainWidget::usernameSearch() const{
    if(username->text()=="*" || username->text()=="") populateList(admin->allUsers());
    else populateList(admin->searchByUsername(username->text().trimmed()));
}//usernameSearch

void AdminMainWidget::nameSearch() const{
    if(name->text()=="" && surname->text()!="") populateList(admin->searchBySurname(surname->text().trimmed()));
    else if(name->text()!="" && surname->text()=="") populateList(admin->searchByName(name->text().trimmed()));
    else if(name->text()!="" && surname->text()!="") populateList(admin->searchByNameSurname(name->text().trimmed(),surname->text().trimmed()));
    else populateList(admin->allUsers());
}//nameSearch
