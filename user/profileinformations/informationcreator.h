#ifndef INFORMATIONCREATOR_H
#define INFORMATIONCREATOR_H

class Information;
class QString;
class QStringList;

class InformationCreator{
public:
    //Factory Method Design Pattern
    virtual Information* createInfo(const QString&,const QStringList&);
};

#endif // INFORMATIONCREATOR_H
