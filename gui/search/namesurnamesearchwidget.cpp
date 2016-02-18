#include "namesurnamesearchwidget.h"
#include "user/research/searchresults.h"
#include "resultelement.h"
#include "exceptions/searchdeniedexception.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QListWidgetItem>

NameSurnameSearchWidget::NameSurnameSearchWidget(LinQedInClient* cl,QWidget* parent):SearchWidget(cl,parent){
    setAttribute(Qt::WA_DeleteOnClose,true);
    name=new QLineEdit;
    name->setPlaceholderText(tr("Nome")); name->setText("");
    connect(name,SIGNAL(returnPressed()),this,SLOT(search()));
    addRowToForm(tr("Nome:"),name);
    surname=new QLineEdit;
    surname->setPlaceholderText(tr("Cognome")); surname->setText("");
    connect(surname,SIGNAL(returnPressed()),this,SLOT(search()));
    addRowToForm(tr("Cognome:"),surname);
    addSearchButton();
}//NameSurnameSearchWidget

void NameSurnameSearchWidget::focus() const{name->setFocus();}

void NameSurnameSearchWidget::search(){
    try{
        if(name->text()=="" && surname->text()!="")
            populateList(getClient()->searchBySurname(surname->text().trimmed()));
        else if(name->text()!="" && surname->text()=="")
            populateList(getClient()->searchByName(name->text().trimmed()));
        else if(name->text()!="" && surname->text()!="") populateList(getClient()->searchByNameSurname(name->text().trimmed(),surname->text().trimmed()));
        else populateList();
    }catch(const SearchDeniedException&){
        populateList();
    }//catch
}//search
