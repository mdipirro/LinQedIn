#ifndef FEEUSER_H
#define FEEUSER_H

#include "user/user.h"
#include <QDate>

class Permissions;

class FeeUser:public User{
private:
    QDate espireDate;

public:
    FeeUser(const QString&,const QString&,const QDate& =QDate::currentDate());

    QDate getEspireDate() const;
    void setEspireDate(const QDate& =QDate::currentDate().addYears(1));
    SearchResults userSearch(const Database&,const SearchFunctor&) const;
};

#endif // FEEUSER_H
