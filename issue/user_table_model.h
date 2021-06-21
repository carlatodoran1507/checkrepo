//
// Created by ztr53 on 19.06.2021.
//

#ifndef ISSUE_USER_TABLE_MODEL_H
#define ISSUE_USER_TABLE_MODEL_H

#include <QAbstractItemModel>
#include "service.h"

class UserTableModel : public QAbstractTableModel
{
private:
    IssueService &service;
public:
    explicit UserTableModel(IssueService &s);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(QModelIndex const &idx, QVariant const &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
};

#endif //ISSUE_USER_TABLE_MODEL_H
