#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <typeinfo>

#include <field.h>
#include <object.h>

namespace Core {

/**@class Manager
 * @brief Abstract interface for storage.
 *
 * Each storage backend must to inherit this class. It can be chahged later,
 * it is too simple to work fast now.
 */
class Manager {
friend class Object;
private:
    std::map<const int, Object *> objects_;
                        /**< Model objects. Each object must be saved here for
                         * correct work of storage.
                         *
                         * You must use this only with object(), set_object() and
                         * new_id() mehods, you can redefine this methods but do
                         * not use this field in other code.
                         */
    int new_id_;
    const int new_id()
    {
        return new_id_++;
    }
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

    std::vector<Field *> parameters_;

    Object * set_object(Object * object)
                        /**< @brief Apply changes in an object.
                         * @param [in] object Object to apply.
                         */
    {
        return objects_[object->id()] = object;
    }

protected:
    void push(const int id, const Field& field)
    {}

    const Field& pull(const std::string& name) const throw (std::bad_cast);
    
public:
    Manager() throw ():
        new_id_(0)
    {}

    Manager(std::fstream input_storage);

    void remove(Object * object)
                        /**< @brief Remove object from the storage.
                         * @param [in] object Object to delete.
                         *
                         * You can redefine this method if you want to store
                         * objects in the other order.
                         */
    {
        for (auto it = objects_.begin(); it != objects_.end(); it++)
        {
            objects_.erase(objects_.find(object->id()));
            delete [] object;
            return;
        }
    }

    template <class T>
    Object * create(std::vector<const Field>& parameters)
                        /**< @brief Create an object of the T type
                         * @param [in] parameters new object`s data.
                         * @return pointer to the created object.
                         *
                         * This method must be called from the user interface to
                         * create new object.
                         */
    {
        int id = new_id();
        parameters_ = parameters;
        return object(new T(new_id(), *this));
    }
    std::vector<Object *>&
    search(const std::vector<const Field *>& parameters) const;
                        /**< @brief Search objects by some parameters.
                         * @param [in] parameters Search parameters.
                         * @return Vector of found objects.
                         *
                         * Parameters are connected by logical AND.
                         * If parameter have not got a name, search value
                         * by the any field of specified type. If value
                         * is empty that all objects will satisfied.
                         */
    Object * object(const int id) const throw (std::bad_cast)
                        /**< @brief Return object by id.
                         * @param [in] id Object identificator.
                         * @return Requested object.
                         *
                         * Use this method carefully. It can be moved to the
                         * protected or private on future.
                         */
    {                    
        return objects_.at(id);
    }
};

};

