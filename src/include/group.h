#pragma once

#include <vector>

#include <abstractgroup.h>

namespace Core {

/**< @class Group
 * @brief Class keeps information about group of people.
 */
class Group: protected AbstractGroup {
private:
    std::vector<AbstractGroup const *> parent_groups_;
    std::vector<AbstractGroup const *>::iterator parent_groups_iterator_;

    virtual void save();
    virtual void load();

public:
    void add_parent_group(AbstractGroup *group);
    void del_parent_group(AbstractGroup *group);

    AbstractGroup const * first_parent_group() { parent_groups_iterator_ = parent_groups_.begin(); return *parent_groups_iterator_++; }
    AbstractGroup const * next_parent_group() { return *parent_groups_iterator_++; }
    const bool has_next_parent_group() { return parent_groups_iterator_ != parent_groups_.end(); }
};

};

