//
// Created by ztr53 on 19.06.2021.
//

#include <vector>
#include <sstream>
#include "domain.h"

User::User(const std::string &n, const std::string &t) : name(n), type(t)
{}
const std::string &User::getName() const
{
    return this->name;
}
void User::setName(const std::string &n)
{
    this->name = n;
}
const std::string &User::getType() const
{
    return this->type;
}
void User::setType(const std::string &t)
{
    this->type = t;
}
bool User::operator==(const User &other) const
{
    return this->name == other.name;
}
std::vector<std::string> split(const std::string &str, char delim)
{
    std::vector<std::string> parts;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delim))
        parts.push_back(token);
    return parts;
}
std::istream &operator>>(std::istream &is, User &u)
{
    std::string line;
    getline(is, line);
    std::vector<std::string> parts = split(line, ',');
    if (parts.size() != 2)
        return is;
    u.name = parts[0];
    u.type = parts[1];
    return is;
}
std::ostream &operator<<(std::ostream &os, const User &u)
{
    os << u.name << "," << u.type;
    return os;
}
std::string User::to_string() const
{
    return this->name + "\n" + this->type;
}
const std::string &Issue::getDescription() const
{
    return description;
}
void Issue::setDescription(const std::string &description)
{
    Issue::description = description;
}
const std::string &Issue::getStatus() const
{
    return status;
}
void Issue::setStatus(const std::string &status)
{
    Issue::status = status;
}
const std::string &Issue::getReporter() const
{
    return reporter;
}
void Issue::setReporter(const std::string &reporter)
{
    Issue::reporter = reporter;
}
const std::string &Issue::getSolver() const
{
    return solver;
}
void Issue::setSolver(const std::string &solver)
{
    Issue::solver = solver;
}
Issue::Issue(const std::string &d, const std::string &s, const std::string &r, const std::string &sol) : description(d),
                                                                                                         status(s),
                                                                                                         reporter(r),
                                                                                                         solver(sol)
{}
bool Issue::operator==(const Issue &other) const
{
    return this->description == other.description;
}
std::istream &operator>>(std::istream &is, Issue &i)
{
    std::string line;
    getline(is, line);
    std::vector<std::string> parts = split(line, ',');
    if (parts.size() != 4)
        return is;
    i.description = parts[0];
    i.status = parts[1];
    i.reporter = parts[2];
    i.solver = parts[3];
    return is;
}
std::ostream &operator<<(std::ostream &os, const Issue &i)
{
    os << i.description << "," << i.status << "," << i.reporter << "," << i.solver;
    return os;
}
std::string Issue::to_string() const
{
    return "Description: " + this->description + "\nStatus: " + this->status + "\nReporter: " + this->reporter +
           "\nSolver: " + this->solver + "\n";
}
