#ifndef LINQEDINUSER_H
#define LINQEDINUSER_H

#include "user/smartuser.h"
#include "user/profileinformations/personal.h"
#include <QVector>

class UserData;
class Profile;
class QString;
class QDate;

class LinQedInUser{
    friend class LinQedInAdmin;
private:
    SmartUser user;

    LinQedInUser(const SmartUser&);
public:
    LinQedInUser(const QString& =""); //valore di default richiesto da QVector
    UserData getLoginInfo() const;
    Profile getProfile() const;
    QString getImagePath() const;
    static QString getImagePathByUsername(const QString&,Personal::Genders);
    QVector<LinQedInUser> getContactsList() const;
    QString getUserPlan() const;
    QDate getEspireDate() const;
};

#endif // LINQEDINUSER_H
