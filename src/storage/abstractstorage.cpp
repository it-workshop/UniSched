#include <abstractstorage.h>

using namespace Storage;

void AbstractStorage::remove(StorableObject * object)
{
    delete object;
}

const int AbstractStorage::new_id()
{
    const int id = objects_.size();
    objects_.reserve(objects_.size() + 1);
    return id;
}

void AbstractStorage::set_object(StorableObject * object)
{
    objects_[object->id()] = object;
}

