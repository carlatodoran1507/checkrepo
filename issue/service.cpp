//
// Created by ztr53 on 19.06.2021.
//

#include "service.h"
#include <algorithm>

UserService::UserService(Repository<User> &r) : repo(r)
{}
void UserService::store(const std::string &name, const std::string &type)
{
    User user{name, type};
    this->repo.store(user);
}
void UserService::update(const std::string &name, const std::string &type)
{
    User user{name, type};
    this->repo.update(user);
}
void UserService::remove(const std::string &name)
{
    User user{name, ""};
    this->repo.remove(user);
}
int UserService::size()
{
    return this->repo.size();
}
const User &UserService::operator[](int i) const
{
    return this->repo[i];
}
typename std::vector<User>::iterator UserService::begin()
{
    return this->repo.begin();
}
typename std::vector<User>::iterator UserService::end()
{
    return this->repo.end();
}
std::vector<User> UserService::get_sorted()
{
    auto elems = this->repo.get_elems();
    sort(elems.begin(), elems.end(), [](const auto &lhs, const auto &rhs) {
        return lhs.getType() < rhs.getType();
    });
    return elems;
}
std::vector<User> UserService::get_filtered(const std::string &type)
{
    auto elems = this->repo.get_elems();
    std::vector<User> result;
    for (const auto &e:elems)
        if (e.getType() == type)
            result.push_back(e);
    return result;
}
std::vector<User> UserService::get_elems()
{
    return this->repo.get_elems();
}
IssueService::IssueService(Repository<Issue> &r) : repo(r)
{}
void IssueService::store(const std::string &desc, const std::string &stat, const std::string &rep, const std::string &sol)
{
    Issue issue{desc, stat, rep, sol};
    this->repo.store(issue);
}
void IssueService::update(const std::string &desc, const std::string &stat, const std::string &rep, const std::string &sol)
{
    Issue issue{desc, stat, rep, sol};
    this->repo.update(issue);
}
void IssueService::remove(const std::string &desc)
{
    Issue issue{desc, "", "", ""};
    this->repo.remove(issue);
}
int IssueService::size()
{
    return this->repo.size();
}
const Issue &IssueService::operator[](int i) const
{
    return this->repo[i];
}
typename std::vector<Issue>::iterator IssueService::begin()
{
    return this->repo.begin();
}
typename std::vector<Issue>::iterator IssueService::end()
{
    return this->repo.end();
}
std::vector<Issue> IssueService::get_elems()
{
    return this->repo.get_elems();
}
