#pragma once

#include <string>
#include <vector>

namespace Core {

/**< @class Object
 * @brief Universal interface of core objects.
 */
class Object {
friend class AbstractUI;
/* TODO: Add database class to friend when create this. */
private:
    const int id_;
                        /**< Identificator of object.
                         * @internal This identificator must not be used in any
                         * class, not implements storage or manager functions.
                         */

    class AbstractUI& ui_;
                        /**< Manager of objects.
                         * @internal This field must be used in pull and push
                         * methods only.
                         */

protected:
    const int id() const { return id_; };
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

    Object(const int id, AbstractUI& ui): id_(id), ui_(ui)
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

