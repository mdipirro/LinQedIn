#include "searchbynamesurname.h"

SearchByNameSurname::SearchByNameSurname(const QString& n,const QString& s):SearchByName(n),SearchBySurname(s){}

bool SearchByNameSurname::operator()(const SmartUser& user) const{
    return SearchByName::operator()(user) && SearchBySurname::operator()(user);
}//operator()
