#ifndef SEARCHDENIEDEXCEPTION_H
#define SEARCHDENIEDEXCEPTION_H

#include "exception.h"
class QString;

class SearchDeniedException:public Exception{
public:
    SearchDeniedException(const QString& ="Utente non abilitato a questo tipo di ricerca");
};

#endif // SEARCHDENIEDEXCEPTION_H
