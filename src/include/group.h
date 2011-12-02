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

public:
    void add_parent_group(AbstractGroup *group);
    void del_parent_group(AbstractGroup *group);
};

};

