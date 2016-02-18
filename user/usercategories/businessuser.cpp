#include "businessuser.h"

double BusinessUser::annualCost=17.99;
int BusinessUser::userID=2;
Permissions BusinessUser::permits(50,false,true,5); //101
QString BusinessUser::plan="Utente Business";

int BusinessUser::getUserId(){return userID;}

QString BusinessUser::getPlan(){return plan;}

BusinessUser::BusinessUser(const QString& emailAddress,const QString& password,const QDate& paymentDate):
    FeeUser(emailAddress,password,paymentDate){}

double BusinessUser::getAnnualCost(){
    return annualCost;
}//getAnnualCost

QString BusinessUser::getUserPlan() const{return getPlan();}

int BusinessUser::getUserID() const{return userID;}

Permissions BusinessUser::getCategoryPermits(){return permits;}

Permissions BusinessUser::getPermits() const{return permits;}

BusinessUser* BusinessUser::clone() const{return new BusinessUser(*this);}
