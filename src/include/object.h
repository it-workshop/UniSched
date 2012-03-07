#pragma once

#include <string>
#include <vector>

namespace Core {

enum obj_t {UNKNOWN, PERSON, GROUP, EVENT};
typedef const unsigned int objid_t;

/**< @class Object
 * @brief Universal interface of core objects.
 */
class Object {
friend class AbstractUI;
/* TODO: Add database class to friend when create this. */
private:
    obj_t type_;
                        /**< Type of the object.
                         * @internal This type must be used only in
                         * classes which implement storage or manager functions.
                         * 
                         */

    objid_t id_;
                        /**< Identificator of the object.
                         * @internal This identificator must be used only in
                         * classes which implement storage or manager
                         * functions.
                         */

    class AbstractUI& ui_;
                        /**< Manager of the objects.
                         * @internal This field must be used in pull and push
                         * methods only.
                         */

protected:
    const obj_t type() const { return type_; };
                        /**< @brief Get type of the object.
                         * @return type of object.
                         * @internal Use this method in the manager and storage
                         * classes only.
                         */
    
    const objid_t id() const { return id_; };
                        /**< @brief Get id of the object.
                         * @return id of object.
                         * @internal Use this method in the manager and storage
                         * classes only.
                         */

    const class Field& pull(const std::string& name) const;
                        /**< @brief Get initial value of the field from the
                         * manager.
                         * @param [in] name Name of the field.
                         * @return Corresponding field.
                         * @internal Use this method in the object's constructo
                         * only.
                         */

    void push(const class Field& field);
                        /**< @brief Set new value of the field in the database.
                         * @param [in] field Field to set.
                         * @internal Use this method in the update method only.
                         */

public:

    Object(obj_t type, objid_t id, AbstractUI& ui): type_(type), id_(id), ui_(ui)
                        /**< @brief Constructor.
                         * @param [in] id Identificator of the object.
                         * @param [in] ui Manager of objects.
                         */
    {}

    virtual const Field& read(const std::string& name) const = 0;
                        /**< @brief Get field of the object.
                         * @param [in] name Name of the field to get.
                         * @return Corresponding field.
                         */

    virtual void update(const Field& field) = 0;
                        /**< @brief Change field of the object.
                         * @param [in] field Field to change.
                         */
};

};

#include <abstractui.h>
#include <field.h>

