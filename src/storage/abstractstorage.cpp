#include <abstractstorage.h>

using namespace Storage;

void AbstractStorage::remove(StorableObject const * object)
{
    delete object;
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

