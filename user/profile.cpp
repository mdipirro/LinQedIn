#include "profile.h"
#include "profileinformations/personal.h"
#include "exceptions/noinfoexception.h"

//CLASSE SMARTINFO
Profile::SmartInfo::SmartInfo(Information* const inform):info((inform)?inform->clone():0){}

Profile::SmartInfo::SmartInfo(const SmartInfo& newInfo):info(newInfo.info->clone()){}

Profile::SmartInfo& Profile::SmartInfo::operator=(const SmartInfo& newInfo){
    if(this!=&newInfo){
        delete info;
        info=newInfo.info->clone();
    }//if
    return *this;
}//operator=

Profile::SmartInfo::~SmartInfo(){
    delete info;
}//~SmartInfo

Information* Profile::SmartInfo::operator->() const{return info;}

Information& Profile::SmartInfo::operator*() const{return *info;}

bool Profile::SmartInfo::operator==(const SmartInfo& other) const{return info==other.info;}

bool Profile::SmartInfo::operator!=(const SmartInfo& other) const{return info!=other.info;}

Profile::SmartInfo::operator bool() const{return info!=0;}

//CLASSE PROFILE
void Profile::addInformationSection(const QString& sectionName,const Information& info){
    infos.insert(sectionName,const_cast<Information*>(&info));
}//addInformationSection

const Information& Profile::getInformationsBySectionName(const QString& sectionName) const{
    QMap<QString,SmartInfo>::const_iterator it=infos.find(sectionName);
    if(it==infos.cend()) throw NoInfoException();
    return *it.value();
}//getInformationBySectionName

const Personal& Profile::getPersonalInformations() const{return static_cast<const Personal&>(getInformationsBySectionName(Personal::getIDString()));}

void Profile::updateInformationsBySectionName(const QString& sectionName,const Information& newInfos){
    try{
        getInformationsBySectionName(sectionName);
        (*infos.find(sectionName))->update(newInfos);
    }catch(const NoInfoException&){addInformationSection(sectionName,newInfos);}
}//updateInformationsBySectionName

QMap<QString,const Information*> Profile::getAllInformations() const{
    QMap<QString,const Information*> aux;
    for(QMap<QString,SmartInfo>::const_iterator it=infos.constBegin();it!=infos.constEnd();it++){
        aux.insert(it.key(),it->info);
    }//for
    return aux;
}//getAllinformations

bool Profile::operator==(const Profile& other) const{return infos==other.infos;}
