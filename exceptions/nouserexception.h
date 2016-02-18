#ifndef NOUSEREXCEPTION_H
#define NOUSEREXCEPTION_H

#include "exception.h"
class QString;

class NoUserException:public Exception{
public:
    NoUserException(const QString& ="Utente non presente");
};

#endif // NOUSEREXCEPTION_H
