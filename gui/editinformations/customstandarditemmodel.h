#ifndef CUSTOMSTANDARDITEMMODEL_H
#define CUSTOMSTANDARDITEMMODEL_H

#include <QStandardItemModel>
#include <QVector>

class QModelIndex;

/*
 * Estensione di QStandardItemModel per permettere campi non editabili
 */

class CustomStandardItemModel:public QStandardItemModel{
private:
    QVector<int> notEditable;
public:
    CustomStandardItemModel(const QVector<int>&,int,int);
protected:
   Qt::ItemFlags flags(const QModelIndex&) const;
};

#endif // CUSTOMSTANDARDITEMMODEL_H
