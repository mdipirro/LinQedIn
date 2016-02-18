#ifndef BASICUSER_H
#define BASICUSER_H

#include "user/user.h"
#include "user/research/permissions.h"
#include <QString>

class BasicUser:public User{
private:
    static int userID;
    static Permissions permits;
    static QString plan;

public:
    static int getUserId();
    static QString getPlan();
    QString getUserPlan() const;
    static Permissions getCategoryPermits();
    Permissions getPermits() const;
    int getUserID() const;
    BasicUser(const QString&,const QString&);
    BasicUser* clone() const;
    SearchResults userSearch(const Database& db,const SearchFunctor& sf) const;
};

#endif // BASICUSER_H
