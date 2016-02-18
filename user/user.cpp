#include "user.h"
#include "database/database.h"
#include "research/permissions.h"
#include "research/searchfunctor.h"
#include "research/searchresults.h"

void User::removeUserFromOthersNetwork() const{
    foreach(SmartUser other,network.getContactsList()) other->removeUserFromNetwork(const_cast<User*>(this));
}//removeUserFromOthersNetwork

User::User(const QString& emailAddress,const QString& password):login(emailAddress,password),references(0){}

UserData User::getLoginInfo() const{return login;}

Profile User::getProfile() const{return profile;}

void User::setLoginInfo(const UserData& other){login=other;}

ContactsNetwork User::getContactsNetwork() const{return network;}

void User::addSectionToProfileInformations(const QString& sectionName,const Information& info){profile.addInformationSection(sectionName,info);}

void User::setProfile(const Profile& newProfile){profile=newProfile;}

void User::addUserToNetwork(const SmartUser& user){ //user non vuoto
    if(!network.findUser(user->getLoginInfo().getEmailAddress())){
        network.addUser(user);
        user->network.addUser(this);
    }//if
}//addUserToNetwork

void User::removeUserFromNetwork(const SmartUser& user){network.removeUser(user);}

bool User::operator==(const User& other) const{return login==other.login && profile==other.profile;}
