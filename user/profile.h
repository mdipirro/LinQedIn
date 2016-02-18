#ifndef PROFILE_H
#define PROFILE_H

#include "profileinformations/information.h"
#include <QMap>
#include <QString>

class Personal;

class Profile{
private:
    class SmartInfo{
    public:
        Information* info;

        //Gestione profonda della memoria
        SmartInfo(Information* const =0);
        SmartInfo(const SmartInfo&);
        SmartInfo& operator=(const SmartInfo&);
        ~SmartInfo();
        Information* operator->() const;
        Information& operator*() const;
        bool operator==(const SmartInfo&) const;
        bool operator!=(const SmartInfo&) const;
        operator bool() const;
    };

    QMap<QString,SmartInfo> infos;

public:
    void addInformationSection(const QString&,const Information&);
    const Information& getInformationsBySectionName(const QString&) const;
    const Personal& getPersonalInformations() const; //impongo la presenza di informazioni personali
    void updateInformationsBySectionName(const QString&,const Information&);
    QMap<QString,const Information*> getAllInformations() const;
    bool operator==(const Profile&) const;
};

#endif // PROFILE_H
