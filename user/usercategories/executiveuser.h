#ifndef EXECUTIVEUSER_H
#define EXECUTIVEUSER_H

#include "feeuser.h"
#include "user/research/permissions.h"
#include <QString>

class ExecutiveUser:public FeeUser{
private:
    static double annualCost;
    static int userID;
    static QString plan;

public:
    static Permissions permits;
    ExecutiveUser(const QString&,const QString&,const QDate& =QDate::currentDate().addYears(1));
    static int getUserId();
    static QString getPlan();
    static double getAnnualCost();
    static Permissions getCategoryPermits();
    Permissions getPermits() const;
    QString getUserPlan() const;
    int getUserID() const;
    ExecutiveUser* clone() const;
};

#endif // EXECUTIVEUSER_H
