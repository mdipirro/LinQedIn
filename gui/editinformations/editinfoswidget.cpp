#include "editinfoswidget.h"
#include "gui/guistyle.h"
#include "controller/linqedinclient.h"
#include "user/profile.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>

int EditInfosWidget::maxBWidth=150;

QString EditInfosWidget::getInformationText(QLineEdit* edit){
    return (edit->text()=="")?((edit->placeholderText()=="")?tr("Nessuna informazione"):
                                                             edit->placeholderText()):
                                    edit->text();
}//getInformationText

EditInfosWidget::EditInfosWidget(QWidget* parent,const QString& title,const LinQedInClient* cl):QFrame(parent),client(cl){
    setAttribute(Qt::WA_DeleteOnClose);
    setStyleSheet(GUIStyle::generalStyle()); //stile generale

    mainWidget=new QWidget;
    mainVerticalLayout=new QVBoxLayout;
    logo=new QPushButton;
    GUIStyle::initLogo(logo);
    logo->setStyleSheet(logo->styleSheet()+"background:"+GUIStyle::lightBeige()+";");
    connect(logo,SIGNAL(clicked()),this,SLOT(cancel()));
    mainVerticalLayout->addWidget(logo,0,Qt::AlignTop | Qt::AlignRight);
    header=new QLabel(title);
    header->setMaximumHeight(100);
    header->setStyleSheet(GUIStyle::headerStyle());
    mainVerticalLayout->addWidget(header,0,Qt::AlignCenter);
    setLayout(mainVerticalLayout);
}//EditInfosWidget

EditInfosWidget::~EditInfosWidget(){}

void EditInfosWidget::initButtons(bool sb,bool cb,bool rb){
    buttonsLayout=new QHBoxLayout;
    saveB=new QPushButton(tr("Salva"));
    saveB->setCursor(QCursor(Qt::PointingHandCursor));
    saveB->setMaximumWidth(maxBWidth);
    cancelB=new QPushButton(tr("Annulla"));
    cancelB->setCursor(QCursor(Qt::PointingHandCursor));
    cancelB->setMaximumWidth(maxBWidth);
    resetB=new QPushButton(tr("Azzera"));
    resetB->setCursor(QCursor(Qt::PointingHandCursor));
    resetB->setMaximumWidth(maxBWidth);

    if(sb) buttonsLayout->addWidget(saveB);
    if(cb) buttonsLayout->addWidget(cancelB);
    if(rb) buttonsLayout->addWidget(resetB);

    mainVerticalLayout->addLayout(buttonsLayout);
    connect(saveB,SIGNAL(clicked()),this,SLOT(saveRequest()));
    connect(cancelB,SIGNAL(clicked()),this,SLOT(cancel()));
    connect(resetB,SIGNAL(clicked()),this,SLOT(writeDefaultValues()));
}//initButtons

void EditInfosWidget::addWidgetToMainLayout(QWidget* w,Qt::Alignment a){mainVerticalLayout->addWidget(w,6,a);}

void EditInfosWidget::addLayoutToMainLayout(QLayout* l){mainVerticalLayout->addLayout(l);}

Profile EditInfosWidget::getProfile() const{return client->getProfile();}

void EditInfosWidget::cancel(){
    close();
    emit cancelled();
}//cancel
