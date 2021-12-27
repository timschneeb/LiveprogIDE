#include "VariableItemModel.h"

VariableItemModel::VariableItemModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int VariableItemModel::rowCount(const QModelIndex &parent) const
{
#ifndef HAS_JDSP_DRIVER
    return 0;
#else
    if (parent.isValid())
        return 0;

    return variables.size();
#endif
}

int VariableItemModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 2;
}

QVariant VariableItemModel::data(const QModelIndex &index, int role) const
{
#ifndef HAS_JDSP_DRIVER
    return QVariant();
#else
    if (!index.isValid())
        return QVariant();

    if(role != Qt::DisplayRole)
        return QVariant();

    auto var = variables[index.row()];
    switch(index.column())
    {
    case 0:
        return QString::fromStdString(var.name);
    case 1:
        return std::holds_alternative<std::string>(var.value) ? QVariant(QString::fromStdString(std::get<std::string>(var.value))) : QVariant(std::get<float>(var.value));
    default:
        return QVariant();
    }
#endif
}

QVariant VariableItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return {};
    switch (section) {
    case 0: return "Parameter";
    case 1: return "Value";
    default: return {};
    }
}

#ifdef HAS_JDSP_DRIVER
void VariableItemModel::onLiveprogVariablesUpdated(const std::vector<EelVariable> &vars)
{
    beginResetModel();
    variables = vars;
    endResetModel();
}
#endif
