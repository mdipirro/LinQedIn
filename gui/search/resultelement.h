#ifndef RESULTELEMENT_H
#define RESULTELEMENT_H

#include "user/research/searchresults.h"
#include <QWidget>

class QLabel;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;

class ResultElement:public QWidget{
    Q_OBJECT
public:
    enum ResultsPossibilities{alreadyInNetwork,notInNetwork,me};

    explicit ResultElement(const SearchResults::Result&,ResultsPossibilities,QWidget* =0);
    SearchResults::Result getResult() const;
    void setResultPossibility(ResultsPossibilities);
    void writeValues();

private:
    SearchResults::Result result;
    ResultsPossibilities type;
    QLabel *image,*job;
    QPushButton *name,*addRemove;
    QHBoxLayout *mainHorizontalLayout;
    QVBoxLayout *infosLayout;

signals:
    void profileRequested(const QString&) const;
    void operationInNetworkRequested(bool,const QString&) const; //bool: true == aggiunta; false == rimozione

private slots:
    void sendProfileRequest() const;
    void sendOperationInNetworkRequest() const;
};

#endif // RESULTELEMENT_H
