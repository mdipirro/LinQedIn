#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#include <QString>

class Permissions{
public:
    enum SearchTypes{byNameSurname=0,byName=1,bySurname=2,byUsername=4};

    Permissions(int =10,bool =false,bool =false,int =byNameSurname);
    int getUserLimit() const;
    bool getVisibleInfos() const;
    bool getVisibleNetwork() const;
    int getSearchType() const;
    bool name() const;
    bool surname() const;
    bool username() const;

private:
    int userLimit;
    bool visibleInfos;
    bool visibleNetwork;
    QString searchType; //corrisponde al numero binario "username surnameOnly nameOnly"
};

#endif // PERMISSIONS_H
