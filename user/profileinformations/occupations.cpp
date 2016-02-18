#include "occupations.h"
#include <QString>
#include <QStringList>

QString Occupations::occupationsID="Esperienze Lavorative";

QString Occupations::getIDString(){
    return occupationsID;
}//getIDString

Occupations::Occupations(const QStringList& argv):Information(occupationsID){ //8 perché una riga nel db contiene 8 campi per lavoro
    for(int i=0;i<argv.size();i+=8){
        if(argv.at(i+5)==0) addJob(Job(argv.at(i),argv.at(i+1),
                                       QDate(argv.at(i+2).toInt(),argv.at(i+3).toInt(),argv.at(i+4).toInt())
                                       )
                                   );
        else addJob(Job(argv.at(i),argv.at(i+1),
                        QDate(argv.at(i+2).toInt(),argv.at(i+3).toInt(),argv.at(i+4).toInt()),
                        QDate(argv.at(i+5).toInt(),argv.at(i+6).toInt(),argv.at(i+7).toInt())
                        )
                    );
    }//for
}//Occupations

void Occupations::addJob(const Job& j){jobs.push_back(j);}

void Occupations::update(const Information& newInfos){
    const Occupations* o=dynamic_cast<const Occupations*>(&newInfos);
    if(o) *this=*o;
}//update

Occupations* Occupations::clone() const{return new Occupations(*this);}

Job Occupations::getActualJob() const{
    return ((jobs.end()-1)->getEndDate().isValid())?(Job("","")):(*(jobs.end()-1)); //se disoccupato ritorno un Job vuoto
}//getActualJob

QVector<Job> Occupations::getJobs() const{return jobs;}

QVector<QString> Occupations::getInformationList(bool print) const{
    QVector<QString> aux;
    if(print) foreach(Job job,jobs) aux.push_back(job.toString());
    else foreach(Job job,jobs){
        aux.push_back(job.getCompany());
        aux.push_back(job.getEmployment());
        aux.push_back(QString::number(job.getBeginDate().year()));
        aux.push_back(QString::number(job.getBeginDate().month()));
        aux.push_back(QString::number(job.getBeginDate().day()));
        aux.push_back(QString::number(job.getEndDate().year()));
        aux.push_back(QString::number(job.getEndDate().month()));
        aux.push_back(QString::number(job.getEndDate().day()));
    }//foreach
    return aux;
}//getInformationList

bool Occupations::operator==(const Information& other) const{
    const Occupations* o=dynamic_cast<const Occupations*>(&other);
    return o && jobs==o->jobs;
}//operator==
