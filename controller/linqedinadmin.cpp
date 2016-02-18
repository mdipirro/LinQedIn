#include "linqedinadmin.h"
#include "linqedinuser.h"
#include "database/database.h"
#include "user/user.h"
#include "user/usercreator.h"
#include "user/research/selectall.h"
#include "user/research/searchbyusername.h"
#include "user/research/searchbyname.h"
#include "user/research/searchbysurname.h"
#include "user/research/searchbynamesurname.h"
#include "user/research/searchfunctor.h"
#include "user/usercategories/feeuser.h"
#include "user/profile.h"
#include "user/userdata.h"
#include "exceptions/useralreadyindb.h"
#include "exceptions/invalidemailexception.h"
#include <QString>
#include <QFile>

LinQedInAdmin::LinQedInAdmin():db(Database::load()),changed(false){}

LinQedInAdmin::~LinQedInAdmin(){db->close();}

QVector<LinQedInUser> LinQedInAdmin::search(const SearchFunctor& sf) const{
    QVector<LinQedInUser> aux;
    foreach(SmartUser user,db->search(sf)) aux.push_back(LinQedInUser(user));
    return aux;
}//search

void LinQedInAdmin::insertInDB(const QString& name,const QString& surname,const QString& email,int plan,Personal::Genders gender){
    if(db->search(SearchByUsername(email)).isEmpty()){
        if(!UserData::validateEmail(email)) throw InvalidEmailException();
        UserCreator uc;
        User* toInsert=uc.createUser(plan,email,"password");
        toInsert->addSectionToProfileInformations(Personal::getIDString(),Personal(name,surname,"","",QDate(),gender));
        db->insert(toInsert);
        changed=true;
    }//if
    else throw UserAlreadyInDB();
}//insertInDB

void LinQedInAdmin::removeFromDB(const QString& username){
    deletedUsers.push_back(username);
    db->remove(db->search(SearchByUsername(username)).first());
    changed=true;
}//removeFromDB

void LinQedInAdmin::saveDB(){
    db->save();
    changed=false;
    foreach(QString user,deletedUsers)
        if(!QFile::remove("images/"+user+".jpg"))
            QFile::remove("images/"+user+".png");
}//save

QVector<LinQedInUser> LinQedInAdmin::allUsers() const{return search(SelectAll());}

void LinQedInAdmin::changeUserPlan(const QString& username,int plan){
    SmartUser aux=(db->search(SearchByUsername(username)).first());
    FeeUser *feAux=dynamic_cast<FeeUser*>(&*aux);
    if(plan!=aux->getUserID()){
        db->remove(aux);
        UserCreator uc;
        User* toInsert=uc.createUser(plan);
        toInsert->setLoginInfo(aux->getLoginInfo());
        toInsert->setProfile(aux->getProfile());
        foreach(SmartUser su,aux->getContactsNetwork().getContactsList()) toInsert->addUserToNetwork(su);
        FeeUser* fe=dynamic_cast<FeeUser*>(toInsert);
        if(fe) fe->setEspireDate((feAux)?feAux->getEspireDate().addYears(1):QDate::currentDate().addYears(1));
        db->insert(toInsert);
    }//if
    else if(feAux) feAux->setEspireDate(feAux->getEspireDate().addYears(1));
    changed=true;
}//changeUserPlan

QVector<LinQedInUser> LinQedInAdmin::searchByUsername(const QString& username) const{return search(SearchByUsername(username));}

QVector<LinQedInUser> LinQedInAdmin::searchByName(const QString& name) const{return search(SearchByName(name));}

QVector<LinQedInUser> LinQedInAdmin::searchBySurname(const QString& surname) const{
    return search(SearchBySurname(surname));
}//serachBySurname

QVector<LinQedInUser> LinQedInAdmin::searchByNameSurname(const QString& name,const QString& surname) const{
    return search(SearchByNameSurname(name,surname));
}//searchByNameSurname

bool LinQedInAdmin::dbChanged() const{return changed;}
