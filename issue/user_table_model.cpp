//
// Created by ztr53 on 19.06.2021.
//

#include "user_table_model.h"
#include <QBrush>

UserTableModel::UserTableModel(IssueService &s) : service{s}
{}
int UserTableModel::rowCount(const QModelIndex &parent) const
{
    return this->service.size();
}
int UserTableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}
QVariant UserTableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row(), column = index.column();
    Issue i = this->service[row];
    if (role == Qt::DisplayRole)
    {
        if (column == 0)return QString::fromStdString(i.getDescription());
        else if (column == 1)return QString::fromStdString(i.getStatus());
        else if (column == 2)return QString::fromStdString(i.getReporter());
        else if (column == 3)return QString::fromStdString(i.getSolver());
    }
    else if (role == Qt::TextAlignmentRole)
    {
        //if (column == 0 || column == 2 || column == 3 || column == 4 || column == 6)
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }
//    else if (role == Qt::FontRole)
//    {
//        if (row == 0 && column == 0)
//        {
//            QFont boldFont;
//            boldFont.setBold(true);
//            return boldFont;
//        }
//    }
    else if (role == Qt::BackgroundRole)
    {
        //if (row & 1)
            //return QBrush(Qt::lightGray);
    }
//    else if (role == Qt::CheckStateRole)
//    {
//        if (row == 1 && column == 0)
//            return Qt::Checked;
//    }
    return QVariant();
}
bool UserTableModel::setData(QModelIndex const &idx, QVariant const &value, int role)
{
    if (role == Qt::DisplayRole)
    {
        QModelIndex topLeft = index(0, 0);
        QModelIndex bottomRight = index(rowCount() - 1, columnCount() - 1);

        emit dataChanged(topLeft, bottomRight);
        emit layoutChanged();
        return true;
    }
    return false;
}
QVariant UserTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            if (section == 0)return QString("Description");
            else if (section == 1)return QString("Status");
            else if (section == 2)return QString("Reporter");
            else if (section == 3)return QString("Solver");
        }
    }
    return QVariant();
}
Qt::ItemFlags UserTableModel::flags(const QModelIndex &index) const
{
    //return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
bool UserTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    endInsertRows();
    return true;
}
bool UserTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
    return true;
}
