#ifndef STUDIES_H
#define STUDIES_H

#include "information.h"
#include "degree.h"
#include <QString>
#include <QVector>

class Studies:public Information{
private:
    static QString studiesID;

    QString highSchool;
    QString qualification;
    QVector<Degree> degrees;

public:
    static QString getIDString();

    Studies(const QString&,const QString& ="Nessuna");
    Studies(const QStringList&);
    void addDegree(const Degree&);
    QString getHighSchool() const;
    QString getQualification() const;
    QVector<Degree> getDegrees() const;
    void update(const Information&);
    Studies* clone() const;
    QVector<QString> getInformationList(bool) const;
    bool operator==(const Information&) const;
};

#endif // STUDIES_H
