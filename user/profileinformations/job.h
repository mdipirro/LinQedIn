#ifndef JOB_H
#define JOB_H

#include <QString>
#include <QDate>

class Job{
private:
    QString company;
    QString employment;
    QDate begin;
    QDate end;

public:
    Job(const QString& ="",const QString& ="",const QDate& =QDate(),const QDate& =QDate()); //valori di default richiesti da QVector
    QString getCompany() const;
    QString getEmployment() const;
    QDate getBeginDate() const;
    QDate getEndDate() const;
    QString toString() const;
    bool operator==(const Job&) const;
};

#endif // JOB_H
