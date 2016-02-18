#ifndef LINQEDINADMIN_H
#define LINQEDINADMIN_H

#include "user/smartuser.h"
#include "user/profileinformations/personal.h"
#include <QVector>

class Database;
class LinQedInUser;
class QString;
class SearchFunctor;

class LinQedInAdmin{
private:
    Database* db;
    QVector<QString> deletedUsers;
    bool changed;

    QVector<LinQedInUser> search(const SearchFunctor&) const;

public:
    LinQedInAdmin();
    ~LinQedInAdmin();
    void insertInDB(const QString&,const QString&,const QString&,int,Personal::Genders);
    void removeFromDB(const QString&);
    void saveDB();
    QVector<LinQedInUser> allUsers() const;
    QVector<LinQedInUser> searchByUsername(const QString&) const;
    QVector<LinQedInUser> searchByName(const QString&) const;
    QVector<LinQedInUser> searchBySurname(const QString&) const;
    QVector<LinQedInUser> searchByNameSurname(const QString&,const QString&) const;
    void changeUserPlan(const QString&,int);
    bool dbChanged() const;
};

#endif // LINQEDINADMIN_H
