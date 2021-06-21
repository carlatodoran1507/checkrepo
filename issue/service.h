//
// Created by ztr53 on 19.06.2021.
//

#ifndef ISSUE_SERVICE_H
#define ISSUE_SERVICE_H

#include "domain.h"
#include "repository.h"

class UserService
{
private:
    Repository<User> &repo;
public:
    explicit UserService(Repository<User> &r);
    void store(const std::string &, const std::string &);
    void update(const std::string &, const std::string &);
    void remove(const std::string &);
    int size();
    const User &operator[](int i) const;
    typename std::vector<User>::iterator begin();
    typename std::vector<User>::iterator end();
    std::vector<User> get_sorted();
    std::vector<User> get_filtered(const std::string &);
    std::vector<User> get_elems();
};

class IssueService
{
private:
    Repository<Issue> &repo;
public:
    explicit IssueService(Repository<Issue> &r);
    void store(const std::string &, const std::string &, const std::string &, const std::string &);
    void update(const std::string &, const std::string &, const std::string &, const std::string &);
    void remove(const std::string &);
    int size();
    const Issue &operator[](int i) const;
    typename std::vector<Issue>::iterator begin();
    typename std::vector<Issue>::iterator end();
    std::vector<Issue> get_elems();
    //std::vector<Issue> get_sorted();
    //std::vector<Issue> get_filtered(const std::string &);
};

#endif //ISSUE_SERVICE_H
