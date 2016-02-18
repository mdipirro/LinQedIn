#ifndef SEARCHBYNAME_H
#define SEARCHBYNAME_H

#include "searchfunctor.h"
#include <QString>

class SmartUser;

class SearchByName:virtual public SearchFunctor{
private:
    QString name;

public:
    SearchByName(const QString&);
    bool operator()(const SmartUser&) const;
};

#endif // SEARCHBYNAME_H
