
#pragma once

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
};

#include <iostream>

namespace Core {

class Config {
private:
    lua_State *vm_;
public:
    Config(const std::string& file)
        throw ():
        vm_(lua_open())
    {
        luaL_openlibs(vm_);
        lua_createtable(vm_, 0, 0);
        lua_setglobal(vm_, "config");
        if (luaL_dofile(vm_, file.c_str()))
        {
            std::cerr << lua_tostring(vm_, 1) << std::endl;
            lua_pop(vm_, 1);
        }
    }

    lua_State *
    vm()
        throw()
    {
        return vm_;
    }
};

}

