#include "job.h"

Job::Job(const QString& company,const QString& employment,const QDate& beg,const QDate& end):
    company(company),employment(employment),begin(beg),end(end){}

QString Job::getCompany() const{return company;}

QString Job::getEmployment() const{return employment;}

QDate Job::getBeginDate() const{return begin;}

QDate Job::getEndDate() const{return end;}

QString Job::toString() const{
    return company+" come "+employment+" dal "+begin.toString("dd/M/yyyy")+" "+((end.isNull())?"ad oggi.":(" al "+end.toString("dd/M/yyyy")));
}//toString

bool Job::operator==(const Job& other) const{
    return company==other.company && employment==other.employment && begin==other.begin && end==other.end;
}//operator==
