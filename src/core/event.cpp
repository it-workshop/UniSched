#include <event.h>

using namespace Core;

const Field& Event::read(const std::string& name) const throw (std::bad_cast)
{
    if (name == "begin")
    {
        return begin_;
    }
    if (name == "duration")
    {
        return duration_;
    }
    return AbstractGroup::read(name);
}

void Event::update(const Field& field) throw (std::bad_cast)
{
    if (field.name() == "begin")
    {
        begin_ = dynamic_cast<const FieldTime&>(field);
        return;
    }
    if (field.name() == "duration")
    {
        duration_ = dynamic_cast<const FieldTime&>(field);
    }
    AbstractGroup::update(field);
}

