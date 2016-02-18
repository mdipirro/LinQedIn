#ifndef ADMINMAINWIDGET_H
#define ADMINMAINWIDGET_H

#include "controller/linqedinuser.h"
#include <QFrame>

class LinQedInAdmin;
class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class QFormLayout;
class QListWidget;
class QPushButton;
class QLineEdit;
class QString;

class AdminMainWidget:public QFrame{
    Q_OBJECT
private:
    LinQedInAdmin *admin;
    QVBoxLayout *mainVerticalLayout;
    QFormLayout *searchULayout,*searchNSLayout;
    QHBoxLayout *buttonsLayout,*searchLayout;
    QLabel *logo,*loggedAsAdmin,*noUsers;
    QListWidget *users;
    QPushButton *save,*add,*logout,*searchU,*searchNS;
    QLineEdit *name,*surname,*username;

    static int buttonsMaxWidth;

    void initUsernameSearch();
    void initNameSurnameSearch();

public:
    explicit AdminMainWidget(LinQedInAdmin*,QWidget* =0);
    void populateList(const QVector<LinQedInUser>&) const;

signals:
    void addUserSignal() const;
    void logoutSignal() const;

private slots:
    void addUserRequest() const;
    void logoutRequest() const;
    void deleteUser(const QString&) const;
    void changePlan(const QString&,int) const;
    void saveDB() const;
    void usernameSearch() const;
    void nameSearch() const;
};

#endif // ADMINMAINWIDGET_H
