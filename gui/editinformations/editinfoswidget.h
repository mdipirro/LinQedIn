#ifndef EDITINFOSWIDGET_H
#define EDITINFOSWIDGET_H

#include <QFrame>
#include <QString>

class Information;
class UserData;
class LinQedInClient;
class Profile;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QPushButton;
class QLayout;
class QLineEdit;

class EditInfosWidget:public QFrame{
    Q_OBJECT

private:
    static int maxBWidth;
    static QString noInfos;

    const LinQedInClient* client;
    QWidget *mainWidget;
    QVBoxLayout *mainVerticalLayout;
    QHBoxLayout *buttonsLayout;
    QPushButton *saveB,*cancelB,*resetB,*logo;
    QLabel* header;

protected:
    void initButtons(bool =true,bool =true,bool =true);

public:
    static QString getInformationText(QLineEdit*);

    explicit EditInfosWidget(QWidget* =0,const QString& ="",const LinQedInClient* =0);
    void addWidgetToMainLayout(QWidget*,Qt::Alignment);
    void addLayoutToMainLayout(QLayout*);
    Profile getProfile() const;
    virtual ~EditInfosWidget();

signals:
    void save(const Profile&) const;
    void save(const UserData&) const;
    void cancelled() const;

protected slots:
    virtual void saveRequest() =0;
    virtual void writeDefaultValues() const =0;
    void cancel();
};

#endif // EDITINFOSWIDGET_H
