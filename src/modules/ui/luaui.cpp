#include <abstractui.h>
#include <person.h>
#include <group.h>
#include <event.h>

#include <boost/format.hpp>

extern "C" {

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

};

class luaUI : public Core::AbstractUI {
private:
    std::string script_;
protected:
public:
    luaUI(std::vector<Core::Module *>* modules, void *handle);

    virtual void init(Core::Config& conf, const std::vector<std::string>& args);
    virtual int run();
};

luaUI::luaUI(std::vector<Core::Module *>* modules, void *handle):
        AbstractUI("luaui", modules, handle)
{
}

void luaUI::init(Core::Config& conf, const std::vector<std::string>& args)
{
    AbstractUI::init(conf, args);

    for (auto it = args.begin(); it != args.end(); it++)
    {
        if ("--lua" == *it)
        {
            script_ = *++it;
            continue;
        }
    }

    if (script_.empty())
    {
        lua_getglobal(vm(), "config");
        lua_getfield(vm(), -1, "script");
        if (lua_isstring(vm(), -1))
        {
            script_ = lua_tostring(vm(), -1);
        }
        lua_pop(vm(), 2);
    }
}

int luaUI::run()
{
    if (luaL_dofile(vm(), script_.empty() ? nullptr : script_.c_str()))
    {
        std::cerr << lua_tostring(vm(), -1) << std::endl;
        lua_pop(vm(), 1);
        return -1;
    }

    return 0;
}

extern "C" {

void init(std::vector<Core::Module *>* modules, void *handle)
{
    new luaUI(modules, handle);
}

};


