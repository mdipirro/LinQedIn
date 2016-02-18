#include "loginwindow.h"
#include "adminwindow.h"
#include "guistyle.h"
#include "controller/linqedinclient.h"
#include "exceptions/nouserexception.h"
#include "user/userdata.h"
#include "clientwindow.h"
#include <QLabel>
#include <QFormLayout>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QMainWindow>
#include <QShortcut>

void LoginWindow::login(){
    try{
        lError->setHidden(true);
        (new ClientWindow(new LinQedInClient(UserData(teUsername->text(),tePwd->text()))))->showMaximized();
        close();
    }//try
    catch(const NoUserException& exc){
        lError->setHidden(false);
        lError->setText(exc.what());
    }//catch
}//login

void LoginWindow::admin(){
    (new AdminWindow)->showMaximized();
    close();
}//admin

LoginWindow::LoginWindow(QWidget* parent):QFrame(parent){
    setAttribute(Qt::WA_DeleteOnClose,true);
    setStyleSheet(GUIStyle::generalStyle()+"QLabel{font-weight:bold;} QPushButton{font-weight:bold;}");
    setWindowIcon(QIcon(GUIStyle::iconPath()));
    setMinimumSize(800,450);
    setMaximumSize(800,450);
    mainVerticalLayout=new QVBoxLayout();
    //immagine
    lImage=new QLabel;
    GUIStyle::initLogo(lImage,785,250);
    mainVerticalLayout->addWidget(lImage,0,Qt::AlignHCenter);

    //form di login
    loginLayout=new QHBoxLayout();
    loginLayout->setContentsMargins(0,50,0,10);
    //username
    vlUsername=new QVBoxLayout();
    lUsername=new QLabel("Username");
    lUsername->setAlignment(Qt::AlignCenter);
    vlUsername->addWidget(lUsername,0,Qt::AlignHCenter|Qt::AlignVCenter);
    teUsername=new QLineEdit;
    vlUsername->addWidget(teUsername,0,Qt::AlignHCenter|Qt::AlignVCenter);
    loginLayout->addLayout(vlUsername);
    //password
    vlPwd=new QVBoxLayout();
    lPwd=new QLabel("Password:");
    lPwd->setAlignment(Qt::AlignCenter);
    vlPwd->addWidget(lPwd,0,Qt::AlignHCenter|Qt::AlignVCenter);
    tePwd=new QLineEdit;
    tePwd->setEchoMode(QLineEdit::Password);
    vlPwd->addWidget(tePwd,0,Qt::AlignHCenter|Qt::AlignVCenter);
    loginLayout->addLayout(vlPwd);
    mainVerticalLayout->addLayout(loginLayout);
    loginButton=new QPushButton("Login");
    loginButton->setCursor(QCursor(Qt::PointingHandCursor));
    mainVerticalLayout->addWidget(loginButton,0,Qt::AlignHCenter|Qt::AlignVCenter);
    //etichetta errore
    lError=new QLabel;
    lError->setHidden(true);
    lError->setAlignment(Qt::AlignCenter);
    lError->resize(150,25);
    lError->setStyleSheet(GUIStyle::errorLabelStyle());
    mainVerticalLayout->addWidget(lError,0,Qt::AlignHCenter|Qt::AlignVCenter);
    //login come admin
    adminButton=new QPushButton("Login come Admin");
    adminButton->setCursor(QCursor(Qt::PointingHandCursor));
    adminButton->setFlat(true);
    mainVerticalLayout->addWidget(adminButton,0,Qt::AlignRight);
    setLayout(mainVerticalLayout);
    setWindowTitle("LinQedIn");
    tePwd->setPlaceholderText("Password");
    teUsername->setPlaceholderText("Username");
    teUsername->setFocus();

    QShortcut *quit=new QShortcut(QKeySequence("Ctrl+Q"),this),
            *admin=new QShortcut(QKeySequence("Ctrl+D"),this);

    //segnali e slots
    connect(teUsername,SIGNAL(returnPressed()),this,SLOT(login()));
    connect(tePwd,SIGNAL(returnPressed()),this,SLOT(login()));
    connect(loginButton,SIGNAL(clicked()),this,SLOT(login()));
    connect(adminButton,SIGNAL(clicked()),this,SLOT(admin()));
    connect(quit,SIGNAL(activated()),this,SLOT(close()));
    connect(admin,SIGNAL(activated()),this,SLOT(admin()));
}//LoginWindow
