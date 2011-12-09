#include <event.h>
#include <group.h>

using namespace Core;

void Event::save()
{
    AbstractGroup::save();

    set_field("begin", begin_);
    set_field("duration", duration_);
}

void Event::load()
{
    AbstractGroup::load();

    begin_ = get_field_time("begin");
    duration_ = get_field_time("duration");
}

const std::string Event::read() const
{
    std::stringstream stream(std::stringstream::out);

    stream << "Start time:\t " << begin_ << std::endl
           << "Duration:\t " << duration_ << std::endl
           << "End time:\t " << begin_ + duration_ << std::endl
           << AbstractGroup::read();

    return stream.str();
}

const time_t Event::read_time(const std::string name) const throw (std::bad_cast)
{
    if (name == "begin")
        { return begin_; }

    if (name == "duration")
        { return duration_; }

    if (name == "end")
        { return begin_ + duration_; }

    return AbstractGroup::read_time(name);
}

void Event::update(const std::string name, const time_t value) throw(std::bad_cast)
{
    if (name == "begin")
    {
        begin_ = value;
        return;
    }

    if (name == "duration")
    {
        duration_ = value;
        return;
    }

    if (name == "end")
    {
        duration_ = value - begin_;
        return;
    }

    return AbstractGroup::update(name, value);
}

void Event::update(UI::UsersObject * object, const bool linked) throw (std::bad_cast)
{
    try
    {
        AbstractGroup::update(object, linked);
    }
    catch (std::bad_cast)
    {
        (dynamic_cast<Group *>(object))->update(this, linked);
    }
}

