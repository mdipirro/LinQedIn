#ifndef SELECTALL_H
#define SELECTALL_H

#include "searchfunctor.h"

class SelectAll:public SearchFunctor{
public:
    bool operator()(const SmartUser&) const;
};

#endif // SELECTALL_H
