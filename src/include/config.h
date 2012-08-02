
#pragma once

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
};

#include <iostream>

namespace Core {

/** @class Config
 * @brief C++ Wrapper for lua config.
 */
class Config {
private:
    lua_State *vm_;     /**< lua machine */
public:
    Config(const std::string& file)
        throw ():
                        /**< @brief Constructor */
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
        throw()         /**< @brief Get lua machine */
    {
        return vm_;
    }

    /* TODO: Add C++ wrapper for lua tables */
};

}

