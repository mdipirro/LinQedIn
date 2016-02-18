#ifndef NOINFOEXCEPTION_H
#define NOINFOEXCEPTION_H

#include "exceptions/exception.h"

class QString;

class NoInfoException:public Exception{
public:
    NoInfoException(const QString& ="Informazione non presente");
};

#endif // NOINFOEXCEPTION_H
