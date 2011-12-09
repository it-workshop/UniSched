#pragma once

#include <vector>

#include <abstractgroup.h>

namespace Core {

/**< @class Group
 * @brief Class keeps information about group of people.
 */
class Group: public AbstractGroup {
private:
    std::vector<AbstractGroup *> parent_groups_;

    virtual void save();
    virtual void load();

public:
    Group(const int id, Storage::AbstractStorage& storage):
            AbstractGroup(id, storage)
            {}

    void add_parent_group(AbstractGroup *group);
    void del_parent_group(AbstractGroup *group);

    virtual const std::string read() const;
    virtual const std::vector<UI::UsersObject *> read_vector(const std::string name) const throw (std::bad_cast);
    virtual void update(UI::UsersObject * object, const bool linked) throw (std::bad_cast);
};

};

