#include <iostream>
#include <sstream>
#include <iomanip>
#include <QApplication>
#include <QLabel>
#include <QFile>
#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "domain.h"
#include "repository.h"
#include "service.h"
#include "gui.h"
#include "user_table_model.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    FileRepository<User> user_repo{"../users.csv"};
    FileRepository<Issue> issue_repo{"../issues.csv"};
    UserService user_service{user_repo};
    IssueService issue_service{issue_repo};
    auto *table_model = new UserTableModel{issue_service};
    auto sorted_model = new QSortFilterProxyModel{};
    sorted_model->setSourceModel(table_model);
    sorted_model->sort(0);
    sorted_model->sort(1);
    sorted_model->moveToThread(qApp->thread());
    auto users = user_service.get_elems();
    for (auto &u:users)
    {
        auto *gui = new UserGUI{u, sorted_model, issue_service};
        gui->resize(800, 600);
        gui->setWindowTitle(QString::fromStdString(u.getName() + " - " + u.getType()));
        gui->show();
    }

    return a.exec();
}
