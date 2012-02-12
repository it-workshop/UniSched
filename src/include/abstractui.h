#pragma once

#include <usersobject.h>
#include <manager.h>

#include <backend.h>

namespace UI {

class AbstractUI: public AbstractBackend {
private:
    Core::Manager *manager_;
    std::vector<UsersObject *> cache_;
protected:
    std::vector<UsersObject *>& cache() { return cache_; }

    void search(std::vector<Core::Manager::Argument *>& parameters);

    template <class T>
    void create(const std::vector<const Core::Manager::Argument>& parameters);

    void remove(UsersObject * object);

public:

    AbstractUI (Core::Manager * manager):
        AbstractBackend(AbstractBackend::UI), manager_(manager) {}

    AbstractUI ():
        AbstractBackend(AbstractBackend::UI)
        {}

    void manager(Core::Manager * manager)
        { manager_ = manager; }

    virtual int run() = 0;
};

};

