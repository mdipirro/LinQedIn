#include "plandialog.h"
#include "guistyle.h"
#include "user/usercategories/basicuser.h"
#include "user/usercategories/businessuser.h"
#include "user/usercategories/executiveuser.h"
#include <QVBoxLayout>
#include <QRadioButton>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QRadioButton>

PlanDialog::Plan::Plan(int planNumber,const QString& planDescr):id(planNumber),description(planDescr){}

PlanDialog::PlanDialog(QWidget* parent,ReturnMode rm):QDialog(parent),mode(rm){
    setWindowIcon(QIcon(GUIStyle::iconPath()));
    setAttribute(Qt::WA_DeleteOnClose,true);
    mainLayout=new QVBoxLayout;
    mainLayout->addWidget(createGroupBox());
    buttonBox=new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(QDialogButtonBox::Ok);
    buttonBox->addButton(QDialogButtonBox::Cancel);
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(confirmed()));
    connect(buttonBox,SIGNAL(rejected()),this,SLOT(close()));
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
}//PlanDialog

QGroupBox* PlanDialog::createGroupBox(){
    QGroupBox* groupBox=new QGroupBox(tr("Piani:"));
    groupBox->setStyleSheet("QGroupBox{"+GUIStyle::formBorderStyle()+"}");
    basic=new QRadioButton(BasicUser::getPlan());
    business=new QRadioButton(BusinessUser::getPlan());
    executive=new QRadioButton(ExecutiveUser::getPlan());
    basic->setChecked(true);

    QVBoxLayout* vbox=new QVBoxLayout;
    vbox->addSpacing(20);
    vbox->addWidget(basic);
    vbox->addWidget(business);
    vbox->addWidget(executive);
    groupBox->setLayout(vbox);

    return groupBox;
}//createGroupBox

void PlanDialog::confirmed(){
    close();
    Plan plan=basic->isChecked()?Plan(BasicUser::getUserId(),BasicUser::getPlan()):
                                 business->isChecked()?Plan(BusinessUser::getUserId(),BusinessUser::getPlan()):
                                                        Plan(ExecutiveUser::getUserId(),ExecutiveUser::getPlan());
    if(mode==idOnly)
        emit planSelected(plan.id);
    emit planSelected(plan.id,plan.description);
}//confirmed
