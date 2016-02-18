#ifndef USERCREATOR_H
#define USERCREATOR_H

class User;
#include <QString>

/* Interfaccia per l'utilizzo di Factory Method Design Pattern. */

class UserCreator{
public:
    virtual User* createUser(int,const QString& ="",const QString& ="") const;
};

#endif // USERCREATOR_H
