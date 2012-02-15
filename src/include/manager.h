#pragma once

#include <string>
#include <vector>
#include <typeinfo>

#include <manageableobject.h>

#include <backend.h>

namespace Core {

/**@class Manager
 * @brief Abstract interface for storage.
 *
 * Each storage backend must to inherit this class. It can be chahged later,
 * it is too simple to work fast now.
 */
class Manager {
friend class ManageableObject;
private:
protected:
    std::vector<ManageableObject *> objects_;
                        /**< Model objects. Each object must be saved here for
                         * correct work of storage.
                         *
                         * You must use this only with object(), set_object and
                         * new_id() mehods, you can redefine this methods but do
                         * not use this field in other code.
                         */
    
    virtual const int
    get_field_int(const int id, const std::string field) const 
            throw (std::bad_cast) = 0;
                        /**< @brief Return integer value of requested field.
                         * @param [in] id Object identificator.
                         * @param [in] field Field name.
                         * @return requested value.
                         *
                         * This method must be realized in inherited classes.
                         * Throw an std::bad_cast exception if requested field
                         * does not exists or keeped in another type.
                         */

    virtual const std::string
    get_field_string(const int id, const std::string field) const
            throw (std::bad_cast) = 0;
                        /**< @brief Return string value of requested field.
                         * @param [in] id Object identificator.
                         * @param [in] field Field name.
                         * @return requested value.
                         *
                         * This method must be realized in inherited classes.
                         * Throw an std::bad_cast exception if requested field
                         * does not exists or keeped in another type.
                         */

    virtual const time_t
    get_field_time(const int id, const std::string field) const
            throw (std::bad_cast) = 0;
                        /**< @brief Return time value of requested field.
                         * @param [in] id Object identificator.
                         * @param [in] field Field name.
                         * @return requested value.
                         *
                         * This method must be realized in inherited classes.
                         * Throw an std::bad_cast exception if requested field
                         * does not exists or keeped in another type.
                         */

    virtual const std::string
    get_field_enum(const int id, const std::string field) const
            throw (std::bad_cast) = 0;
                        /**< @brief Return enum value of requested field.
                         * @param [in] id Object identificator.
                         * @param [in] field Field name.
                         * @return requested value.
                         *
                         * This method must be realized in inherited classes.
                         * Throw an std::bad_cast exception if requested field
                         * does not exists or keeped in another type.
                         */

    virtual ManageableObject *
    get_field_object(const int id, const std::string field) const
            throw (std::bad_cast) = 0;
                        /**< @brief Return object value of requested field.
                         * @param [in] id Object identificator.
                         * @param [in] field Field name.
                         * @return requested value.
                         *
                         * This method must be realized in inherited classes.
                         * Throw an std::bad_cast exception if requested field
                         * does not exists or keeped in another type.
                         */

    virtual const std::vector<ManageableObject *>
    get_field_vector(const int id, const std::string field) const
            throw (std::bad_cast) = 0;
                        /**< @brief Return vector value of requested field.
                         * @param [in] id Object identificator.
                         * @param [in] field Field name.
                         * @return requested value.
                         *
                         * This method must be realized in inherited classes.
                         * Throw an std::bad_cast exception if requested field
                         * does not exists or keeped in another type.
                         */

    virtual void 
    set_field(const int id, const std::string field, const int value)
            throw (std::bad_cast) = 0;
                        /**< @brief Set integer value of requested field.
                         * @param [in] id Object identificator.
                         * @param [in] field Field name.
                         * @param [in] value New value.
                         *
                         * This method must be realized in inherited classes.
                         * Throw an std::bad_cast exception if requested field
                         * keeped in another type.
                         */

    virtual void 
    set_field(const int id, const std::string field, const std::string value)
            throw (std::bad_cast) = 0;
                        /**< @brief Set string value of requested field.
                         * @param [in] id Object identificator.
                         * @param [in] field Field name.
                         * @param [in] value New value.
                         *
                         * This method must be realized in inherited classes.
                         * Throw an std::bad_cast exception if requested field
                         * keeped in another type.
                         */

    virtual void 
    set_field(const int id, const std::string field, const time_t value)
            throw (std::bad_cast) = 0;
                        /**< @brief Set time value of requested field.
                         * @param [in] id Object identificator.
                         * @param [in] field Field name.
                         * @param [in] value New value.
                         *
                         * This method must be realized in inherited classes.
                         * Throw an std::bad_cast exception if requested field
                         * keeped in another type.
                         */
    virtual void 
    set_field(const int id, const std::string field, ManageableObject * value)
            throw (std::bad_cast) = 0;
                        /**< @brief Set object value of requested field.
                         * @param [in] id Object identificator.
                         * @param [in] field Field name.
                         * @param [in] value New value.
                         *
                         * This method must be realized in inherited classes.
                         * Throw an std::bad_cast exception if requested field
                         * keeped in another type.
                         */

    virtual void 
    set_field_enum(const int id, const std::string field,
        const std::string value)
            throw (std::bad_cast) = 0;
                        /**< @brief Set enum value of requested field.
                         * @param [in] id Object identificator.
                         * @param [in] field Field name.
                         * @param [in] value New value.
                         *
                         * This method must be realized in inherited classes.
                         * Throw an std::bad_cast exception if requested field
                         * keeped in another type.
                         */
    virtual void
    set_field_vector(const int id, const std::string field,
        const std::vector<ManageableObject *> vector)
            throw (std::bad_cast) = 0;
                        /**< @brief Set vector value of requested field.
                         * @param [in] id Object identificator.
                         * @param [in] field Field name.
                         * @paraw [in] value New value.
                         *
                         * This method must be realized in inherited classes.
                         * Throw an std::bad_cast exception if requested field
                         * keeped in another type.
                         */

    virtual void set_object(ManageableObject * object);
                        /**< @brief Set integer value of requested field.
                         * @param [in] Object to save.
                         *
                         * You can redefine this method if you want to keep
                         * objects in other order.
                         *
                         * Do not use this method anywhere, it used by create
                         * method.
                         */

    virtual const int new_id();
                        /**< @brief Return new object identificator and reserve
                         * cell for it in the objects vector.
                         * @return New id.
                         *
                         * You can redefine this method if you want to keep
                         * objects in other order.
                         *
                         * Do not use this method anywhere, it used by create
                         * method.
                         */
public:
    /**@struct Argument
     * @brief an auxiliary structure to make search query and create objects.
     *
     * set to the field name of the field (empty string for searching in the all
     * fields of the type), set type and the value.
     *
     * Use constructors instead of manual editing.
     */
    struct Argument {
        const std::string field;
                        /**< Name of requested field. */

        const enum {
            STRING,
            INTEGER,
            TIME,
            ENUMERATION
        } type;
                        /**< Type of the field. */

        const std::string string;
                        /**< String or enum value. */

        const int integer;
                        /**< Integer value. */

        const time_t time;
                        /**< Time value. */
        
        Argument(const std::string field, const std::string value):
                field(field), type(STRING), string(value), integer(0), time(0)
                {}
                        /**< @brief Constructor for string type.
                         * @param [in] field Name of the field.
                         * @param [in] value String value.
                         */
        Argument(const std::string field, const int value):
                field(field), type(INTEGER), integer(value), time(0)
                {}
                        /**< @brief Constructor for integer type.
                         * @param [in] field Name of the field.
                         * @param [in] value Integer value.
                         */
        Argument(const std::string field, const time_t value):
                field(field), type(TIME), integer(0), time(value)
                {}
                        /**< @brief Constructor for time type.
                         * @param [in] field Name of the field.
                         * @param [in] value Time value.
                         */
        Argument(const std::string field, const std::string value,
            const int number):
                field(field), type(ENUMERATION), string(value),
                integer(number), time(0)
                {}
                        /**< @brief Constructor for enumeration type.
                         * @param [in] field Name of the field.
                         * @param [in] value Enumeration value in the string
                         * representation.
                         * @param [in] number Enumoration value in the integer
                         * representation.
                         */
 
    };

    virtual void remove(ManageableObject * object);
                        /**< @brief Remove object from the storage.
                         * @param [in] object Object to delete.
                         *
                         * You can redefine this method if you want to store
                         * objects in the other order.
                         */

    template <class T>
    ManageableObject * create(std::vector<const Argument *>& parameters)
                        /**< @brief Create an object of the T type
                         * @param [in] parameters new object`s data.
                         * @return pointer to the created object.
                         *
                         * This method must be called from the user interface to
                         * create new object.
                         */
    {
        ManageableObject * object = new T(new_id(), *this);
    
        set_object(object);

        for (auto it = parameters.begin(); it != parameters.end(); it++)
        {
            switch ((*it)->type)
            {
            case Argument::STRING:
                set_field(object->id(), (*it)->field, (*it)->string);
                break;

            case Argument::INTEGER:
                set_field(object->id(), (*it)->field, (*it)->integer);
                break;

            case Argument::TIME:
                set_field(object->id(), (*it)->field, (*it)->time);
                break;

            case Argument::ENUMERATION:
                set_field_enum(object->id(), (*it)->field, (*it)->string);
                break;
            }
        }

        object->load();

        return object;
    }

    virtual std::vector<ManageableObject *> *
    search(std::vector<Argument *>& parameters) = 0;
                        /**< @brief Search objects by some parameters.
                         * @param [in] parameters Search parameters.
                         * @return Vector of found objects.
                         *
                         * Parameters are connected by logical AND.
                         * If parameter have not got a name, search value
                         * by the any field of specified type. If value
                         * is empty that all objects will satisfied.
                         */

    virtual ManageableObject * object(const int id) const throw (std::bad_cast)
            { return objects_[id]; }
                        /**< @brief Return object by id.
                         * @param [in] id Object identificator.
                         * @return Requested object.
                         *
                         * Use this method carefully. It can be moved to the
                         * protected or private on future.
                         */
};

};

