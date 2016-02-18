#include "linqedinuser.h"
#include "user/userdata.h"
#include "user/profile.h"
#include "user/user.h"
#include "user/usercategories/feeuser.h"
#include "user/research/searchbyusername.h"
#include "database/database.h"
#include <QDate>
#include <QFile>

LinQedInUser::LinQedInUser(const QString& username):user(Database::constLoad()->search(SearchByUsername(username)).first()){}

LinQedInUser::LinQedInUser(const SmartUser& newUser):user(newUser){}

UserData LinQedInUser::getLoginInfo() const{return user->getLoginInfo();}

Profile LinQedInUser::getProfile() const{return user->getProfile();}

QString LinQedInUser::getImagePath() const{
    return getImagePathByUsername(user->getLoginInfo().getEmailAddress(),user->getProfile().getPersonalInformations().getGender());
}//getImagePath

QString LinQedInUser::getImagePathByUsername(const QString& username,Personal::Genders gender){
    QFile image("images/"+username+".png");
    if(image.exists()) return image.fileName();
    else{
        image.setFileName("images/"+username+".jpg");
        if(image.exists()) return image.fileName();
    }//else
    return (gender==Personal::M)?"images/maleUser.png":
                                 "images/femaleUser.png";
}//getImagePath

QVector<LinQedInUser> LinQedInUser::getContactsList() const{
    QVector<LinQedInUser> aux;
    foreach(SmartUser us,user->getContactsNetwork().getContactsList()) aux.push_back(LinQedInUser(us));
    return aux;
}//getContactsList

QString LinQedInUser::getUserPlan() const{return user->getUserPlan();}

QDate LinQedInUser::getEspireDate() const{
    FeeUser* fe=dynamic_cast<FeeUser*>(&*user);
    return (fe)?fe->getEspireDate():QDate(0,0,0);
}//getEspireDate
