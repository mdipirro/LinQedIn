#ifndef BUSINESSUSER_H
#define BUSINESSUSER_H

#include "feeuser.h"
#include "user/research/permissions.h"
#include <QString>

class BusinessUser:public FeeUser{
private:
    static double annualCost;
    static int userID;
    static Permissions permits;
    static QString plan;

public:
    BusinessUser(const QString&,const QString&,const QDate& =QDate::currentDate().addYears(1));
    static int getUserId();
    static QString getPlan();
    static double getAnnualCost();
    static Permissions getCategoryPermits();
    Permissions getPermits() const;
    QString getUserPlan() const;
    int getUserID() const;
    BusinessUser* clone() const;
};

#endif // BUSINESSUSER_H
