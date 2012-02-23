#include <module.h>

static std::vector<class Module *> modules_;

Module::Module (const enum Type type, const std::string& name):
    type_(type), name_(name)
{
    modules().push_back(this);
}

std::vector<Module *>& modules()
{
    static std::vector<Module *> modules;
    return modules;
}
