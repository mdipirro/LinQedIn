#ifndef INVALIDIMAGEEXCEPTION_H
#define INVALIDIMAGEEXCEPTION_H

#include "exception.h"

class QString;

class InvalidImageException:public Exception{
public:
    InvalidImageException(const QString& ="Immagine non valida");
};

#endif // INVALIDIMAGEEXCEPTION_H
