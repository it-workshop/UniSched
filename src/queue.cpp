#include <queue.h>

Queue::Queue(string name)
:   name_ (name)
{
}

Queue::~Queue()
{
}

vector<Group *>::iterator Queue::get_begin()
{
    return groups_.begin();
}

vector<Group *>::iterator Queue::get_end()
{
    return groups_.end();
}

string Queue::get_name()
{
    return name_;
}

id_type Queue::get_id()
{
    return id_;
}

void Queue::set_id(id_type id)
{
    id_ = id;
}

void Queue::enqueue(Group *adding)
{
    groups_.push_back(adding);
}

Group *Queue::dequeue()
{
    Group *tmp = groups_[0];
    groups_.erase(groups_.begin());
    return tmp;
}

