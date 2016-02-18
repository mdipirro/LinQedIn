#include "degree.h"

int Degree::maxMark=110;
int Degree::minMark=66;

Degree::Degree(const QString& un,const QString& deg,int m,bool h):university(un),degree(deg),mark(m),honors(h){
    if(mark>maxMark){mark=maxMark; honors=true;}
}//Degree

QString Degree::getUniversityName() const{return university;}

QString Degree::getDegreeName() const{return degree;}

int Degree::getDegreeMark() const{return mark;}

bool Degree::graduated() const{return mark<minMark;}

bool Degree::isHonors() const{return honors;}

void Degree::setHonors(bool h){honors=h;}

QString Degree::toString() const{return degree+
            ((mark>minMark)?" presso "+university+" con voto "+((honors)?
                                                                               QString::number(maxMark)+"/"+QString::number(maxMark)+" e lode":
                                                                               QString::number(mark)+"/"+QString::number(maxMark)):
                           " in corso presso "+university);}

bool Degree::operator==(const Degree& other) const{
    return university==other.university && degree==other.degree && mark==other.mark;
}//operator==
