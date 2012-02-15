#include <manageableobject.h>

using namespace Core;

const Field& ManageableObject::pull(const std::string& name) const
{
    return manager_.pull(name);
}

void ManageableObject::push(const Field& field)
{
    return field_.push(id(), field);
}

