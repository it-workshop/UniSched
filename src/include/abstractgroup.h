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
class AbstractGroup: public ManagersObject, public UI::UsersObject {
friend class Group;
private:
    std::string name_;
                        /**< Name of the group. */

    std::vector<AbstractGroup *> child_groups_;
                        /**< Child groups. Them can be only groups not events. */
    
    std::vector<class Person *> people_;
                        /**< People of the group. */

protected:
    void add_child(AbstractGroup * group);
                        /**< @brief Method to add child group.
                         * @param group Group to add.
                         *
                         * This method does not controlls that group in not a
                         * child already. This check must be in function
                         * Group::add_parent(). That function must be only the
                         * one place where this caled from.
                         */

    void del_child(AbstractGroup * group);
                        /**< @brief Method to delete child group.
                         * @param group Group to delete.
                         *
                         * This method looks for requested group and deletes it.
                         * Group::del_parent() must be only the one place where
                         * this method called from.
                         */

    virtual void save();
                        /**< @brief Method to save all data in the manager.
                         *
                         * Declared in the ManagersObject. This method
                         * saves name, child groups and people. Inherited
                         * classes must to redefine and call this one.
                         */

    virtual void load();
                        /**< @brief Method to load all data from the manager.
                         *
                         * Declared in the ManagersObject. Thil method
                         * loads name, child groups and people. Inherited
                         * classes must to redefine and coll this one.
                         */

public:
    AbstractGroup(const int id, Manager& manager):
            ManagersObject(id, manager)
            {}
                        /**< @brief Constructor
                         * @param id Managers object`s identificator.
                         * @param manager Storage.
                         *
                         * This constructor called from inherited classes.
                         */

    AbstractGroup(const int id, Manager& manager,
        const std::string name):
            ManagersObject(id, manager), name_(name)
            {}
                        /**< @brief Constructor
                         * @param id Managers object`s identificotor.
                         * @param manager Storage.
                         * @param name Group`s name.
                         *
                         * @deprecated This constructor keeped for debug. Using
                         * can be very hard. Must be deleted later.
                         *
                         * This constructor called from inherited classes.
                         */

    const std::string name() const
            { return name_; }
                        /**< @brief Returns group`s name
                         * @return Name of group.
                         *
                         * @deprecated This method keeped for debug. Using can
                         * be comfortable, but not universal, you must to use
                         * UI::UsersObject::get_field_string("name") instead.
                         * Must be deleted later.
                         *
                         * Use this for debug.
                         */

    void add_person(Person * person);
                        /**< @brief Add person to the group.
                         * @param person Person to add.
                         *
                         * Do not use this directly. It must be moved into
                         * protected or private. This method called from update
                         * method.
                         */

    void del_person(Person * person);
                        /**< @brief Delete person from the group.
                         * @param person to delete.
                         *
                         * Do not use this directly. It must be moved into
                         * protected or private. This method called from update
                         * method.
                         */

    virtual const std::string read() const;
                        /**< @brief Returns full object information.
                         * @return Object`s information in the string.
                         *
                         * Method declared in the UI::UsersObject use to retrive
                         * all information about object.
                         *
                         * Inherited classes must to redefine and call this one.
                         */

    virtual const int read_int(const std::string name) const
                throw (std::bad_cast);
                        /**< @brief Return integer value of requested field.
                         * @param name Name of the field which must be returned.
                         * Ignored really.
                         * @return Integer value of requested field. Never
                         * return really.
                         *
                         * Call of this method possible from the user interface,
                         * but really useless. This method throws std::bad_cast
                         * directly.
                         */

    virtual const std::string read_string(const std::string name) const
                throw (std::bad_cast);
                        /**< @brief Return string value of requested field.
                         * @param name Name of the field which must be returned.
                         * @return String value of requested field.
                         *
                         * Use this for name field. Throws exception in other
                         * cases.
                         */

    virtual const time_t read_time(const std::string name) const
                throw (std::bad_cast);
                        /**< @brief Return time value of requested field.
                         * @param name Name of field which must be returned.
                         * Ignored really.
                         * @return Time value of requested field. Never return
                         * really.
                         *
                         * Call of this method possible from the user interface,
                         * but really useless. This method throws std::bad_cast
                         * directly. Method used in event class which redefines
                         * this.
                         */

    virtual const std::string read_enum(const std::string name) const
                throw (std::bad_cast);
                        /**< @brief Return enum value of requested field.
                         * @param name Name of field which must be returned.
                         * Ignored really.
                         * @return Time value of requested field. Never return
                         * really.
                         *
                         * Call of this method possible from the user interface,
                         * but really useless. This method throws std::bad_cast
                         * directly.
                         */

    virtual const std::vector<UI::UsersObject *>
    read_vector(const std::string name) const throw (std::bad_cast);
                        /**< @brief Return vector value of requested field.
                         * @param name Name of field which must be returned.
                         * @return Vector value of requested field.
                         *
                         * Use this for child_groups and people fields. Throws
                         * exception in the other cases.
                         */

    virtual void update(const std::string name, const int value)
                throw (std::bad_cast);
                        /**< @brief change current integer value of field.
                         * @param name Name of field which must be changed.
                         * Ignored really.
                         * @param value New value of field. Ignored really.
                         *
                         * Never return really.
                         *
                         * Call of this method possible from the user interface,
                         * but really useless. This method throws std::bad_cast
                         * directly.
                         */
                        
    virtual void update(const std::string name, const std::string value)
                throw (std::bad_cast);
                        /**< @brief change current string value of field.
                         * @param name Name of field which must be changed.
                         * @param value New value of field.
                         *
                         * Use this for name field. Throws exception in the
                         * other cases.
                         */

    virtual void update(const std::string name, const time_t value)
                throw (std::bad_cast);
                        /**< @brief change current time value of field.
                         * @param name Name of field which must be changed.
                         * Ignored really.
                         * @param value New value of field. Ignored really.
                         *
                         * Call of this method possible from the user interface,
                         * but really useless. This method throws std::bad_cast
                         * directly. Event class must to redefine this one.
                         */

    virtual void update_enum(const std::string name, const std::string value)
                throw (std::bad_cast);
                        /**< @brief change current enum value of field.
                         * @param name Name of field which must be changed.
                         * Ignored really.
                         * @param value New value of field. Ignored really.
                         *
                         * Call of this method possible from the user interface,
                         * but never useless. This method throws std::bad_cast
                         * directly.
                         */


    virtual void update(UI::UsersObject * object, const bool linked)
                throw (std::bad_cast);
                        /**< @brief change current link value of field.
                         * @param object Object link with that must be changed.
                         * @param linked New state of thi link.
                         *
                         * This method tries to add or delete object to the
                         * group as the Person. dynamic_cast will throw
                         * std::bad_cast if object is not Person.
                         *
                         * You can not set child group by this method use
                         * redefined method in Group class to add parent group.
                         */
};

};

