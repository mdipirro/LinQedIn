#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include "controller/linqedinadmin.h"
#include "user/profileinformations/personal.h"
#include <QMainWindow>

class AdminMainWidget;
class QTabWidget;
class QCloseEvent;

class AdminWindow:public QMainWindow{
    Q_OBJECT
private:
    LinQedInAdmin admin;
    QTabWidget *tabPane;
    AdminMainWidget *amw;

public:
    explicit AdminWindow(QWidget* =0);
    void closeEvent(QCloseEvent*);

public slots:
    void addUser();
    void insertUser(const QString&,const QString&,const QString&,int,Personal::Genders);
    void closeTab(int) const;
    void logout();
};

#endif // ADMINWINDOW_H
