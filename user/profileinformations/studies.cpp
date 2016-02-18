#include "studies.h"
#include <QStringList>

QString Studies::studiesID="Titoli Di Studio";

Studies::Studies(const QString& school,const QString& qual):
    Information(studiesID),
    highSchool(school),qualification(qual){}

Studies::Studies(const QStringList& argv):
    Information(studiesID),
    highSchool(argv.at(0)),qualification(argv.at(1))
{
    for(int i=2;i<argv.size();i+=3) addDegree(Degree(argv.at(i),argv.at(i+1),argv.at(i+2).toInt()));
}//Studies

void Studies::addDegree(const Degree& deg){degrees.push_back(deg);}

QString Studies::getIDString(){
    return studiesID;
}//getIDString

void Studies::update(const Information& newInfos){
    const Studies* s=dynamic_cast<const Studies*>(&newInfos);
    if(s) *this=*s;
}//update

QString Studies::getHighSchool() const{return highSchool;}

QString Studies::getQualification() const{return qualification;}

QVector<Degree> Studies::getDegrees() const{return degrees;}

Studies* Studies::clone() const{return new Studies(*this);}

QVector<QString> Studies::getInformationList(bool print) const{
    QVector<QString> aux;
    aux.push_back(highSchool); aux.push_back(qualification);
    if(print) foreach(Degree deg,degrees) aux.push_back(deg.toString());
    else foreach(Degree deg,degrees){
        aux.push_back(deg.getUniversityName());
        aux.push_back(deg.getDegreeName());
        aux.push_back(QString::number(deg.getDegreeMark()));
    }//foreach
    return aux;
}//getInformationList

bool Studies::operator==(const Information& other) const{
    const Studies* otherS=dynamic_cast<const Studies*>(&other);
    return otherS && highSchool==otherS->highSchool && qualification==otherS->qualification && degrees==otherS->degrees;
}//operator==
