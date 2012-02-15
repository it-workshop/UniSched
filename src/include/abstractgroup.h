#pragma once

#include <string>
#include <vector>

#include <manageableobject.h>
#include <person.h>

/**@namespace Core
 * @brief Core model classes.
 */
namespace Core {

/**@class AbstractGroup
 * @brief Base group functionality. You need to use it instead of Group or
 * Event in most cases.
 *
 * This is a generalization of groups and events. It allows to work with them
 * easy. It have not parent group as an Event, but Group have.
 */
class AbstractGroup: public ManageableObject, public UI::UsersObject {
friend class Group;
private:
    FieldString name_;
                        /**< Name of the group. */

    FieldVector child_groups_;
                        /**< Child groups. Them can be only groups not events. */
    
    FieldVector people_;
                        /**< People of the group. */

protected:
    void add_child(AbstractGroup * group);
    void del_child(AbstractGroup * group);

public:
    AbstractGroup(const int id, Manager& manager) throw(std::bad_cast);
                        /**< @brief Constructor
                         * @param id Managers object`s identificator.
                         * @param manager Storage.
                         *
                         * This constructor called from inherited classes.
                         */

    virtual const Field& read(const std::string& name) const throw(std::bad_cast);
    virtual void update(const Field& field) throw(std::bad_cast);
};

};

