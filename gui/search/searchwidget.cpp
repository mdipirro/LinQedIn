#include "searchwidget.h"
#include "resultelement.h"
#include "gui/guistyle.h"
#include "user/research/searchresults.h"
#include "user/research/searchbyusername.h"
#include "database/database.h"
#include <QString>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>

SearchWidget::SearchWidget(LinQedInClient* cl,QWidget* parent):QFrame(parent),client(cl){
    setAttribute(Qt::WA_DeleteOnClose,true);
    setStyleSheet(GUIStyle::generalStyle());
    mainVerticalLayout=new QVBoxLayout;

    logo=new QLabel;
    GUIStyle::initLogo(logo);
    mainVerticalLayout->addWidget(logo,0,Qt::AlignTop | Qt::AlignRight);

    formWidget=new QWidget;
    formWidget->setMaximumWidth(400);
    form=new QFormLayout;
    formWidget->setLayout(form);
    mainVerticalLayout->addWidget(formWidget,0,Qt::AlignCenter);
    formWidget->setContentsMargins(10,10,10,10);
    formWidget->setObjectName("form");
    formWidget->setStyleSheet("#form{"+GUIStyle::borderStyle()+"}");

    searchB=new QPushButton(tr("Cerca"));
    connect(searchB,SIGNAL(clicked()),this,SLOT(search()));
    form->addWidget(searchB); form->setAlignment(searchB,Qt::AlignCenter);

    mainVerticalLayout->addSpacing(100);
    results=new QListWidget;
    results->setHidden(true);
    results->setEditTriggers(results->NoEditTriggers);
    results->setSelectionMode(QAbstractItemView::NoSelection);
    results->setMinimumWidth(520);
    results->setStyleSheet("QListWidget{"+GUIStyle::borderStyle()+"}");
    results->setContentsMargins(10,10,10,10);
    mainVerticalLayout->addWidget(results,5,Qt::AlignHCenter | Qt::AlignTop);

    _noResults=new QLabel(tr("Nessun Risultato"));
    _noResults->setHidden(true);
    _noResults->setStyleSheet(GUIStyle::errorLabelStyle());
    mainVerticalLayout->addWidget(_noResults,5,Qt::AlignHCenter | Qt::AlignTop);

    setLayout(mainVerticalLayout);
}//SearchWidget

void SearchWidget::noResults(bool _results){results->setVisible(_results); _noResults->setVisible(!_results);}

LinQedInClient* SearchWidget::getClient() const{return client;}

void SearchWidget::addRowToForm(const QString& label,QWidget* widget) const{form->addRow(label,widget);}

void SearchWidget::addSearchButton() const{
    form->addWidget(searchB);
    searchB->setCursor(QCursor(Qt::PointingHandCursor));
    form->setAlignment(searchB,Qt::AlignRight);
}//addSearchButton

SearchWidget::~SearchWidget(){}

void SearchWidget::populateList(const SearchResults& sr){
    results->clear();
    noResults(sr.size()>0);
    int row=0,height=15,limit=(client->getPermits().getUserLimit()==0)?sr.size():client->getPermits().getUserLimit();
    for(SearchResults::ScanResults it=sr.begin();it!=sr.end() && row<limit;it++){
        QListWidgetItem* item=new QListWidgetItem;
        ResultElement* re;
        if(client->getLoginInfo().getEmailAddress()==(*it).getUsername()) re=new ResultElement(*it,ResultElement::me,this);
        else if(client->getContactsNetwork().findUser((*it).getUsername())) re=new ResultElement(*it,ResultElement::alreadyInNetwork,this);
        else re=new ResultElement(*it,ResultElement::notInNetwork,this);
        connect(re,SIGNAL(operationInNetworkRequested(bool,QString)),this,SLOT(networkOperation(bool,QString)));
        if(client->getPermits().getVisibleInfos() || client->getContactsNetwork().findUser((*it).getUsername()))
            connect(re,SIGNAL(profileRequested(QString)),this,SLOT(userSelected(QString)));
        item->setSizeHint(re->size());
        results->insertItem(row++,item);
        results->setItemWidget(item,re);
        height+=re->height();
    }//for
    height=(height>300)?300:height;
    results->setMaximumHeight(height);
    results->setMinimumHeight(height);
}//populateList

void SearchWidget::networkOperation(bool operation,const QString& username) const{
    ResultElement* re=dynamic_cast<ResultElement*>(sender());
    if(operation){
        client->addToContactsNetwork(username); //aggiunta
        if(re){re->setResultPossibility(ResultElement::alreadyInNetwork); re->writeValues();}
    }//if
    else{
        client->removeFromContactsNetwork(username); //rimozione
        if(re){re->setResultPossibility(ResultElement::notInNetwork); re->writeValues();}
    }//else
    emit networkOperationDone();
}//networkOperation

void SearchWidget::userSelected(const QString& username) const{emit selectUser(username);}
