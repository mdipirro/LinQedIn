#ifndef LINQEDINCLIENT_H
#define LINQEDINCLIENT_H

#include "user/smartuser.h"
#include "user/research/searchresults.h"

class Database;
class UserData;
class Profile;
class Permissions;
class ContactsNetwork;
class QDate;

/* La classe è il controller che si frappone tra l'interfaccia grafica e modello di utenti. Per un un utente loggato si
 * conoscono i suoi permessi. Questo, in combinazione con i risultati della ricerca nel db, permette di rappresentare in
 * modo consistente i risultati rispettando le regole di ciascun utente.
 */
class LinQedInClient{
private:
    SmartUser loggedUser;
    const Database* db;

public:
    LinQedInClient(const UserData&);
    ~LinQedInClient();
    UserData getLoginInfo() const;
    Permissions getPermits() const;
    ContactsNetwork getContactsNetwork() const;
    Profile getProfile() const;
    void updateProfile(const Profile&) const;
    void updateLogin(const UserData&) const;
    void addToContactsNetwork(const QString&);
    void removeFromContactsNetwork(const QString&);
    void setImagePath(const QString&);
    SearchResults searchByUsername(const QString&) const;
    SearchResults searchByName(const QString&) const;
    SearchResults searchBySurname(const QString&) const;
    SearchResults searchByNameSurname(const QString&,const QString&) const;
    QString getUserPlan() const;
    QDate getEspireDate() const;
};

#endif // LINQEDINCLIENT_H
