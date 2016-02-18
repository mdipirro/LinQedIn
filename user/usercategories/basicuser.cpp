#include "basicuser.h"
#include "database/database.h"
#include "user/research/searchresults.h"
#include "user/profileinformations/personal.h"
#include <QString>

int BasicUser::userID=1;
Permissions BasicUser::permits;
QString BasicUser::plan="Utente Basic";

int BasicUser::getUserId(){return userID;}

QString BasicUser::getPlan(){return plan;}

QString BasicUser::getUserPlan() const{return getPlan();}

int BasicUser::getUserID() const{return userID;}

Permissions BasicUser::getCategoryPermits(){return permits;}

Permissions BasicUser::getPermits() const{return permits;}

BasicUser::BasicUser(const QString& emailAddress,const QString& password):User(emailAddress,password){}

BasicUser* BasicUser::clone() const{return new BasicUser(*this);}

SearchResults BasicUser::userSearch(const Database& db,const SearchFunctor& sf) const{
    SearchResults sr;
    foreach(SmartUser r,db.search(sf)){
        Personal p=r->getProfile().getPersonalInformations();
        sr.addResult(SearchResults::Result(r->getLoginInfo().getEmailAddress(),p.getName(),p.getSurname(),"",p.getGender()));
    }//foreach
    return sr;
}//userSearch
