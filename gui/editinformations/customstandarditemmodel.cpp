#include "customstandarditemmodel.h"

CustomStandardItemModel::CustomStandardItemModel(const QVector<int>& ne,int r,int c):QStandardItemModel(r,c),notEditable(ne){}

Qt::ItemFlags CustomStandardItemModel::flags(const QModelIndex& index) const{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if(notEditable.indexOf(index.column())==-1){
        flags|=Qt::ItemIsEditable;
        return flags;
    }//if
    return QAbstractItemModel::flags(index);
}//flags
