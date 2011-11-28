#include "event_template.h"

Event_Template::Event_Template(id_type id, string name, string script, time_t duration)
:   script_ (script),
    id_ (id),
    name_ (name),
    duration_ (duration)
{
}

Event_Template::~Event_Template()
{
}

id_type Event_Template::get_id()
{
    return id_;
}

void Event_Template::set_id(id_type id)
{
    id_ = id;
}

string Event_Template::get_name()
{
    return name_;
}

string Event_Template::get_script()
{
    return script_;
}

void Event_Template::get_requered_people()
{
    vector<string> args;
    string reading = "";
    for (int i = 0; i < script_.size(); i++)
    {
        if (script_[i] == '\n')
        {
            args.push_back(reading);
            reading = "";
            uiconsole::execute(args);
            args.resize(0);
            continue;
        }
        if (script_[i] == ' ')
        {
            args.push_back(reading);
            reading = "";
            continue;
        }
        reading += script_[i];
    }
}

