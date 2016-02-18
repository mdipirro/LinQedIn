#include "permissions.h"

Permissions::Permissions(int limit,bool infos,bool network,int st):
    userLimit(limit),visibleInfos(infos),visibleNetwork(network),searchType((st>=0 && st<=7)?QString::number(st,2):"000"){
    if(searchType.length()<3) for(int i=0;i<3-searchType.length()+1;i++) searchType.prepend('0');
}//Permissions

int Permissions::getUserLimit() const{return userLimit;}

bool Permissions::getVisibleInfos() const{return visibleInfos;}

bool Permissions::getVisibleNetwork() const{return visibleNetwork;}

int Permissions::getSearchType() const{bool ok; return searchType.toInt(&ok,2);} //so essere in base 2: ok non serve

bool Permissions::name() const{return searchType.at(2)=='1';}

bool Permissions::surname() const{return searchType.at(1)=='1';}

bool Permissions::username() const{return searchType.at(0)=='1';}
