#include "resultelement.h"
#include "searchwidget.h"
#include "gui/guistyle.h"
#include "user/research/searchresults.h"
#include "user/profileinformations/personal.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>

ResultElement::ResultElement(const SearchResults::Result& r,ResultsPossibilities rp,QWidget* parent):QWidget(parent),result(r),type(rp){
    setAttribute(Qt::WA_DeleteOnClose,true);
    mainHorizontalLayout=new QHBoxLayout;

    image=new QLabel;
    image->setScaledContents(true);
    image->setMaximumSize(100,70);
    mainHorizontalLayout->addWidget(image);

    infosLayout=new QVBoxLayout;
    mainHorizontalLayout->addLayout(infosLayout);
    name=new QPushButton;
    name->setFlat(true);
    name->setStyleSheet("QPushButton{font-size:15px;font-weight:bold;text-decoration:underline;color:black;}"
                        "QPushButton:pressed{background-color:"+GUIStyle::lightGold()+";color:black;}");
    connect(name,SIGNAL(clicked()),this,SLOT(sendProfileRequest()));
    infosLayout->addWidget(name);
    job=new QLabel;
    infosLayout->addWidget(job);

    addRemove=new QPushButton;
    addRemove->setMaximumSize(200,50);
    addRemove->setStyleSheet("color:black;");
    connect(addRemove,SIGNAL(clicked()),this,SLOT(sendOperationInNetworkRequest()));
    mainHorizontalLayout->addWidget(addRemove,7,Qt::AlignCenter);
    setLayout(mainHorizontalLayout);
    setMinimumSize(170,100);

    writeValues();
}//ResultElement

void ResultElement::writeValues(){
    image->setPixmap(QPixmap(LinQedInUser::getImagePathByUsername(result.getUsername(),result.getGender())));
    name->setText(result.getName()+" "+result.getSurname());
    job->setText(result.getActualJob());
    switch(type){
    case alreadyInNetwork:
        addRemove->setText("Rimuovi dai contatti");
        break;
    case notInNetwork:
        addRemove->setText("Aggiungi ai contatti");
        break;
    case me:
        addRemove->setHidden(true);
        break;
    }//switch
}//writeValues

SearchResults::Result ResultElement::getResult() const{return result;}

void ResultElement::setResultPossibility(ResultsPossibilities rp){type=rp;}

void ResultElement::sendProfileRequest() const{emit profileRequested(result.getUsername());}

void ResultElement::sendOperationInNetworkRequest() const{
    emit operationInNetworkRequested(type!=alreadyInNetwork,result.getUsername());
}//sendOperationInNetworkRequest
