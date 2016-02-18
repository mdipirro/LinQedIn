#include "smartuser.h"
#include "user.h"

SmartUser::SmartUser(User* const us):user(us){if(user) user->references++;}

SmartUser::SmartUser(const SmartUser& us):user(us.user){if(user) user->references++;}

SmartUser& SmartUser::operator=(const SmartUser& newUser){
    if(this!=&newUser){
        User* aux=user;
        user=newUser.user;
        if(user) user->references++;
        if(aux){
            aux->references--;
            if(aux->references==0) delete aux;
        }//if
    }//if
    return *this;
}//operator=

SmartUser::~SmartUser(){
    if(user){
        user->references--;
        if(user->references==0) delete user;
    }//if
}//~SmartUser

bool SmartUser::operator==(const SmartUser& other) const{return user==other.user;}

bool SmartUser::operator!=(const SmartUser& other) const{return !(user==other.user);}

bool SmartUser::operator<(const SmartUser& other) const{
    return user->getLoginInfo().getEmailAddress()<other.user->getLoginInfo().getEmailAddress();
}//operator!=

User& SmartUser::operator*() const{return *user;}

User* SmartUser::operator->() const{return user;}

SmartUser::operator bool() const{return user;}

void SmartUser::setReferences(int r){user->references=r;}
