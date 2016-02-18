#ifndef BASICCONTACTVIEWER_H
#define BASICCONTACTVIEWER_H

#include "controller/linqedinuser.h"
#include <QFrame>

class QWidget;
class QLabel;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QString;

class BasicContactViewer:public QFrame{
    Q_OBJECT

private:
    LinQedInUser user;
    QLabel *name,*email,*actualJob;
    QPushButton *viewProfile,*removeContact,*addContact;
    QVBoxLayout *mainVerticalLayout;
    QHBoxLayout *buttonsLayout;

    void leaveEvent(QEvent*);

public:
    explicit BasicContactViewer(const LinQedInUser&,QWidget* =0);

signals:
    void removalRequest(const QString&) const;
    void viewRequest(const LinQedInUser&) const;
    void addingRequest(const QString&) const;

private slots:
    void sendRemovalRequest() const;
    void sendViewRequest() const;
    void sendAddingRequest() const;
};

#endif // BASICCONTACTVIEWER_H
