#include <event.h>

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

