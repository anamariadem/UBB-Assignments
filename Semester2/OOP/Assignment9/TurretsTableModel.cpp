//
// Created by Ana Maria on 29/05/2020.
//

#include <QBrush>
#include <QDebug>
#include "TurretsTableModel.h"

int TurretsTableModel::rowCount(const QModelIndex &parent) const {
    qDebug()<<"sizeeeeee"<<this->service.getAllSavedTurrets().size();
    return this->service.getAllSavedTurrets().size();
}

int TurretsTableModel::columnCount(const QModelIndex &parent) const {
    return 5;
}

QVariant TurretsTableModel::data(const QModelIndex &index, int role) const {

    int row = index.row();
    int column = index.column();

    auto turets = this->service.getAllSavedTurrets();
    auto currentTurret = turets[row];
    qDebug() << row<<" " <<column;
    if(role == Qt::DisplayRole){
        qDebug()<<row;
        switch (column){
            case 0:
                return QString::fromStdString(currentTurret.getLocationOfTurret());
            case 1:
                return QString::fromStdString(currentTurret.getSizeOfTurret());
            case 2:
                return QString::number(currentTurret.getAuraLevelOfTurret());
            case 3:
                return QString::number(currentTurret.getNumberOfSeparatePartsOfTurret());
            case 4:
                return QString::fromStdString(currentTurret.getVisionOfTurret());
            default:
                break;
        }
    }
    if(role == Qt::BackgroundRole){
        if(row%2 == 1) {
            return QBrush{QColor{102, 0, 204}};
        }
    }

    return QVariant();
}


QVariant TurretsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {

    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch (section){
                case 0:
                    return QString("Location");
                case 1:
                    return QString("Size");
                case 2:
                    return QString("Aura level");
                case 3:
                    return QString("Separate parts");
                case 4:
                    return QString("Vision");
                default:
                    break;
            }
        }
    }

    return QVariant();
}

QModelIndex TurretsTableModel::index(int row, int column, const QModelIndex &parent) const {
    return createIndex(row, column, nullptr);
}
/*
bool TurretsTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if(role != Qt::EditRole)
        return false;
    int row = index.row();
    int column = index.column();

    NorvenTurret& turret = this->service.getAllSavedTurrets()[row];
    switch(column){
        case 0:
            break;
        case 1: {
            std::string size = value.toString().toStdString();
            turret.setSizeOfTurret(size);
            break;
        }
        case 2 : {
            std::string auraLevel = value.toString().toStdString();
            turret.setAuraLevelOfTurret(std::stoi(auraLevel));
            break;
        }
        case 3: {
            std::string separateParts = value.toString().toStdString();
            turret.setNumberOfSeparatePartsOfTurret(std::stoi(separateParts));
        }
        case 4: {
            std::string vision = value.toString().toStdString();
            turret.setVisionOfTurret(vision);
        }
        default:
            break;

    }

    return false;
}

Qt::ItemFlags TurretsTableModel::flags(const QModelIndex& index) const {
    int column = index.column();
    if(column == 0)
        return Qt::ItemFlags();
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
*/