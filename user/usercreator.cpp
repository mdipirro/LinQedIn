#include "usercreator.h"
#include "usercategories/basicuser.h"
#include "usercategories/businessuser.h"
#include "usercategories/executiveuser.h"

User* UserCreator::createUser(int userType,const QString& email,const QString& password) const{
    if(userType==BasicUser::getUserId()) return new BasicUser(email,password);
    if(userType==BusinessUser::getUserId()) return new BusinessUser(email,password);
    if(userType==ExecutiveUser::getUserId()) return new ExecutiveUser(email,password);
    return 0;
}//createUser
