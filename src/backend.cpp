#include <backend.h>

static std::vector<class AbstractBackend *> backends_;

AbstractBackend::AbstractBackend (const enum Type type):
    type_(type)
{
    backends().push_back(this);
}

std::vector<AbstractBackend *>& backends()
{
    static std::vector<AbstractBackend *> backends;
    return backends;
}
