#ifndef OCCUPATIONS_H
#define OCCUPATIONS_H

class Job;

#include "information.h"
#include "job.h"
#include <QVector>
#include <QStringList>

class Occupations:public Information{
private:
    static QString occupationsID;
    QVector<Job> jobs;

public:
    static QString getIDString();

    Occupations(const QStringList& =QStringList());
    void addJob(const Job&);

    void update(const Information&);
    Occupations* clone() const;
    Job getActualJob() const;
    QVector<Job> getJobs() const;
    QVector<QString> getInformationList(bool) const;
    bool operator==(const Information&) const;
};

#endif // OCCUPATIONS_H

