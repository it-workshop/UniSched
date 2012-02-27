#pragma once

#include <string>
#include <vector>

#include <object.h>
#include <person.h>

/**@namespace Core
 * @brief Core model classes.
 */
namespace Core {

/**@class AbstractGroup
 * @brief Base group functionality. You need to use it instead of Group or
 * Event in most cases.
 *
 * This is a generalization of groups and events. It allows to work easy with
 * them. It have not parent group as an Event, but Group have.
 */
class AbstractGroup: public Object {
friend class Group;
private:
    FieldString name_;
                        /**< Name of the group. */

    FieldVector child_groups_;
                        /**< Child groups. Them can be only groups not events.
                         */
    
    FieldVector people_;
                        /**< People of the group. */

protected:
    void add_child(AbstractGroup * group);
                        /**< @brief Add child group to this one.
                         * @param group Group to add.
                         * @internal For use in Core::Group::update method only.
                         *
                         * You must not use this method directly. Use update
                         * methods instead.
                         */

    void del_child(AbstractGroup * group);
                        /**< @brief Delete child group from this one.
                         * @param group Group to delete.
                         * @intertal For use in Core::Group::update method only.
                         *
                         * You must not use this method directly Use update
                         * methods instead.
                         */

public:
    AbstractGroup(const int id, AbstractUI& ui) throw(std::bad_cast);
                        /**< @brief Constructor
                         * @param id AbstractUIs object`s identificator.
                         * @param ui Storage.
                         * @internal This constructor called from inherited
                         * classes.
                         */

    virtual const Field& read(const std::string& name) const
        throw(std::bad_cast);
                        /**< @copydoc Core::Object::read()
                         * Get values of fields with those names: "name",
                         * "people", "child_groups".
                         *
                         * Method returns object of Core::FieldString or
                         * Core::FieldVector types.
                         */

    virtual void update(const Field& field) throw(std::bad_cast);
                        /**< @copydoc Core::Object::update()
                         * Change values of fields with those names: "name",
                         * "people", "child_groups".
                         *
                         * Methods accepts object of Core::FieldString,
                         * Core::FieldLink or Core::FieldVector types.
                         */
};

};

