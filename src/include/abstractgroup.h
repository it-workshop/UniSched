#pragma once

#include <string>
#include <vector>

#include <storableobject.h>
#include <person.h>

namespace Core {

class AbstractGroup: public Storage::StorableObject, public UI::UsersObject {
friend class Group;
private:
    std::string name_;

    std::vector<AbstractGroup *> child_groups_;
    
    std::vector<class Person *> people_;

protected:
    void add_child(AbstractGroup * group) { child_groups_.push_back(group); }
    void del_child(AbstractGroup * group);

    virtual void save();
    virtual void load();

public:
    AbstractGroup(const int id, Storage::AbstractStorage& storage):
            StorableObject(id, storage) {}
    AbstractGroup(const int id, Storage::AbstractStorage& storage, const std::string name):
            StorableObject(id, storage), name_(name) {}

    const std::string name() const { return name_; }

    void add_person(Person * person);
    void del_person(Person * person);

    virtual const std::string read() const;

    virtual const int read_int(const std::string name) const throw (std::bad_cast);
    virtual const std::string read_string(const std::string name) const throw (std::bad_cast);
    virtual const time_t read_time(const std::string name) const throw (std::bad_cast);
    virtual const std::string read_enum(const std::string name) const throw (std::bad_cast);
    virtual const std::vector<UI::UsersObject *> read_vector(const std::string name) const throw (std::bad_cast);

    virtual void update(const std::string name, const int value) throw (std::bad_cast);
    virtual void update(const std::string name, const std::string value) throw (std::bad_cast);
    virtual void update(const std::string name, const time_t value) throw (std::bad_cast);
    virtual void update_enum(const std::string name, const std::string value) throw (std::bad_cast);
    virtual void update(UI::UsersObject * object, const bool linked) throw (std::bad_cast);

};

};

