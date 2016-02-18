#include "contactsnetwork.h"
//#include "exceptions/exception.h"
#include "user.h"
#include <QString>

QList<SmartUser> ContactsNetwork::getContactsList() const{return net;}

bool ContactsNetwork::empty() const{return net.empty();}

void ContactsNetwork::addUser(const SmartUser& user){net.append(user);}

void ContactsNetwork::removeUser(const SmartUser& user){net.removeOne(user);}

SmartUser ContactsNetwork::findUser(const QString& username) const{
    bool found=false; QList<SmartUser>::const_iterator it=net.constBegin();
    for(;it!=net.constEnd() && !found;it++) found=((*it)->getLoginInfo().getEmailAddress()==username);
    return (found)?*(--it):SmartUser(0);
}//findUser
