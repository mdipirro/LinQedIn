#include "personal.h"
#include <QString>
#include <QStringList>
#include <QVector>

QString Personal::personalID="Personali";

Personal::Personal(const QString& name,const QString& surname,const QString& placeOfBirth,const QString& state,
                   const QDate& birth,const QChar& gender):
    Information(personalID),
    name(name),surname(surname),birthplace(placeOfBirth),birthState(state),dateOfBirth(birth),gender(gender){}

Personal::Personal(const QStringList& argv):
    Information(personalID),
    name(argv.at(0)),surname(argv.at(1)),birthplace(argv.at(2)),birthState(argv.at(3)),
    dateOfBirth(QDate((argv.at(4)).toInt(),(argv.at(5)).toInt(),(argv.at(6)).toInt())),
    gender((argv.at(7).at(0)))
{}

QString Personal::getIDString(){
    return personalID;
}//getIDString

void Personal::update(const Information& newInfos){
    const Personal* p=dynamic_cast<const Personal*>(&newInfos); //safe downcasting a Personal
    if(p) *this=*p;
}//update

Personal* Personal::clone() const{
    return new Personal(*this);
}//clone

QVector<QString> Personal::getInformationList(bool) const{
    QVector<QString> aux;
    aux.push_back(name); aux.push_back(surname);
    aux.push_back(birthplace);
    aux.push_back(birthState);
    aux.push_back(QString::number(dateOfBirth.year()));
    aux.push_back(QString::number(dateOfBirth.month()));
    aux.push_back(QString::number(dateOfBirth.day()));
    aux.push_back(gender);
    return aux;
}//getInformationList

QString Personal::getName() const{return name;}

QString Personal::getSurname() const{return surname;}

Personal::Genders Personal::getGender() const{return (gender=='M')?M:F;}

QDate Personal::getBirthdate() const{return dateOfBirth;}

QString Personal::getBirthplace() const{return birthplace;}

QString Personal::getBirthState() const{return birthState;}

bool Personal::operator==(const Information& other) const{
    const Personal* otherP=dynamic_cast<const Personal*>(&other);
    return otherP && name==otherP->name && surname==otherP->surname && birthplace==otherP->birthplace &&
            dateOfBirth==otherP->dateOfBirth && gender==otherP->gender;
}//operator==
