//
// Created by ztr53 on 19.06.2021.
//

#ifndef ISSUE_GUI_H
#define ISSUE_GUI_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include "service.h"
#include "user_table_model.h"

class UserGUI : public QDialog
{
Q_OBJECT
private:
    User &user;
    IssueService &issue_service;
    QAbstractItemModel *user_table_model;
    QTableView *user_table_view;
    QPushButton *add_issue;
    QLineEdit *issue_description;
    QPushButton *resolve_issue;
    QPushButton *remove_issue;

public:
    explicit UserGUI(User &, QAbstractItemModel *, IssueService &, QWidget *parent = 0);
private:
    void init_gui();
    void connect_signals_and_slots();
    int get_selected_index() const;
    void add_issue_handler();
    void remove_issue_handler();
    void resolve_issue_handler();
};

#endif //ISSUE_GUI_H
