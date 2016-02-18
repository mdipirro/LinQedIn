#ifndef BASICUSERVIEWER_H
#define BASICUSERVIEWER_H

#include <QFrame>

class LinQedInUser;
class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QString;

class BasicUserViewer:public QFrame{
    Q_OBJECT
private:
    QLabel *image,*username,*name,*plan,*espireDate;
    QHBoxLayout *mainHorizontalLayout;
    QVBoxLayout *infosLayout;
    QPushButton *deleteUser,*changePlan;

public:
    explicit BasicUserViewer(const LinQedInUser&,QWidget* =0);

signals:
    void deleteRequest(const QString&) const;
    void changePlanRequest(const QString&,int) const;

public slots:
    void emitDeleteRequest() const;
    void openPlanDialog() const;
    void emitChangePlanRequest(int) const;
};

#endif // BASICUSERVIEWER_H
