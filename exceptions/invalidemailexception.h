#ifndef INVALIDEMAILEXCEPTION_H
#define INVALIDEMAILEXCEPTION_H

#include "exceptions/exception.h"

class QString;

class InvalidEmailException:public Exception{
public:
    InvalidEmailException(const QString& ="Email non valida");
};

#endif // INVALIDEMAILEXCEPTION_H
