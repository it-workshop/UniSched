#pragma once

#include <string>
#include <vector>
#include <map>

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
    std::vector<ManageableObject *> objects_;
                        /**< Model objects. Each object must be saved here for
                         * correct work of storage.
                         *
                         * You must use this only with object(), set_object and
                         * new_id() mehods, you can redefine this methods but do
                         * not use this field in other code.
                         */
    int new_id_;
    const int new_id()
    {
        objects_.reserve(new_id_ + 1);
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
    std::map<const int, std::vector<Field *>> records_;

    ManageableObject * object(ManageableObject * object)
    {
        return objects_[object->id()] = object;
    }

protected:
    void push(const int id, const Field& field)
    {
        for (Field * record: records_[id])
        {
            if (record->name() == field.name())
            {
                switch (field.type())
                {
                    case Field::STRING:
                        delete [] record;
                        record = new FieldString(
                                dynamic_cast<const FieldString&>(field));
                        break;
                    case Field::TIME:
                        delete [] record;
                        record = new FieldTime(
                                dynamic_cast<const FieldTime&>(field));
                        break;
                    case Field::ENUM:
                        delete [] record;
                        record = new FieldEnum(
                                dynamic_cast<const FieldEnum&>(field));
                        break;
                    case Field::VECTOR:
                        delete [] record;
                        record = new FieldVector(
                                dynamic_cast<const FieldVector&>(field));
                        break;
                    case Field::LINK:
                        dynamic_cast<FieldVector *>(record)->commit(
                                dynamic_cast<const FieldLink&>(field));
                        break;
                }
                return;
            }
        }
        switch(field.type())
        {
            case Field::STRING:
                records_[id].push_back(new FieldString(
                        dynamic_cast<const FieldString&>(field)));
                break;
            case Field::TIME:
                records_[id].push_back(new FieldTime(
                        dynamic_cast<const FieldTime&>(field)));
                break;
            case Field::ENUM:
                records_[id].push_back(new FieldEnum(
                        dynamic_cast<const FieldEnum&>(field)));
                break;
            case Field::VECTOR:
                records_[id].push_back(new FieldVector(
                        dynamic_cast<const FieldVector&>(field)));
                break;
            case Field::LINK:
                records_[id].push_back(new FieldVector(field.name()));
                dynamic_cast<FieldVector *>(records_[id][0])->commit(dynamic_cast<const FieldLink&>(field));
                break;
        }
    }

    const Field& pull(const std::string& name) const throw (std::bad_cast)
    {
        for (const Field* parameter: parameters_)
        {
            if (parameter->name() == name)
            {
                return *parameter;
            }
        }
        throw std::bad_cast();
    }
    
public:
    Manager() throw ():
        new_id_(0)
    {}

    void remove(ManageableObject * object)
                        /**< @brief Remove object from the storage.
                         * @param [in] object Object to delete.
                         *
                         * You can redefine this method if you want to store
                         * objects in the other order.
                         */
    {
        for (Field* record : records_[object->id()])
        {
            if (record->type() == Field::VECTOR)
            {
                for (ManageableObject* obj:
                    (dynamic_cast<FieldVector *>(record))->vector())
                {
                    object->update(FieldLink(record->name(),
                                             std::make_pair(object, false)));
                }
            }
        }
        for (auto it = objects_.begin(); it != objects_.end(); it++)
        {
            objects_.erase(it);
            delete [] object;
            return;
        }
    }

    template <class T>
    ManageableObject * create(std::vector<const Field>& parameters)
                        /**< @brief Create an object of the T type
                         * @param [in] parameters new object`s data.
                         * @return pointer to the created object.
                         *
                         * This method must be called from the user interface to
                         * create new object.
                         */
    {
        int id = new_id();
        records_.insert(std::make_pair(id, (parameters_ = parameters)));
        return object(new T(new_id(), *this));
    }

    std::vector<ManageableObject *>&
    search(const std::vector<const Field *>& parameters) const
                        /**< @brief Search objects by some parameters.
                         * @param [in] parameters Search parameters.
                         * @return Vector of found objects.
                         *
                         * Parameters are connected by logical AND.
                         * If parameter have not got a name, search value
                         * by the any field of specified type. If value
                         * is empty that all objects will satisfied.
                         */
    {
        static std::vector<ManageableObject *> results;

        results.clear();

        for (const Field * parameter: parameters)
        {
            for (const std::pair<const int, std::vector<Field *>>& objects_records :
                records_)
            {
                for (const Field *record: objects_records.second)
                {
                    if (parameter == record)
                    {
                        results.push_back(objects_[objects_records.first]);
                    }
                }
            }
        }

        return results;
    }

    ManageableObject * object(const int id) const throw (std::bad_cast)
                        /**< @brief Return object by id.
                         * @param [in] id Object identificator.
                         * @return Requested object.
                         *
                         * Use this method carefully. It can be moved to the
                         * protected or private on future.
                         */
    {                    
        return objects_[id];
    }
};

};

