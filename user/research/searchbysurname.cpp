#include "searchbysurname.h"
#include "user/user.h"
#include "user/profileinformations/personal.h"

SearchBySurname::SearchBySurname(const QString& s):surname(s){}

bool SearchBySurname::operator()(const SmartUser& user) const{
    return !surname.compare(user->getProfile().getPersonalInformations().getSurname(),Qt::CaseInsensitive);
}//operator()
