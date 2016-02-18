#include "userdata.h"
#include <QRegExp>

UserData::UserData(const QString& emailAddress,const QString& password):email(emailAddress),pwd(password){}

bool UserData::validateEmail(const QString& email){
    QRegExp regExp("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",Qt::CaseInsensitive);
    regExp.setPatternSyntax(QRegExp::RegExp);
    return regExp.exactMatch(email);
}//validateEmail

QString UserData::getEmailAddress() const{return email;}

QString UserData::getPassword() const{return pwd;}

bool UserData::operator==(const UserData& other) const{
    return email==other.email && pwd==other.pwd;
}//operator==
