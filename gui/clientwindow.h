#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include "controller/linqedinclient.h"
#include "controller/linqedinuser.h"
#include <QMainWindow>
#include <QVector>

class ClientProfileWidget;
class Profile;
class UserData;
class QTabWidget;
class QAction;
class QMenu;

class ClientWindow:public QMainWindow{
    Q_OBJECT
private:
    class Tab{
    public:
        enum TabsID{editPersonalsTab,editStudiesTab,editOccupationsTab,editLoginTab,searchByNameTab,searchByUsernameTab};
        bool isOpen;
        short tabIndex;
        Tab(bool =false,short =-1);
    };

    static int tabTypes;
    static int maxWidth;
    static int maxHeight;

    QVector<Tab> openTabs;
    LinQedInClient* client;
    QTabWidget *tabPane;
    ClientProfileWidget* cpw;
    QMenu *editMenu,*searchMenu;
    QAction *editPersonal,*editStudies,*editOccupations,*editImage;
    QAction *aboutA,*searchByUsernameA,*searchByNameA,*logoutA,*editLogin,*subscriptionA;

    void createActions();
    void createMenus();

public:
    explicit ClientWindow(LinQedInClient*,QMainWindow* =0);
    ~ClientWindow();

signals:
    void userSelected(const LinQedInUser&) const;

private slots:
    void repaintCPW();
    void paintProfile(const LinQedInUser&) const;
    void updateProfile(const Profile&);
    void editPersonalInformations();
    void editStudiesInformations();
    void editOccupationalInformations();
    void editProfileImage();
    void about();
    void searchByUsername();
    void searchByName();
    void tabClosing(int);
    void networkOperation() const;
    void logout();
    void editLoginInfo();
    void updateLogin(const UserData&);
    void subscription();
};

#endif // CLIENTWINDOW_H
