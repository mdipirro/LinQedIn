#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include "controller/linqedinclient.h"
#include "controller/linqedinuser.h"
#include <QFrame>

class SearchResults;
class QFormLayout;
class QListWidget;
class QVBoxLayout;
class QPushButton;
class QLabel;

class SearchWidget:public QFrame{
    Q_OBJECT
private:
    LinQedInClient* client;
    QListWidget *results;
    QFormLayout *form;
    QWidget* formWidget;
    QVBoxLayout *mainVerticalLayout;
    QPushButton *searchB;
    QLabel *_noResults,*logo;

    void noResults(bool);

protected:
    LinQedInClient* getClient() const;
    void addRowToForm(const QString&,QWidget*) const;
    void addSearchButton() const;
    void populateList(const SearchResults& =SearchResults());

public:
    explicit SearchWidget(LinQedInClient*,QWidget* =0);
    virtual ~SearchWidget();
    virtual void focus() const =0; //per dare il focus al campo di inserimento voluto

signals:
    void selectUser(const LinQedInUser&) const;
    void networkOperationDone() const;

protected slots:
    virtual void search() =0;
    void networkOperation(bool,const QString&) const;
    void userSelected(const QString&) const;
};

#endif // SEARCHWIDGET_H
