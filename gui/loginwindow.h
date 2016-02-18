#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class QLineEdit;
class QPushButton;
class LinQedInClient;

#include <QFrame>

class LoginWindow:public QFrame{
    Q_OBJECT

private:
    QVBoxLayout *mainVerticalLayout,*vlUsername,*vlPwd;
    QLabel *lImage,*lUsername,*lPwd,*lError;
    QHBoxLayout *loginLayout;
    QLineEdit *teUsername,*tePwd;
    QPushButton *loginButton,*adminButton;

public:
    explicit LoginWindow(QWidget* =0);

public slots:
    void login();
    void admin();
};

#endif // LOGINWINDOW_H
