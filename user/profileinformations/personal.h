#ifndef PERSONAL_H
#define PERSONAL_H

#include "information.h"
#include "QDate"

class Personal:public Information{
private:
    static QString personalID;

    QString name;
    QString surname;
    QString birthplace;
    QString birthState;
    QDate dateOfBirth;
    QChar gender;

public:
    static QString getIDString();
    enum Genders{M='M',F='F'};

    Personal(const QString&,const QString&,const QString& ="",const QString& ="",const QDate& =QDate(),const QChar& =M);
    Personal(const QStringList&);
    void update(const Information&);
    Personal* clone() const;
    QVector<QString> getInformationList(bool) const;
    QString getName() const;
    QString getSurname() const;
    Genders getGender() const;
    QDate getBirthdate() const;
    QString getBirthplace() const;
    QString getBirthState() const;
    bool operator==(const Information&) const;
};

#endif // PERSONAL
