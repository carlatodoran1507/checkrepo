//
// Created by ztr53 on 19.06.2021.
//

#ifndef ISSUE_REPOSITORY_H
#define ISSUE_REPOSITORY_H

#include <domain.h>
#include <vector>
#include <fstream>

template<class TElem>
class Repository
{
protected:
    std::vector<TElem> elems;
public:
    int search(const TElem &item);
    virtual void store(const TElem &);
    virtual void update(const TElem &);
    virtual void remove(const TElem &);
    const TElem &operator[](int i) const;
    int size();
    std::vector<TElem> get_elems();
    //typename std::vector<TElem>::const_iterator begin() const;
    //typename std::vector<TElem>::const_iterator end() const;
    typename std::vector<TElem>::iterator begin();
    typename std::vector<TElem>::iterator end();
};

template<class TElem>
void Repository<TElem>::store(const TElem &elem)
{
    if (this->search(elem) != -1)
        throw std::runtime_error("Elem already exists!\n");
    this->elems.push_back(elem);
}
template<class TElem>
int Repository<TElem>::search(const TElem &elem)
{
    int i = 0;
    for (const auto &e:this->elems)
    {
        if (e == elem)
            return i;
        i++;
    }
    return -1;
}
template<class TElem>
void Repository<TElem>::update(const TElem &elem)
{
    int index = this->search(elem);
    if (index == -1)
        throw std::runtime_error("Elem doesn't exist!\n");
    this->elems[index] = elem;
}
template<class TElem>
void Repository<TElem>::remove(const TElem &elem)
{
    int index = this->search(elem);
    if (index == -1)
        throw std::runtime_error("Elem doesn't exist!\n");
    this->elems.erase(this->elems.begin() + index);
}
template<class TElem>
const TElem &Repository<TElem>::operator[](int i) const
{
    return this->elems[i];
}
template<class TElem>
std::vector<TElem> Repository<TElem>::get_elems()
{
    return this->elems;
}
template<class TElem>
int Repository<TElem>::size()
{
    return this->elems.size();
}
template<class TElem>
typename std::vector<TElem>::iterator Repository<TElem>::begin()
{
    return this->elems.begin();
}
template<class TElem>
typename std::vector<TElem>::iterator Repository<TElem>::end()
{
    return this->elems.end();
}

template<class TElem>
class FileRepository : public Repository<TElem>
{
private:
    std::string file_path;
    void read_from_file();
    void write_to_file();
public:
    explicit FileRepository(const std::string &);
    void store(const TElem &) override;
    void update(const TElem &) override;
    void remove(const TElem &) override;
};

template<class TElem>
FileRepository<TElem>::FileRepository(const std::string &txt): file_path(txt)
{
    this->read_from_file();
}
template<class TElem>
void FileRepository<TElem>::read_from_file()
{
    std::ifstream fin;
    fin.open(this->file_path);
    if (!fin.is_open())
        throw std::runtime_error("Error on opening file!\n");
    while (!fin.eof())
    {
        TElem elem;
        try
        {
            fin >> elem;
            if (!elem.empty())
                Repository<TElem>::store((const TElem &) elem);
        }
        catch (...)
        {}
    }
    fin.close();
}
template<class TElem>
void FileRepository<TElem>::write_to_file()
{
    std::ofstream fout;
    fout.open(this->file_path);
    if (!fout.is_open())
        throw std::runtime_error("Error on opening file!\n");
    for (auto &elem:Repository<TElem>::elems)
        if (!elem.empty())
            fout << elem << '\n';
    fout.close();
}
template<class TElem>
void FileRepository<TElem>::store(const TElem &elem)
{
//    this->read_from_file();
    Repository<TElem>::store(elem);
    this->write_to_file();
}
template<class TElem>
void FileRepository<TElem>::update(const TElem &elem)
{
//    this->read_from_file();
    Repository<TElem>::update(elem);
    this->write_to_file();
}
template<class TElem>
void FileRepository<TElem>::remove(const TElem &elem)
{
//    this->read_from_file();
    Repository<TElem>::remove(elem);
    this->write_to_file();
}


#endif //ISSUE_REPOSITORY_H
