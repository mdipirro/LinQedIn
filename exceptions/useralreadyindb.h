#ifndef USERALREADYINDB_H
#define USERALREADYINDB_H

#include "exception.h"

class QString;

class UserAlreadyInDB:public Exception{
public:
    UserAlreadyInDB(const QString& ="Un utente con questo username è già presente");
};

#endif // USERALREADYINDB_H
