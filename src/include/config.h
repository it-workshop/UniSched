/** @file
 * @brief Configuration implementation.
 * @author Aleksander Derbenev
 * @date 2012
 */
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
                        /**< @brief Constructor
                         * @param [in] file Name of the file to load.
                         *
                         * FIXME: Is there is alright that lua vm created here
                         * but removed in the AbstractUI?
                         */
 
    lua_State *
    vm()
        throw()
    {
        return vm_;
    }
                        /**< Getter for the lua vm.
                         * @return Lua virtual machine.
                         */

    /* TODO: Add C++ wrapper for lua tables */
};

}

