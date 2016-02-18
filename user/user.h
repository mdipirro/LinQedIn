#ifndef USER_H
#define USER_H

#include "userdata.h"
#include "profile.h"
#include "contactsnetwork.h"
#include "smartuser.h"
//#include "database/database.h"

class SearchResults;
class QString;
class Permissions;
class SearchResults;
class SearchFunctor;
class Database;

class User{
    friend class SmartUser;
private:
    UserData login;
    Profile profile;
    ContactsNetwork network;
    /*  Ogni categoria di User ha dei permessi specifici che verranno usati per differenziare la
      * rappresentazione dei dati risultanti dalla ricerca. L'astrazione di User rappresentante un Client
      * si occuperà di rappresentare i risultati in modo consistente ai permessi dello specifico User.
      * Questo permette di alleggerire la classe User da questo compito, che diventa a carico
      * dell'astrazione sovrastante il livello User. User mette a disposizione delle regole che dovranno
      * essere usate per rappresentare i risultati della ricerca. In questo modo è sufficiente modificare i
      * permessi per ogni classe di User, senza dover cambiare l'intero metodo per la ricerca.
      */

    int references;

public:
    User(const QString&,const QString&);
    virtual ~User(){}
    virtual User* clone() const =0;
    virtual QString getUserPlan() const =0;
    virtual int getUserID() const =0;
    UserData getLoginInfo() const;
    Profile getProfile() const;
    virtual Permissions getPermits() const =0;
    ContactsNetwork getContactsNetwork() const;
    void addSectionToProfileInformations(const QString&,const Information&);
    void setProfile(const Profile& pf);
    void setLoginInfo(const UserData&);
    void addUserToNetwork(const SmartUser&);
    void removeUserFromNetwork(const SmartUser&);
    void removeUserFromOthersNetwork() const;
    virtual SearchResults userSearch(const Database&,const SearchFunctor&) const =0;
    /* La classe SearchFunctor specifica che ricerca effettuare sul db passato come parametro. Viene richiamato il metodo
     * di ricerca del db, che effettua la ricerca specificata da SearchFunctor su ogni elemento. La classe SearchResults
     * contiene i risultati di tale ricerca. Questa classe si occupa di fornire un'astrazione indipendente dal contenitore
     * utilizzato per rappresentare i risultati della ricerca (0, 1 o più).
    */
    bool operator==(const User&) const;
};

#endif // USER_H
