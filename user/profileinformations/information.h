#ifndef INFORMATION_H
#define INFORMATION_H

#include <QVector>

class QString;
class QStringList;

class Information{
private:
    const QString* sectionID;

protected:
    Information(const QString&);

public:
    const QString getIDString() const;

    virtual ~Information(){}
    virtual void update(const Information&) =0;
    virtual Information* clone() const =0;
    virtual QVector<QString> getInformationList(bool =false) const =0;
    virtual bool operator==(const Information&) const =0;
};

#endif // INFORMATION_H
