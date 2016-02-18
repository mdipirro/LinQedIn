#ifndef CONTACTSNETWORK_H
#define CONTACTSNETWORK_H

#include "smartuser.h"
#include <QList>

class QString;

class ContactsNetwork{
private:
    QList<SmartUser> net;

public:
    QList<SmartUser> getContactsList() const;
    bool empty() const;
    void addUser(const SmartUser&);
    void removeUser(const SmartUser&);
    SmartUser findUser(const QString& username) const;
};

#endif // CONTACTSNETWORK_H
