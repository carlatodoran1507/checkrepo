//
// Created by ztr53 on 19.06.2021.
//

#include "gui.h"
#include <QVBoxLayout>
#include <QMessageBox>

UserGUI::UserGUI(User &u, QAbstractItemModel *model, IssueService &s, QWidget *parent) : user_table_model{model},
                                                                                         user{u},
                                                                                         issue_service{s},
                                                                                         QDialog(parent)
{
    this->init_gui();
    this->connect_signals_and_slots();
}
void UserGUI::init_gui()
{
    //this->user_table_model = new UserTableModel{this->issue_service};
    this->user_table_view = new QTableView{};
    this->user_table_view->setSortingEnabled(true);
    this->user_table_view->setModel(this->user_table_model);
    this->user_table_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->user_table_view->setSelectionMode(QAbstractItemView::SingleSelection);

    this->add_issue = new QPushButton{"Add"};
    this->resolve_issue = new QPushButton{"Resolve"};
    this->remove_issue = new QPushButton{"Remove selected issue"};
    this->issue_description = new QLineEdit{};

    auto *main_layout = new QVBoxLayout{this};
    main_layout->addWidget(this->user_table_view);

    if (this->user.getType() == "tester")
    {
        main_layout->addWidget(this->issue_description);
        main_layout->addWidget(this->add_issue);
        main_layout->addWidget(this->remove_issue);
    }
    else
    {
        main_layout->addWidget(this->resolve_issue);
        main_layout->addWidget(this->remove_issue);
    }
}
void UserGUI::connect_signals_and_slots()
{
    QObject::connect(this->user_table_view->selectionModel(), &QItemSelectionModel::selectionChanged, this,
                     [this]() {
                         int selected_index = this->get_selected_index();
                         if (selected_index < 0)
                             return;
                         Issue i = this->issue_service[selected_index];
                         //this->get_movie_id->setText(QString::fromStdString(std::to_string(m.get_id())));
                     });
    QObject::connect(this->add_issue, &QPushButton::clicked, this, &UserGUI::add_issue_handler);
    QObject::connect(this->remove_issue, &QPushButton::clicked, this, &UserGUI::remove_issue_handler);
    QObject::connect(this->resolve_issue, &QPushButton::clicked, this, &UserGUI::resolve_issue_handler);
}
int UserGUI::get_selected_index() const
{
//    QModelIndexList selected_indexes = this->watchlist_table_view->selectionModel()->selection().indexes();
    QModelIndexList selected_indexes = this->user_table_view->selectionModel()->selectedRows();
    if (selected_indexes.empty())
    {
        //this->get_movie_id->clear();
        return -1;
    }
    int selected_index = selected_indexes.at(0).row();
    return selected_index;
}
void UserGUI::add_issue_handler()
{
    std::string desc = this->issue_description->text().toStdString();
    if (desc.empty())
    {
        QMessageBox err;
        err.setText("No description given!");
        err.exec();
        return;
    }
    try
    {
        this->issue_service.store(desc, "open", this->user.getName(), "-");
        this->user_table_model->insertRow(this->user_table_model->rowCount(QModelIndex()));
    } catch (const std::exception &e)
    {
        QMessageBox err;
        err.setText(e.what());
        err.exec();
    }
}
void UserGUI::remove_issue_handler()
{
    try
    {
        int selected_index = this->get_selected_index();
        std::string desc = this->user_table_view->model()->index(selected_index, 0).data().toString().toStdString();
        std::string stat = this->user_table_view->model()->index(selected_index, 1).data().toString().toStdString();
        if (stat == "closed")
        {
            this->issue_service.remove(desc);
            this->user_table_model->removeRow(selected_index);
        }
    } catch (const std::exception &e)
    {
        QMessageBox err;
        err.setText(e.what());
        err.exec();
    }
}
void UserGUI::resolve_issue_handler()
{
    int selected_index = this->get_selected_index();
    std::string desc = this->user_table_view->model()->index(selected_index, 0).data().toString().toStdString();
    std::string stat = this->user_table_view->model()->index(selected_index, 1).data().toString().toStdString();
    std::string reporter = this->user_table_view->model()->index(selected_index, 2).data().toString().toStdString();
    if (stat == "open")
    {
        this->issue_service.update(desc, "closed", reporter, this->user.getName());
        emit this->user_table_model->dataChanged(QModelIndex(), QModelIndex());
    }
}
