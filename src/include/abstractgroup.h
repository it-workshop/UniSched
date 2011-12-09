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

    std::vector<AbstractGroup const *> child_groups_;
    std::vector<AbstractGroup const *>::iterator child_groups_iterator_;
    
    std::vector<class Person const *> people_;
    std::vector<class Person const *>::iterator people_iterator_;

protected:
    void add_child(AbstractGroup const * group) { child_groups_.push_back(group); }
    void del_child(AbstractGroup const * group);

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

    AbstractGroup const * first_child_group() { child_groups_iterator_ = child_groups_.begin(); return *child_groups_iterator_++; }
    AbstractGroup const * next_child_group() { return *child_groups_iterator_++; }
    const bool has_next_child_group() const { return child_groups_iterator_ != child_groups_.end(); }

    class Person const * first_person() { people_iterator_ = people_.begin(); return *people_iterator_++; }
    class Person const * next_person() { return *people_iterator_++; }
    const bool has_next_person() const { return people_iterator_ != people_.end(); }
};

};

