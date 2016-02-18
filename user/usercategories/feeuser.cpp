#include "feeuser.h"
#include "user/research/searchresults.h"
#include "database/database.h"
#include "user/profileinformations/personal.h"
#include "user/profileinformations/occupations.h"
#include "exceptions/noinfoexception.h"

FeeUser::FeeUser(const QString& emailAddress,const QString& password,const QDate& paymentDate):
    User(emailAddress,password),espireDate(paymentDate){}

QDate FeeUser::getEspireDate() const{return espireDate;}

void FeeUser::setEspireDate(const QDate& date){espireDate=date;}

SearchResults FeeUser::userSearch(const Database& db,const SearchFunctor& sf) const{
    SearchResults sr;
    foreach(SmartUser r,db.search(sf)){
        Personal p=r->getProfile().getPersonalInformations();
        try{
            const Occupations& o=dynamic_cast<const Occupations&>(r->getProfile().getInformationsBySectionName(Occupations::getIDString()));
            sr.addResult(SearchResults::Result(r->getLoginInfo().getEmailAddress(),p.getName(),p.getSurname(),
                                               o.getActualJob().getCompany()+" come "+o.getActualJob().getEmployment(),
                                               p.getGender(),true));
        }catch(const NoInfoException&){
            sr.addResult(SearchResults::Result(r->getLoginInfo().getEmailAddress(),p.getName(),p.getSurname(),
                                               "Nessuna informazione sul lavoro",p.getGender(),true));
        }//catch
    }//foreach
    return sr;
}//userSearch
