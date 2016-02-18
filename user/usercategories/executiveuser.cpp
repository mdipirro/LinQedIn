#include "executiveuser.h"

double ExecutiveUser::annualCost=59.99;
int ExecutiveUser::userID=3;
Permissions ExecutiveUser::permits(0,true,true,7); //111
QString ExecutiveUser::plan="Utente Executive";

int ExecutiveUser::getUserId(){return userID;}

QString ExecutiveUser::getPlan(){return plan;}

ExecutiveUser::ExecutiveUser(const QString& emailAddress,const QString& password,const QDate& paymentDate):
    FeeUser(emailAddress,password,paymentDate){}

double ExecutiveUser::getAnnualCost(){
    return annualCost;
}//getAnnualCost

QString ExecutiveUser::getUserPlan() const{return getPlan();}

int ExecutiveUser::getUserID() const{return userID;}

Permissions ExecutiveUser::getCategoryPermits(){return permits;}

Permissions ExecutiveUser::getPermits() const{return permits;}

ExecutiveUser* ExecutiveUser::clone() const{return new ExecutiveUser(*this);}
