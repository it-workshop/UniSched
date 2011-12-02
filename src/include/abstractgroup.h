#pragma once

#include <string>
#include <vector>

#include <storage.h>
#include <person.h>

namespace Core {

class AbstractGroup: public Storage::StorableObject {
friend class Group;
private:
    const std::string name_;
    std::vector<AbstractGroup const *> child_groups_;
    std::vector<class Person const *> people_;

protected:
    void add_child(AbstractGroup const * group) { child_groups_.push_back(group); }
    void del_child(AbstractGroup const * group);

public:
    AbstractGroup(const int id, Storage::AbstractStorage& storage, const std::string name):
            StorableObject(id, storage), name_(name) {}

    const std::string name() const { return name_; }

    void add_person(Person * person);
    void del_person(Person * person);

};

};

