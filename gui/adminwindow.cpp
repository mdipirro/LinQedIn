#include "adminwindow.h"
#include "adminmainwidget.h"
#include "userinsertionwidget.h"
#include "guistyle.h"
#include "loginwindow.h"
#include "exceptions/exception.h"
#include <QTabWidget>
#include <QShortcut>
#include <QMessageBox>
#include <QCloseEvent>

AdminWindow::AdminWindow(QWidget* parent):QMainWindow(parent){
    setAttribute(Qt::WA_DeleteOnClose,true);
    setStyleSheet(GUIStyle::popupStyle());
    setWindowIcon(QIcon(GUIStyle::iconPath()));
    tabPane=new QTabWidget;
    tabPane->setTabsClosable(true);
    connect(tabPane,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));

    amw=new AdminMainWidget(&admin,this);
    connect(amw,SIGNAL(addUserSignal()),this,SLOT(addUser()));
    connect(amw,SIGNAL(logoutSignal()),this,SLOT(logout()));
    tabPane->setCurrentIndex(tabPane->addTab(amw,tr("Pannello Principale")));

    setCentralWidget(tabPane);

    QShortcut *quit=new QShortcut(QKeySequence("Ctrl+Q"),this),
            *ins=new QShortcut(QKeySequence("Ctrl+I"),this);
    connect(quit,SIGNAL(activated()),this,SLOT(logout()));
    connect(ins,SIGNAL(activated()),this,SLOT(addUser()));
}//AdminWindow

void AdminWindow::addUser(){
    UserInsertionWidget* uiw=new UserInsertionWidget(this);
    tabPane->setCurrentIndex(tabPane->addTab(uiw,tr("Inserisci utente")));
    connect(uiw,SIGNAL(insertion(QString,QString,QString,int,Personal::Genders)),this,
            SLOT(insertUser(QString,QString,QString,int,Personal::Genders)));
    connect(uiw,SIGNAL(closeSignal(int)),this,SLOT(closeTab(int)));
}//addUser

void AdminWindow::insertUser(const QString& name,const QString& surname,const QString& email,int plan,Personal::Genders gender){
    try{
        admin.insertInDB(name,surname,email,plan,gender);
        tabPane->removeTab(tabPane->currentIndex());
        AdminMainWidget* amw=dynamic_cast<AdminMainWidget*>(tabPane->widget(0));
        if(amw) amw->populateList(admin.allUsers());
    }catch(const Exception& exc){
        QMessageBox msg(this);
        msg.setWindowIcon(QIcon(GUIStyle::iconPath()));
        msg.setText(exc.what());
        msg.exec();
    }//catch
}//insertUser

void AdminWindow::closeTab(int index) const{
    if(index!=tabPane->indexOf(amw)){
        if(index>-1) tabPane->removeTab(index);
        else tabPane->removeTab(tabPane->currentIndex());
    }//if
}//closeTab

void AdminWindow::logout(){
    if(close()) (new LoginWindow)->show();
}//logout

void AdminWindow::closeEvent(QCloseEvent* event){
    if(admin.dbChanged()){
        QMessageBox::StandardButton btn=QMessageBox::question(this,"LinQedIn",
                                                                   tr("Database modificato. Salvare prima di uscire?\n"),
                                                                   QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                   QMessageBox::Yes);
        if (btn==QMessageBox::Yes){admin.saveDB(); event->accept();}
        else if (btn==QMessageBox::No) event->accept();
        else event->ignore();
    }//if
}//closeEvent
