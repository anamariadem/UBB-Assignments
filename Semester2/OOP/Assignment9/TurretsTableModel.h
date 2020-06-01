//
// Created by Ana Maria on 29/05/2020.
//

#ifndef ASSIGNMENT9_VERSION2_TURRETSTABLEMODEL_H
#define ASSIGNMENT9_VERSION2_TURRETSTABLEMODEL_H


#include <QAbstractTableModel>
#include "Service.h"

class TurretsTableModel : public QAbstractTableModel {
private:
    Service& service;

public:
    TurretsTableModel(Service& serviceToBuild) : service{serviceToBuild} {}
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override ;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override ;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const  override;

    QModelIndex index(int row, int column, const QModelIndex& parent) const override ;
    //bool setData(const QModelIndex& index, const QVariant& value, int role =  Qt::EditRole) override;
    //Qt::ItemFlags flags(const QModelIndex& index) const override ;
};


#endif //ASSIGNMENT9_VERSION2_TURRETSTABLEMODEL_H
