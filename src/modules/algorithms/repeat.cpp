#include <algorithm.h>
#include <event.h>

class repeat : public Core::Algorithm {
public:
    repeat(std::vector<Core::Module *>* modules, void *handle);

    void init(const std::vector<std::string>& args);

    void exec(Core::Object *object);
};

repeat::repeat(std::vector<Core::Module *>* modules, void *handle):
    Algorithm("repeat", modules, handle)
{
}

void repeat::init(const std::vector<std::string>& args)
{
}

void repeat::exec(Core::Object *object)
{
    if (!object || object->type() != Core::EVENT)
    {
        std::cerr << "Algorithm repeat works only with events!" << std::endl;
        return;
    }

    boost::any value = object->read("start");
    if (value.empty())
    {
        std::cerr << "Start time not specified!" << std::endl;
        return;
    }
    time_t first = boost::any_cast<const time_t>(value);
    value = object->read("max_start");
    if (value.empty())
    {
        std::cerr << "max_start time of event not specified!" << std::endl;
        return;
    }
    time_t max_start = boost::any_cast<const time_t>(value);
    value = object->read("repeat_interval");
    if (value.empty())
    {
        std::cerr << "repeat_interval not specified!" << std::endl;
        return;
    }
    time_t interval = boost::any_cast<const time_t>(value);
    for (time_t start = first + interval; start < max_start; start += interval)
    {
        Core::Object *new_object = ui()->create<Core::Event>();
        for (auto field : object->read())
        {
            if (field.second.type() != typeid(std::vector<Core::Object *>))
            {
                new_object->update(field.first, field.second);
                continue;
            }
            for (Core::Object *conn : boost::any_cast<std::vector<Core::Object *>>(field.second))
            {
                new_object->connect(conn);
            }
        }
        new_object->update("start", start);
    }
}

extern "C" {

void init(std::vector<Core::Module *>* modules, void *handle)
{
    new repeat(modules, handle);
}

};

