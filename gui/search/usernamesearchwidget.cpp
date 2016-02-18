#include "usernamesearchwidget.h"
#include "resultelement.h"
#include "user/research/searchresults.h"
#include "controller/linqedinclient.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QListWidgetItem>

UsernameSearchWidget::UsernameSearchWidget(LinQedInClient* cl,QWidget* parent):SearchWidget(cl,parent){
    setAttribute(Qt::WA_DeleteOnClose);
    username=new QLineEdit;
    username->setPlaceholderText(tr("Username"));
    connect(username,SIGNAL(returnPressed()),this,SLOT(search()));
    addRowToForm(tr("Username:"),username);
    addSearchButton();
}//UsernameSearchWidget

void UsernameSearchWidget::focus() const{username->setFocus();}

void UsernameSearchWidget::search(){populateList(getClient()->searchByUsername(username->text().trimmed()));}
