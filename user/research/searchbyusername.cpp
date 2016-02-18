#include "searchbyusername.h"
#include "user/user.h"

SearchByUsername::SearchByUsername(const QString& us):username(us){}

bool SearchByUsername::operator()(const SmartUser& user) const{
    return !username.compare(user->getLoginInfo().getEmailAddress(),Qt::CaseInsensitive);
}//operator()
