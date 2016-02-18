#ifndef SEARCHFUNCTOR_H
#define SEARCHFUNCTOR_H

#include "user/smartuser.h"

class SearchFunctor{
public:
    virtual bool operator()(const SmartUser&) const =0;
    virtual ~SearchFunctor(){}
};

#endif // SEARCHFUNCTOR_H
