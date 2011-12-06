#include <abstractstorage.h>

using namespace Storage;

void AbstractStorage::remove(StorableObject const * object)
{
    delete object;
}

template <class T>
StorableObject const * AbstractStorage::create(std::vector<const Argument *>& parameters)
{
    T const * object = new T(new_id(), this);
    
    set_object(dynamic_cast<StorableObject const *>(object));

    for (auto it = parameters.begin(); it != parameters.end(); it++)
    {
        switch ((*it)->type)
        {
        case Argument::STRING:
            set_field((dynamic_cast<StorableObject const *>(object))->id(),
                        (*it)->field, (*it)->string);
            break;
        case Argument::INTEGER:
            set_field((dynamic_cast<StorableObject const *>(object))->id(),
                        (*it)->field, (*it)->integer);
            break;
        case Argument::TIME:
            set_field((dynamic_cast<StorableObject const *>(object))->id(),
                        (*it)->field, (*it)->time);
            break;
        case Argument::ENUMERATION:
            set_field_enum((dynamic_cast<StorableObject const *>(object))->id(),
                        (*it)->field, (*it)->string);
            break;
        }
    }

    (dynamic_cast<StorableObject const *>(object))->load();

    return dynamic_cast<StorableObject const *>(object);
}

const int AbstractStorage::new_id()
{
    const int id = objects_.size();
    objects_.reserve(objects_.size() + 1);
    return id;
}

void AbstractStorage::set_object(StorableObject const * object)
{
    objects_[object->id()] = object;
}

