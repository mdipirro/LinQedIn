#ifndef DEGREE_H
#define DEGREE_H

#include <QString>

class Degree{
private:
    QString university;
    QString degree;
    int mark;
    bool honors;
    static int maxMark;
    static int minMark;

public:
    Degree(const QString& ="",const QString& ="",int =0,bool =false);
    QString getUniversityName() const;
    QString getDegreeName() const;
    int getDegreeMark() const;
    bool graduated() const;
    bool isHonors() const;
    void setHonors(bool);
    QString toString() const;
    bool operator==(const Degree&) const;
};

#endif // DEGREE_H
