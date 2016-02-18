#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>

/*
 * Classe base per la gerarchia di eccezioni
 */

class Exception{
private:
    QString msg;
public:
    Exception(const QString& ="");
    virtual ~Exception();
    QString what() const;
};

#endif // EXCEPTION_H
