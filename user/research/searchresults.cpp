#include "searchresults.h"

//CLASSE RESULTS
SearchResults::Result::Result(const QString& us,const QString& n,const QString& s,const QString& aj,
                              Personal::Genders g,
                              bool vp,bool vn):
    username(us),name(n),surname(s),actualJob(aj),gender(g),visibleProfile(vp),visibleNetwork(vn){}

QString SearchResults::Result::getUsername() const{return username;}

QString SearchResults::Result::getName() const{return name;}

QString SearchResults::Result::getSurname() const{return surname;}

QString SearchResults::Result::getActualJob() const{return actualJob;}

Personal::Genders SearchResults::Result::getGender() const{return gender;}

bool SearchResults::Result::isAbleTo(ViewPermits p) const{
    switch(p){
    case profile: return visibleProfile;
    case network: return visibleNetwork;
    default: return false;
    }//switch
}//isAbleTo

//CLASSE SCANRESULTS
SearchResults::ScanResults::ScanResults(const QVector<Result>::const_iterator& i):it(i){}
SearchResults::ScanResults SearchResults::ScanResults::operator++(){
    ScanResults aux=*this;
    it++;
    return aux;
}//operator++

SearchResults::ScanResults& SearchResults::ScanResults::operator++(int){
    it++;
    return *this;
}//operator++

SearchResults::ScanResults& SearchResults::ScanResults::operator+(int offset){
    for(;offset>0;offset--) it++;
    return *this;
}//operator+

bool SearchResults::ScanResults::operator==(const ScanResults& sr) const{return it==sr.it;}

bool SearchResults::ScanResults::operator!=(const ScanResults& sr) const{return it!=sr.it;}

SearchResults::Result SearchResults::ScanResults::operator*() const{return *it;}

//CLASSE SEARCHRESULTS
SearchResults::SearchResults(const QVector<Result>& r):results(r){}

void SearchResults::addResult(const Result& r){results.push_back(r);}

SearchResults::ScanResults SearchResults::begin() const{return ScanResults(results.begin());}

SearchResults::ScanResults SearchResults::end() const{return ScanResults(results.end());}

int SearchResults::size() const{return results.size();}
