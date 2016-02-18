#include "searchbyname.h"
#include "user/user.h"
#include "user/profileinformations/personal.h"

SearchByName::SearchByName(const QString& n):name(n){}

bool SearchByName::operator()(const SmartUser& user) const{
    return !name.compare(user->getProfile().getPersonalInformations().getName(),Qt::CaseInsensitive);
}//operator()
