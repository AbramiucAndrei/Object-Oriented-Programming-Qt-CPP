//
// Created by Mihai Adomnitei on 24.05.2024.
//

#include "TableModel.hpp"

TableModel::TableModel(Service &service, QObject *parent) : QAbstractTableModel(parent), service(service) {
    records = service.getAllFarma();
}

int TableModel::rowCount(const QModelIndex &parent) const {
    return (int) records.size();
}

int TableModel::columnCount(const QModelIndex &parent) const {
    return 4;
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return {};
    }

    const auto &meds = records;
    const auto &med = meds[index.row()];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
            case 0:return QString::fromStdString(med.getDenumire());
            case 1:return QString::fromStdString(med.getProducator());
            case 2:return QString::fromStdString(med.getSubstActiva());
            case 3:return med.getPret();
            default:return {};
        }
    }

    return {};
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return {};
    }

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:return "Denumire";
            case 1:return "Producator";
            case 2:return "Substanta Activa";
            case 3:return "Pret";
            default:return {};
        }
    }

    return {};
}

void TableModel::updateModel() {
    beginResetModel();
    endResetModel();
}

void TableModel::setRecords(std::vector<Medicament> rec) {
    records = std::move(rec);
    updateModel();
}

void TableModel::refreshModel() {
    records = service.getAllFarma();
    updateModel();
}