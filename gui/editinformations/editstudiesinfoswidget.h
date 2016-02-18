#ifndef EDITSTUDIESINFOSWIDGET_H
#define EDITSTUDIESINFOSWIDGET_H

#include "editinfoswidget.h"
#include <QString>

class Profile;
class Studies;
class CustomStandardItemModel;
class QFormLayout;
class QWidget;
class QLineEdit;
class QTableView;
class QPushButton;
class QLabel;
class QModelIndex;

class EditStudiesInfosWidget:public EditInfosWidget{
    Q_OBJECT
private:
    static QString deleteImagePath,deleteS,noDegreeS;

    const Studies* infos;
    QFormLayout *form;
    QWidget *formWidget;
    QLineEdit *highSchool,*qualification;
    QTableView *degrees;
    QPushButton *addDegree;
    QLabel *noDegree;
    CustomStandardItemModel *model;

    enum{remove,university,course,situation};

    void initDegrees();
    void adjustTableHeight() const;

public:
    explicit EditStudiesInfosWidget(const LinQedInClient*,QWidget* =0);

protected slots:
    void saveRequest();
    void writeDefaultValues() const;
    void changeCursor(const QModelIndex&) const;
    void deleteRow(const QModelIndex&) const;
    void addRow() const;
};

#endif // EDITSTUDIESINFOSWIDGET_H
