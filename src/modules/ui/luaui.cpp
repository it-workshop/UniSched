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

    if (script_.empty())
    {
        std::cerr << "lua UI: script name not set!" << std::endl;
    }
}

int luaUI::run()
{
    if (script_.empty())
    {
        luaL_loadfile(vm(), nullptr);
    }
    else
    {
        luaL_loadfile(vm(), script_.c_str());
    }
    if (lua_pcall(vm(), 0, LUA_MULTRET, 0))
    {
        std::cerr << lua_tostring(vm(), -1) << std::endl;
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


