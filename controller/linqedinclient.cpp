#include "linqedinclient.h"
#include "user/user.h"
#include "user/research/searchbyusername.h"
#include "user/research/searchbyname.h"
#include "user/research/searchbysurname.h"
#include "user/research/searchbynamesurname.h"
#include "user/usercategories/feeuser.h"
#include "database/database.h"
#include "exceptions/nouserexception.h"
#include "exceptions/searchdeniedexception.h"
#include "exceptions/invalidimageexception.h"
#include "exceptions/useralreadyindb.h"
#include "exceptions/invalidemailexception.h"
#include "user/research/permissions.h"
#include <QFile>
#include <QImage>
#include <QDate>

LinQedInClient::LinQedInClient(const UserData& loginInfos):
    db(Database::constLoad()){
    QVector<SmartUser> res=db->search(SearchByUsername(loginInfos.getEmailAddress()));
    loggedUser=(!res.isEmpty() && res.first()->getLoginInfo().getPassword()==loginInfos.getPassword())?res.first():SmartUser(0);
    if(!loggedUser){db->close(); throw NoUserException("Login o password errati.");}
}//LinQedInClient

LinQedInClient::~LinQedInClient(){Database::close();}

UserData LinQedInClient::getLoginInfo() const{return loggedUser->getLoginInfo();}

Permissions LinQedInClient::getPermits() const{return loggedUser->getPermits();}

ContactsNetwork LinQedInClient::getContactsNetwork() const{return loggedUser->getContactsNetwork();}

Profile LinQedInClient::getProfile() const{return loggedUser->getProfile();}

void LinQedInClient::updateProfile(const Profile& newProfile) const{loggedUser->setProfile(newProfile); db->save();}

void LinQedInClient::updateLogin(const UserData& newLogin) const{
    QVector<SmartUser> aux=db->search(SearchByUsername(newLogin.getEmailAddress()));
    if(aux.isEmpty() || aux.first()==loggedUser){
        if(!UserData::validateEmail(newLogin.getEmailAddress())) throw InvalidEmailException();
        QString oldEmail=loggedUser->getLoginInfo().getEmailAddress();
        loggedUser->setLoginInfo(newLogin);
        db->save();
        if(oldEmail!=newLogin.getEmailAddress()) db->updateNetowrk(oldEmail,newLogin.getEmailAddress());
    }//if
    else throw UserAlreadyInDB();
}//updateLogin

void LinQedInClient::setImagePath(const QString& imagePath){
    if(!imagePath.isEmpty()){
        QImage im(imagePath);
        if(im.isNull()) throw InvalidImageException();
        else{
            QFile photo("images/"+loggedUser->getLoginInfo().getEmailAddress()+".jpg");
            if(photo.exists()) photo.remove();
            else{
                photo.setFileName("images/"+loggedUser->getLoginInfo().getEmailAddress()+".png");
                if(photo.exists()) photo.remove();
            }//else
            (imagePath.mid(imagePath.size()-3)=="jpg")?QFile::copy(imagePath,"images/"+loggedUser->getLoginInfo().getEmailAddress()+".jpg"):
                                                     QFile::copy(imagePath,"images/"+loggedUser->getLoginInfo().getEmailAddress()+".png");
        }//else
    }//if
}//setImagePath

void LinQedInClient::addToContactsNetwork(const QString& username){
    loggedUser->addUserToNetwork(db->search(SearchByUsername(username)).first());
    Database::writeNetwork();
}//addToContactsNetwork

void LinQedInClient::removeFromContactsNetwork(const QString& username){
    loggedUser->removeUserFromNetwork(db->search(SearchByUsername(username)).first());
    db->search(SearchByUsername(username)).first()->removeUserFromNetwork(loggedUser);
    Database::writeNetwork();
}//removeFromContactsNetwork

SearchResults LinQedInClient::searchByUsername(const QString& username) const{
    if(!loggedUser->getPermits().username()) throw SearchDeniedException();
    return loggedUser->userSearch(*db,SearchByUsername(username));
}//searchByUsername

SearchResults LinQedInClient::searchByName(const QString& name) const{
    if(!loggedUser->getPermits().name()) throw SearchDeniedException();
    return loggedUser->userSearch(*db,SearchByName(name));
}//searchByName

SearchResults LinQedInClient::searchBySurname(const QString& surname) const{
    if(!loggedUser->getPermits().surname()) throw SearchDeniedException();
    return loggedUser->userSearch(*db,SearchBySurname(surname));
}//searchBySurname

SearchResults LinQedInClient::searchByNameSurname(const QString& name,const QString& surname) const{
    return loggedUser->userSearch(*db,SearchByNameSurname(name,surname));
}//searchByName

QString LinQedInClient::getUserPlan() const{return loggedUser->getUserPlan();}

QDate LinQedInClient::getEspireDate() const{
    FeeUser* fe=dynamic_cast<FeeUser*>(&*loggedUser);
    return (fe)?fe->getEspireDate():QDate(0,0,0);
}//getEspireDate
