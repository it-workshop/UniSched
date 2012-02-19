#pragma once

#include <object.h>
#include <manager.h>

#include <module.h>

namespace UI {

class AbstractUI: public Module {
private:
    Core::Manager manager_;
    std::vector<Core::Object *> cache_;
protected:
    std::vector<Core::Object *>& cache()
    {
        return cache_;
    }

    void search(const std::vector<const Core::Field *>& parameters)
    {
        auto tmp = manager_.search(parameters);

        for (Core::Object * object: tmp)
        {
            cache_.push_back(object);
        }
    }

    template <class T>
    void create(const std::vector<const Core::Field *>& parameters)
    {
        cache_.push_back(manager_.create<T>());
    }

    void remove(Core::Object * object)
    {
        for (auto it = cache_.begin(); it != cache_.end(); it++)
        {
            if (*it == object)
            {
                cache_.erase(it);
                manager_.remove(object);
                return;
            }
        }
    }

    void reset_cache() throw ()
    {
        cache_.clear();
    }

public:

    AbstractUI ():
        Module(Module::UI)
    {}

    Core::Manager& manager() throw ()
    {
        return manager_;
    }

    virtual int run() = 0;
};

};

