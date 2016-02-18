#ifndef USERDATA_H
#define USERDATA_H

#include <QString>

class UserData{
private:
    QString email;
    QString pwd;

public:
    UserData(const QString&,const QString&);

    static bool validateEmail(const QString&);

    QString getEmailAddress() const;
    QString getPassword() const;

    bool operator==(const UserData&) const;
};

#endif // USERDATA_H
