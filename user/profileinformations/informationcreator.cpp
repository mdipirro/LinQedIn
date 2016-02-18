#include "informationcreator.h"
#include "personal.h"
#include "studies.h"
#include "occupations.h"

Information* InformationCreator::createInfo(const QString& initType,const QStringList& argv){
    if(initType==Personal::getIDString()) return new Personal(argv);
    if(initType==Studies::getIDString()) return new Studies(argv);
    if(initType==Occupations::getIDString()) return new Occupations(argv);
    return 0;
}//createInfo
