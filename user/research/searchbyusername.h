#ifndef SEARCHBYUSERNAME_H
#define SEARCHBYUSERNAME_H

#include "searchfunctor.h"
#include "user/smartuser.h"
#include <QString>

class SearchByUsername:public SearchFunctor{
private:
    QString username;

public:
    SearchByUsername(const QString&);
    bool operator()(const SmartUser&) const;
};

#endif // SEARCHBYUSERNAME_H
