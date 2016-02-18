#include "information.h"
#include <QString>

Information::Information(const QString& id):sectionID(&id){}

const QString Information::getIDString() const{return *sectionID;}
