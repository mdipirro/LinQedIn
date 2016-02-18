#ifndef EDITOCCUPATIONSINFOSWIDGET_H
#define EDITOCCUPATIONSINFOSWIDGET_H

#include "editinfoswidget.h"
#include <QString>

class LinQedInClient;
class Occupations;
class CustomStandardItemModel;
class QFormLayout;
class QWidget;
class QLineEdit;
class QTableView;
class QStandardItem;
class QPushButton;
class QLabel;
class QCalendarWidget;
class QModelIndex;

class EditOccupationsInfosWidget:public EditInfosWidget{
    Q_OBJECT
private:
    static QString deleteImagePath,deleteS,noJobS;

    const Occupations* infos;
    QTableView *jobs;
    QPushButton *addJob;
    QLabel *noJob;
    QCalendarWidget *calendar;
    QStandardItem *targetItem;
    CustomStandardItemModel *model;

    void initJobs();
    void adjustTableHeight() const;
    void deleteRow(int) const;

    enum{remove=0,company=1,employment=2,begin=3,end=4};

public:
    explicit EditOccupationsInfosWidget(const LinQedInClient* cl,QWidget* =0);
    ~EditOccupationsInfosWidget();

protected slots:
    void saveRequest();
    void writeDefaultValues() const;
    void changeCursor(const QModelIndex&) const;
    void clickHandler(const QModelIndex&);
    void addRow() const;
    void changeDate(const QDate&);
};
#endif // EDITOCCUPATIONSINFOSWIDGET_H
