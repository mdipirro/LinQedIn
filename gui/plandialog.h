#ifndef PLANDIALOG_H
#define PLANDIALOG_H

#include <QDialog>

class QGroupBox;
class QDialogButtonBox;
class QRadioButton;
class QVBoxLayout;

class PlanDialog:public QDialog{
    Q_OBJECT
public:
    enum ReturnMode{idOnly,idAndDescription};
    explicit PlanDialog(QWidget* =0,ReturnMode =idOnly);

private:
    QString username;
    ReturnMode mode;
    QVBoxLayout* mainLayout;
    QDialogButtonBox *buttonBox;
    QRadioButton *basic,*business,*executive;

    QGroupBox *createGroupBox();

    class Plan{
    public:
        int id;
        QString description;
        Plan(int,const QString&);
    };

signals:
    void planSelected(int) const;
    void planSelected(int,const QString&) const;

public slots:
    void confirmed();
};

#endif // PLANDIALOG_H
