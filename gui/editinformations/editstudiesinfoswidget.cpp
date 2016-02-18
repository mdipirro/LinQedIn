#include "editstudiesinfoswidget.h"
#include "customstandarditemmodel.h"
#include "gui/guistyle.h"
#include "user/profileinformations/studies.h"
#include "user/profileinformations/degree.h"
#include "user/profile.h"
#include "exceptions/noinfoexception.h"
#include <QVector>
#include <QString>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableView>
#include <QStringList>
#include <QHeaderView>
#include <QStandardItem>
#include <QStandardItem>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

QString EditStudiesInfosWidget::deleteImagePath="images/delete.png";
QString EditStudiesInfosWidget::deleteS=tr("Elimina");
QString EditStudiesInfosWidget::noDegreeS=tr("Nessuna Laurea.");

EditStudiesInfosWidget::EditStudiesInfosWidget(const LinQedInClient* cl,QWidget* parent):EditInfosWidget(parent,
                                                                                                    tr("Modifica informazioni di studio"),
                                                                                                    cl){
    setAttribute(Qt::WA_DeleteOnClose);
    try{
        infos=dynamic_cast<const Studies*>(&getProfile().getInformationsBySectionName(Studies::getIDString()));
    }catch(const NoInfoException&){infos=0;}
    formWidget=new QFrame;
    form=new QFormLayout;
    highSchool=new QLineEdit; qualification=new QLineEdit;
    connect(highSchool,SIGNAL(returnPressed()),this,SLOT(saveRequest()));
    connect(qualification,SIGNAL(returnPressed()),this,SLOT(saveRequest()));
    form->addRow(tr("Scuola Superiore: "),highSchool); form->setAlignment(highSchool,Qt::AlignCenter);
    form->addRow(tr("Qualificazione Professionale: "),qualification); form->setAlignment(qualification,Qt::AlignCenter);
    initDegrees();

    noDegree=new QLabel(noDegreeS);
    noDegree->setStyleSheet(GUIStyle::errorLabelStyle());
    form->addWidget(noDegree); form->setAlignment(noDegree,Qt::AlignCenter);

    addDegree=new QPushButton(tr("Aggiungi Laurea"));
    addDegree->setCursor(QCursor(Qt::PointingHandCursor));
    form->addWidget(addDegree); form->setAlignment(addDegree,Qt::AlignCenter);
    connect(addDegree,SIGNAL(clicked()),this,SLOT(addRow()));

    formWidget->setLayout(form);
    addWidgetToMainLayout(formWidget,Qt::AlignCenter);
    initButtons();
    formWidget->setObjectName("form");
    formWidget->setStyleSheet("#form{"+GUIStyle::borderStyle()+"padding-left:10px;padding-top:10px;}");
    writeDefaultValues();
}//EditStudiesInfosWidget

void EditStudiesInfosWidget::initDegrees(){
    QVector<int> aux; aux.push_back(remove);
    QStringList header; header<<deleteS<<tr("Università")<<tr("Corso di Laurea")<<tr("Situazione");
    model=new CustomStandardItemModel(aux,0,header.size());
    model->setHorizontalHeaderLabels(header);

    degrees=new QTableView;
    degrees->setMinimumWidth(500);
    degrees->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    degrees->verticalHeader()->setVisible(false);
    degrees->setMouseTracking(true);
    degrees->setModel(model);
    degrees->setStyleSheet("QHeaderView::section{background:"+GUIStyle::lightGold()+";}");
    form->addRow(tr("Lauree: "),degrees); form->setAlignment(degrees,Qt::AlignLeft);
    connect(degrees,SIGNAL(entered(QModelIndex)),this,SLOT(changeCursor(QModelIndex)));
    connect(degrees,SIGNAL(clicked(QModelIndex)),this,SLOT(deleteRow(QModelIndex)));
}//initDegrees

void EditStudiesInfosWidget::adjustTableHeight() const{
    degrees->resizeColumnsToContents();
    degrees->resizeRowsToContents();
    degrees->horizontalHeader()->setStretchLastSection(true);
    degrees->setMinimumHeight(model->rowCount()*degrees->rowHeight(0)+degrees->horizontalHeader()->height()+
                              2*degrees->frameWidth());
    degrees->setMaximumHeight(1.5*model->rowCount()*degrees->rowHeight(0)+degrees->horizontalHeader()->height()+
                              2*degrees->frameWidth());
}//adjustTableHeight

void EditStudiesInfosWidget::writeDefaultValues() const{
    highSchool->setText("");
    qualification->setText("");
    if(infos){
        highSchool->setPlaceholderText(infos->getHighSchool());
        qualification->setPlaceholderText(infos->getQualification());
        QVector<Degree> degs=infos->getDegrees();
        degrees->setVisible(degs.size()>0); noDegree->setHidden(degs.size()>0);
        if(degs.size()>0){
            model->setRowCount(degs.size());
            int r=0;
            QLabel *del=new QLabel;
            del->setPixmap(QPixmap(deleteImagePath));
            del->setMinimumSize(30,30);
            del->setMaximumSize(30,30);
            del->setScaledContents(true);
            del->setAlignment(Qt::AlignCenter);
            for(QVector<Degree>::const_iterator it=degs.constBegin();it!=degs.constEnd();it++,r++){
                model->setItem(r,remove,new QStandardItem(QIcon(deleteImagePath),deleteS));
                model->setItem(r,university,new QStandardItem(it->getUniversityName()));
                model->setItem(r,course,new QStandardItem(it->getDegreeName()));
                model->setItem(r,situation,new QStandardItem(((it->graduated())?
                                                               tr("In corso"):
                                                               (QString::number(it->getDegreeMark())+
                                                                   ((it->isHonors())?tr(" e lode"):
                                                                                   ""))
                                                            )));
            }//for
            adjustTableHeight();
        }//if
    }//if
    else{noDegree->setVisible(true); degrees->setVisible(false);}
}//writeDefaultValues

void EditStudiesInfosWidget::saveRequest(){
    Studies s(getInformationText(highSchool),getInformationText(qualification));
    bool stopped=false;
    int r=0;
    for(;r<model->rowCount() && !stopped;r++){
        stopped=(model->item(r,university)->text()=="" || model->item(r,course)->text()=="" || model->item(r,situation)->text()=="");
        ((model->item(r,3)->text().contains(" e lode"))?
                s.addDegree(Degree(model->item(r,university)->text(),
                                   model->item(r,course)->text(),
                                   model->item(r,situation)->text().mid(0,model->item(r,situation)->text().size()-7).toInt(),
                                   true)):
                s.addDegree(Degree(model->item(r,university)->text(),
                                   model->item(r,course)->text(),
                                   ((model->item(r,situation)->text()=="In corso")?0:
                                                                             model->item(r,situation)->text().toInt())
                                  )));
    }//for
    if(stopped){
        noDegree->setText("Informazioni mancanti nell'inserimento di una laurea.");
        noDegree->setVisible(true);
    }//if
    else if(r==0) cancel();
    else{
        Profile prof=getProfile();
        prof.updateInformationsBySectionName(Studies::getIDString(),s);
        emit save(prof);
    }//else
}//saveRequest

void EditStudiesInfosWidget::changeCursor(const QModelIndex& index) const{
    if(index.column()==0) degrees->setCursor(QCursor(Qt::PointingHandCursor));
    else degrees->setCursor(QCursor(Qt::ArrowCursor));
}//changeCursor

void EditStudiesInfosWidget::deleteRow(const QModelIndex& index) const{
    if(index.column()==remove) model->removeRow(index.row());
    if(model->rowCount()!=0) adjustTableHeight();
    else{degrees->setVisible(false); noDegree->setVisible(true); noDegree->setText(noDegreeS);}
}//deleteRow

void EditStudiesInfosWidget::addRow() const{
    model->setRowCount(model->rowCount()+1);
    model->setItem(model->rowCount()-1,remove,new QStandardItem(QIcon(deleteImagePath),deleteS));
    model->setItem(model->rowCount()-1,university,new QStandardItem(""));
    model->setItem(model->rowCount()-1,course,new QStandardItem(""));
    model->setItem(model->rowCount()-1,situation,new QStandardItem(""));
    adjustTableHeight();
    if(model->rowCount()==1){
        degrees->setVisible(true);
        noDegree->setVisible(false);
    }//if
}//addRow
