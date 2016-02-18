#ifndef SEARCHBYNAMESURNAME_H
#define SEARCHBYNAMESURNAME_H

#include "searchbyname.h"
#include "searchbysurname.h"
#include "searchbyusername.h"
class QString;
class SmartUser;

class SearchByNameSurname:public SearchByName,public SearchBySurname{
public:
    SearchByNameSurname(const QString&,const QString&);
    bool operator()(const SmartUser&) const;
};

#endif // SEARCHBYNAMESURNAME_H
