#ifndef ClientProfileWidget_H
#define ClientProfileWidget_H

#include <QFrame>
#include <QString>

class LinQedInClient;
class LinQedInUser;
class BasicContactViewer;
class QVBoxLayout;
class QGroupBox;
class QLabel;
class QPushButton;
class QHBoxLayout;
class QGridLayout;
class QScrollArea;
class QListView;
class QStringListModel;
class QResizeEvent;
class QKeyEvent;

class ClientProfileWidget:public QFrame{
    Q_OBJECT
friend class BasicContactViewer;
private:
    static QString noInformations;

    LinQedInClient* client;
    LinQedInUser* user;
    bool equals; //bool di appoggio per evitare numerosi test di uguaglianza
    QStringListModel *jobsModel,*contactsModel,*degreesModel;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidget,*contactsWidget;
    QVBoxLayout *mainVerticalLayout,*studiesLayout,*scrollAreaLayout,*occupationsLayout,*contactsLayout;
    QHBoxLayout *personal,*horizontalLayout;
    QGroupBox *personalInfosGroupBox;
    QGridLayout *gridLayout;
    QLabel *image;
    QPushButton* logo;
    QLabel *name,*studies,*occupations,*contactsL;
    QLabel *gender,*genderV;
    QLabel *birthdate,*birthdateV;
    QLabel *birthplace,*birthplaceV;
    QLabel *email,*emailV;
    QLabel *highSchool,*qualification,*degree;
    QListView *jobs,*contacts,*degrees;
    BasicContactViewer* basicViewer;
    QFrame *generalInfosFrame;

    enum grid{numGridRows=5,numGridCols=2};
    void initPersonalInformations();
    void initStudiesInformations();
    void initOccupationsInformations();
    void initNetworkAndInfos();

public:
    explicit ClientProfileWidget(LinQedInClient*,LinQedInUser* =0,QWidget* =0);
    void setupGui() const;
    void changeUserImage(const QString&) const;

protected:
    void resizeEvent(QResizeEvent*);
    void keyReleaseEvent(QKeyEvent*);

private slots:
    void viewContactProfile(const QModelIndex&);
    void removeFromNetwork(const QString&) const;
    void viewUserProfile(const LinQedInUser&);
    void addInNetwork(const QString&) const;
    void goHome();
};

#endif // ClientProfileWidget_H
