#include "database.h"
#include "user/user.h"
#include "user/usercategories/feeuser.h"
#include "user/usercreator.h"
#include "user/userdata.h"
#include "user/profileinformations/personal.h"
#include "user/profileinformations/informationcreator.h"
#include "user/research/searchbyusername.h"
#include <QXmlStreamReader>
#include <QTextStream>
#include <QStringList>
#include <QFile>
#include <QResource>

//Inizializzazione campi dati statici
QString Database::databaseNodeName="database";
QString Database::userNodeName="user";
QString Database::informationNodeName="information";
QString Database::loginNodeName="login";
QString Database::paymentNodeName="payment";
QString Database::infoNodeName="info";
QString Database::valueNodeName="value";
QString Database::networkNodeName="network";
QString Database::typeName="type";
QString Database::usernameName="username";
QString Database::databaseFileName="database.xml";
QString Database::networkFileName="network.xml";
QString Database::tempFileName="temp.xml";
Database* Database::dbPointer(0);

void Database::writeLoginInfo(QXmlStreamWriter* xml,const SmartUser& user) const{
    xml->writeStartElement(loginNodeName);
    xml->writeTextElement(valueNodeName,user->getLoginInfo().getEmailAddress());
    xml->writeTextElement(valueNodeName,user->getLoginInfo().getPassword());
    xml->writeEndElement(); //login
}//writeLoginInfo

void Database::writePaymentInfo(QXmlStreamWriter* xml,const SmartUser& user) const{
    const FeeUser* fu=dynamic_cast<const FeeUser*>(&*user);
    if(fu){
        xml->writeStartElement(paymentNodeName);
        xml->writeTextElement(valueNodeName,QString::number(fu->getEspireDate().year()));
        xml->writeTextElement(valueNodeName,QString::number(fu->getEspireDate().month()));
        xml->writeTextElement(valueNodeName,QString::number(fu->getEspireDate().day()));
        xml->writeEndElement(); //payment
    }//if
}//writeLoginInfo

void Database::writeInformations(QXmlStreamWriter* xml,const SmartUser& user) const{
    QMap<QString,const Information*> map=user->getProfile().getAllInformations();
    for(QMap<QString,const Information*>::const_iterator it=map.constBegin();it!=map.constEnd();it++){
        xml->writeStartElement(infoNodeName);
        xml->writeAttribute(typeName,it.key());
        foreach(QString el,it.value()->getInformationList(false)) xml->writeTextElement(valueNodeName,el);
        xml->writeEndElement(); //info
    }//for
}//writeInformations

void Database::writeNetworkInfo(QXmlStreamWriter* xml,const SmartUser& user){
    Q_FOREACH(SmartUser aux,user->getContactsNetwork().getContactsList()) xml->writeTextElement(valueNodeName,aux->getLoginInfo().getEmailAddress());
}//writeLoginInfo

void Database::loadNetwork(){
    QFile file(networkFileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QXmlStreamReader xml(&file);
        SmartUser user;
        while(!xml.atEnd()){
            xml.readNextStartElement();
            if(xml.name()==userNodeName && xml.tokenType()!=QXmlStreamReader::EndElement)
                user=dbPointer->search(SearchByUsername(xml.attributes().value(usernameName).toString())).first();
            else if(xml.name()==valueNodeName)
                if(user) user->addUserToNetwork(dbPointer->search(SearchByUsername(xml.readElementText())).first());
        }//while
        file.close();
    }//if
}//loadNetwork

Database::Database():db(new QList<SmartUser>){}

Database::~Database(){close();}

Database* Database::load(){
    if(!dbPointer){
        dbPointer=new Database();
        QFile file(databaseFileName);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QXmlStreamReader xml(&file);
            int userType=1;
            QString infoType="";
            UserCreator uc;
            InformationCreator ic;
            while(!xml.atEnd()){
                xml.readNextStartElement();
                if(xml.name()==userNodeName) userType=xml.attributes().value(typeName).toInt();
                else if(xml.name()==loginNodeName){ //nodo di login
                    QString email,pwd;
                    xml.readNextStartElement(); email=xml.readElementText();
                    xml.readNextStartElement(); pwd=xml.readElementText();
                    SmartUser aux(uc.createUser(userType,email,pwd));
                    dbPointer->db->append(aux);
                    xml.readNextStartElement();
                }//if
                else if(xml.name()==paymentNodeName){
                    FeeUser* fu=dynamic_cast<FeeUser*>(&*dbPointer->db->last());
                    if(fu){
                        int day,month,year;
                        xml.readNextStartElement(); day=xml.readElementText().toInt();
                        xml.readNextStartElement(); month=xml.readElementText().toInt();
                        xml.readNextStartElement(); year=xml.readElementText().toInt();
                        fu->setEspireDate(QDate(day,month,year));
                    }//if
                    xml.readNextStartElement();
                }//if
                else if(xml.name()==infoNodeName){ //nodi di informazione
                    infoType.append(xml.attributes().value(typeName));
                    QStringList attr;
                    do{
                        xml.readNextStartElement();
                        if(xml.name()!=infoNodeName) attr.append(xml.readElementText());
                    }while(xml.name()!=infoNodeName);
                    dbPointer->db->last()->addSectionToProfileInformations(infoType,*ic.createInfo(infoType,attr));
                    infoType="";
                }//if
            }//while
        }//if
        file.close();
        loadNetwork();
    }//if
    return dbPointer;
}//load

const Database* Database::constLoad(){
    return load();
}//constLoad

void Database::save() const{
    QFile file(databaseFileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QXmlStreamWriter xml(&file);
        xml.setAutoFormatting(true);
        xml.writeStartDocument();
        xml.writeStartElement(databaseNodeName);
        for(int i=0;i<db->size();i++){
            xml.writeStartElement(userNodeName);
            xml.writeAttribute(typeName,QString::number(db->at(i)->getUserID()));
            writeLoginInfo(&xml,db->at(i));
            writePaymentInfo(&xml,db->at(i));
            xml.writeStartElement(informationNodeName);
            writeInformations(&xml,db->at(i));
            xml.writeEndElement(); //information
            xml.writeEndElement(); //user
        }//for
        xml.writeEndElement(); //database
        xml.writeEndDocument();
        file.close();
    }//if
}//save

void Database::close(){
    if(dbPointer && dbPointer->db){
        foreach(SmartUser us,*dbPointer->db) us.setReferences(1);
        delete dbPointer->db;
    }//if
    dbPointer=0;
}//close

QVector<SmartUser> Database::search(const SearchFunctor& sf) const{
    QVector<SmartUser> results;
    foreach(SmartUser us,*db) if(sf(us)) results.push_back(us);
    return results;
}//search

void Database::writeNetwork(){
    QFile file(networkFileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QXmlStreamWriter xml(&file);
        xml.setAutoFormatting(true);
        xml.writeStartDocument();
        xml.writeStartElement(networkNodeName);
        for(int i=0;i<dbPointer->db->size();i++){
            if(!dbPointer->db->at(i)->getContactsNetwork().empty()){
                xml.writeStartElement(userNodeName);
                xml.writeAttribute(usernameName,dbPointer->db->at(i)->getLoginInfo().getEmailAddress());
                writeNetworkInfo(&xml,dbPointer->db->at(i));
                xml.writeEndElement(); //user
            }//if
        }//for
        xml.writeEndElement(); //network
        xml.writeEndDocument();
        file.close();
    }//if
}//writeUserNetwork

void Database::updateNetowrk(const QString& oldEmail, const QString& newEmail){
    QFile file(tempFileName),net(networkFileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text) && net.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&net),out(&file);
        out<<in.readAll().replace(oldEmail,newEmail);
        file.close();
        net.close();
        QFile::remove(networkFileName);
        QFile::rename(tempFileName,networkFileName);
    }//if
}//updateNetwork

void Database::insert(const SmartUser& newUser){db->append(newUser);}

void Database::remove(const SmartUser& user){
    user->removeUserFromOthersNetwork();
    db->removeOne(user);
    writeNetwork();
}//remove
