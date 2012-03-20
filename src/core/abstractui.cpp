#include <abstractui.h>
#include <person.h>
#include <group.h>
#include <event.h>

using namespace Core;

static const bool operator==(const boost::any& lhs, const boost::any& rhs)
    throw (boost::bad_any_cast)
{
    if (lhs.empty() != rhs.empty())
    {
        return false;
    }
    if (typeid(std::string) == lhs.type())
    {
        return boost::any_cast<std::string>(lhs)
            == boost::any_cast<std::string>(rhs);
    }
    if (typeid(time_t) == lhs.type())
    {
        return boost::any_cast<time_t>(lhs)
            == boost::any_cast<time_t>(rhs);
    }
    throw boost::bad_any_cast();
}

std::vector<Object *> AbstractUI::search(const std::map<std::string, boost::any>& parameters)
{
    std::vector<Object *> results;
    for (auto m: objects_) {
        results.push_back(m.second);
    }
    for (auto p: parameters)
    {
        for (auto it = results.begin(); it != results.end(); it++)
        {
            try
            {
                if (p.second == (*it)->read(p.first))
                {
                    continue;
                }
            }
            catch (std::bad_cast)
            {}
            it = results.erase(it);
        }
    }

    for (Object * object: results)
    {
        cache_.push_back(object);
    }

    return results;
}

void AbstractUI::push(const int id, const std::string& name,
        const boost::any& value)
{
    if (storage_)
    {
        storage_->push(id, name, value);
    }
}

void AbstractUI::push(Object * object, Object * with, bool connect)
{
    if (storage_)
    {
        storage_->push_connect(object->id(), with->id(), connect);
    }
}

void AbstractUI::remove(Object *object)

{
    int id = object->id();
    objects_.erase(objects_.find(id));
    object->cleanup();
    delete object;
    if (storage_)
    {
        storage_->remove(id);
    }
    for (auto it = cache_.begin(); it != cache_.end(); it++)
    {
        if (*it == object)
        {
            cache_.erase(it);
            return;
        }
    }
}

void AbstractUI::create_in_storage(const Object *object)
{
    if (storage_)
    {
        storage_->create(object);
    }
}

