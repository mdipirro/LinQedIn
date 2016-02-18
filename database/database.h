#ifndef DATABASE_H
#define DATABASE_H

#include "user/smartuser.h"
#include "user/research/searchfunctor.h"
#include <QString>
#include <QVector>

class QXmlStreamWriter;
class UserData;

class Database{
private:
    QList<SmartUser>* db;
    static Database* dbPointer; /*Singleton Design Pattern
                    ci deve essere una sola istanza del DB in memoria. Gli altri tentativi di istanziazione ottengono un puntatore
                    al DB già presente in memoria.
                        */
    static QString databaseNodeName;
    static QString userNodeName;
    static QString informationNodeName;
    static QString loginNodeName;
    static QString paymentNodeName;
    static QString infoNodeName;
    static QString valueNodeName;
    static QString networkNodeName;
    static QString contactNodeName;
    static QString typeName;
    static QString usernameName;
    static QString databaseFileName;
    static QString networkFileName;
    static QString tempFileName;

    void writeLoginInfo(QXmlStreamWriter*,const SmartUser&) const;
    void writePaymentInfo(QXmlStreamWriter*,const SmartUser&) const;
    void writeInformations(QXmlStreamWriter*,const SmartUser&) const;
    static void writeNetworkInfo(QXmlStreamWriter*,const SmartUser&);
    static void loadNetwork();

    //Impedisco di creare un database se non passando dalle funzioni load e close (applicazione del Singleton Pattern)
    Database();
    Database(const Database&);
    ~Database();
    Database& operator=(const Database&);

public:
    //static const QString separator;

    static Database* load(); //caricamento in lettura/scrittura
    static const Database* constLoad(); //caricamento in sola lettura
    void save() const;
    static void close();

    QVector<SmartUser> search(const SearchFunctor&) const;
    static void writeNetwork();
    static void updateNetowrk(const QString&,const QString&);
    void insert(const SmartUser&);
    void remove(const SmartUser&);
};

#endif // DATABASE_H
