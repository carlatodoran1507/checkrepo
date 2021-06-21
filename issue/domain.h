//
// Created by ztr53 on 19.06.2021.
//

#ifndef ISSUE_DOMAIN_H
#define ISSUE_DOMAIN_H

#include <string>

class User
{
private:
    std::string name;
    std::string type;
public:
    User() = default;
    User(const std::string &, const std::string &);
    bool operator==(const User &other) const;
    friend std::istream &operator>>(std::istream &is, User &u);
    friend std::ostream &operator<<(std::ostream &os, const User &u);
    const std::string &getName() const;
    void setName(const std::string &name);
    const std::string &getType() const;
    void setType(const std::string &type);
    bool empty()
    {
        return this->name.empty() && this->type.empty();
    }
    std::string to_string()const;
};

class Issue
{
private:
    std::string description{};
    std::string status{};
    std::string reporter{};
    std::string solver{};
public:
    Issue() = default;
    Issue(const std::string &, const std::string &, const std::string &, const std::string &);
    bool operator==(const Issue &other) const;
    friend std::istream &operator>>(std::istream &is, Issue &i);
    friend std::ostream &operator<<(std::ostream &os, const Issue &i);
    const std::string &getDescription() const;
    void setDescription(const std::string &description);
    const std::string &getStatus() const;
    void setStatus(const std::string &status);
    const std::string &getReporter() const;
    void setReporter(const std::string &reporter);
    const std::string &getSolver() const;
    void setSolver(const std::string &solver);
    bool empty()
    {
        return this->description.empty() && this->status.empty() && this->reporter.empty() && this->solver.empty();
    }
    std::string to_string() const;
};

#endif //ISSUE_DOMAIN_H
