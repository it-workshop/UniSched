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
friend int luaUI___object___index(lua_State *state);
friend int luaUI___object___newindex(lua_State *state);
friend int luaUI___object___eq(lua_State *state);
friend int luaUI_create(lua_State *state);
friend int luaUI_search(lua_State *state);
friend int luaUI_remove(lua_State *state);
friend int luaUI_object_type(lua_State *state);
friend int luaUI_object_read(lua_State *state);
friend int luaUI_object_update(lua_State *state);
friend int luaUI_object_connect(lua_State *state);
friend int luaUI_object_disconnect(lua_State *state);
friend void luaUI_create_lua_object(lua_State *state, Core::Object *object);
friend int luaUI___cache___index(lua_State *state);
friend int luaUI___cache___newindex(lua_State *state);
friend int luaUI___cache___len(lua_State *state);
friend int luaUI___cache___next(lua_State *state);
friend int luaUI___cache___ipairs(lua_State *state);
private:
    std::string script_;
    lua_State *vm_;
protected:
public:
    luaUI(std::vector<Core::Module *>* modules, void *handle);

    virtual void init(const std::vector<std::string>& args);
    virtual int run();
};

luaUI::luaUI(std::vector<Core::Module *>* modules, void *handle):
        AbstractUI("luaui", modules, handle)
{
}

void luaUI::init(const std::vector<std::string>& args)
{
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
        std::cerr << "lua UI: script name not set!" << std::endl;
    }
}

static luaUI *self;

int luaUI_object_type(lua_State *state)
{
    /* Stack:
     * 
     *  lua_upvalueindex(1): varid
     */
    switch (((Core::Object *)lua_touserdata(state, lua_upvalueindex(1)))->type())
    {
    case Core::PERSON:
        lua_pushstring(state, "person");
        break;
    case Core::GROUP:
        lua_pushstring(state, "group");
        break;
    case Core::EVENT:
        lua_pushstring(state, "event");
        break;
    default:
        lua_pushstring(state, "unknown");
        break;
    }
    return 1;
}

int luaUI_object_read(lua_State *state);
int luaUI_object_update(lua_State *state);
int luaUI_object_connect(lua_State *state);
int luaUI_object_disconnect(lua_State *state);

void luaUI_create_lua_object(lua_State *state, Core::Object *object)
{
    lua_createtable(state, 0, 0);                           // #-1: object

    lua_pushlightuserdata(state, object);
    lua_pushcclosure(state, luaUI_object_type, 1);          // #-2: object, #-1: [id]type()
    lua_setfield(state, -2, "type");                        // #-1: object
    
    lua_pushlightuserdata(state, object);
    lua_pushcclosure(state, luaUI_object_read, 1);          // #-2: object, #-1: [id]read()
    lua_setfield(state, -2, "read");                        // #-1: object

    lua_pushlightuserdata(state, object);
    lua_pushcclosure(state, luaUI_object_update, 1);        // #-2: object, #-1: [id]update()
    lua_setfield(state, -2, "update");                      // #-1: object
    
    lua_pushlightuserdata(state, object);
    lua_pushcclosure(state, luaUI_object_connect, 1);       // #-2: object, #-1: [id]connect()
    lua_setfield(state, -2, "connect");                     // #-1: object

    lua_pushlightuserdata(state, object);
    lua_pushcclosure(state, luaUI_object_disconnect, 1);    // #-2: object, #-1: [id]disconnect()
    lua_setfield(state, -2, "disconnect");                  // #-1: object

    lua_pushlightuserdata(state, object);
    lua_setfield(state, -2, "__object");                     // #-1: object

    lua_getglobal(state, "__object");                       // #-2: object, #-1: __object
    lua_setmetatable(state, -2);                            // #-1: object
}

int luaUI_object_read(lua_State *state)
{
    /* Stack:
     *  1: index
     *  lua_upvalueindex(1): varid
     */
    if (lua_gettop(state) == 0)
    {
        Core::Object *object = (Core::Object *)lua_touserdata(state, lua_upvalueindex(1));
        auto fields = object->read();
        lua_createtable(state, 0, 0);
        for (auto field : fields)
        {
            if (typeid(std::string) == field.second.type())
            {
                lua_pushstring(state, boost::any_cast<const std::string&>(field.second).c_str());
            }
            else if (typeid(time_t) == field.second.type())
            {
                lua_pushnumber(state, boost::any_cast<const time_t>(field.second));
            }
            else if (typeid(std::vector<Core::Object *>) == field.second.type())
            {
                auto vector = boost::any_cast<std::vector<Core::Object *>>(field.second);
                int i = 0;
                lua_createtable(state, 0, 0);
                for (Core::Object *obj : vector)
                {
                    lua_pushnumber(state, ++i);
                    luaUI_create_lua_object(state, obj);
                    lua_settable(state, -3);
                }
            }
            else
            {
                lua_pushstring(state, "Invalid field type!");
                lua_error(state);
                // long jump
            }
            lua_setfield(state, -2, field.first.c_str());
        }
        return 1;
    }
    else if (lua_gettop(state) != 1 || !lua_isstring(state, 1))
    {
        lua_pushstring(state, "Invalid arguments!");
        lua_error(state);
        // long jump
    }
    std::string field = lua_tostring(state, 1);
    Core::Object *object = (Core::Object *)lua_touserdata(state, lua_upvalueindex(1));
    boost::any value = object->read(field);
    if (value.empty())
    {
        lua_pushnil(state);
    }
    else if (value.type() == typeid(const std::string))
    {
        lua_pushstring(state, boost::any_cast<const std::string&>(value).c_str());
    }
    else if (value.type() == typeid(const time_t))
    {
        lua_pushnumber(state, boost::any_cast<const time_t>(value));
    }
    else if (value.type() == typeid(const std::vector<Core::Object *>))
    {
        auto vector = boost::any_cast<const std::vector<Core::Object *>>(value);
        int i = 0;
        lua_createtable(state, 0, 0);
        for (Core::Object *obj : vector)
        {
            lua_pushnumber(state, ++i);
            luaUI_create_lua_object(state, obj);
            lua_settable(state, -3);
        }
    }
    else
    {
        lua_pushstring(state, "Invalid field type!");
        lua_error(state);
        // long jump
    }
    return 1;
}

int luaUI_object_update(lua_State *state)
{
    /* Stack:
     *  1: index
     *  2: value
     *  lua_upvalueindex(1): varid
     */
    if (lua_gettop(state) != 2 || !lua_isstring(state, 1) || !lua_isstring(state, 2))
    {
        lua_pushstring(state, "Invalid arguments!");
        lua_error(state);
        // long jump
    }
    std::string field = lua_tostring(state, 1);
    Core::Object *object = (Core::Object *)lua_touserdata(state, lua_upvalueindex(1));
    boost::any value;
    if (lua_isnumber(state, 2))
    {
        value = (time_t) lua_tonumber(state, 2);
    }
    else
    {
        value = std::string(lua_tostring(state, 2));
    }
    try
    {
        object->update(field, value);
    }
    catch (boost::bad_any_cast)
    {
        lua_pushstring(state, "Could not change field!");
        lua_error(state);
        // long jump
    }
    return 0;
}

int luaUI_object_connect(lua_State *state)
{
    /* Stack:
     *  1: with
     *  lua_upvalueindex(1): varid
     */
    if (lua_gettop(state) != 1 || !lua_istable(state, 1))
    {
        lua_pushstring(state, "Invalid arguments!");
        lua_error(state);
        // long jump
    }
    Core::Object *object = (Core::Object *)lua_touserdata(state, lua_upvalueindex(1));
    lua_getfield(state, 1, "__object");
    Core::Object *with = (Core::Object *)lua_touserdata(state, -1);
    lua_pop(state, 1);
    try
    {
        object->connect(with);
    }
    catch (std::bad_cast)
    {
        lua_pushstring(state, "Could not connect objects!");
        lua_error(state);
        // long jump
    }
    return 0;
}

int luaUI_object_disconnect(lua_State *state)
{
    /* Stack:
     *  1: with
     *  lua_upvalueindex(1): varid
     */
    if (lua_gettop(state) != 1 || !lua_istable(state, 1))
    {
        lua_pushstring(state, "Invalid arguments!");
        lua_error(state);
        // long jump
    }
    Core::Object *object = (Core::Object *)lua_touserdata(state, lua_upvalueindex(1));
    lua_getfield(state, 1, "__object");
    Core::Object *with = (Core::Object *)lua_touserdata(state, -1);
    lua_pop(state, 1);
    try
    {
        object->disconnect(with);
    }
    catch (std::bad_cast)
    {
        lua_pushstring(state, "Could not disconnect objects!");
        lua_error(state);
        // long jump
    }
    return 0;
}

int luaUI___object___index(lua_State *state)
{
    /* Stack: 
     *  1: self
     *  2: index
     */
    if (lua_gettop(state) != 2 || !lua_istable(state, 1) || !lua_isstring(state, 2))
    {
        lua_pushstring(state, "Invalid arguments!");
        lua_error(state);
        //long jump
    }
                                    // #1: self #2: index
    lua_pushstring(state, "read");  // #1: self #2: index   #-1: "read"
    lua_rawget(state, 1);           // #1: self #2: index   #-1: read
    lua_pushvalue(state, 2);        // #1: self #2: index   #-2: read   #-1: index
    lua_call(state, 1, 1);          // #1: self #2: index   #-1: value
    return 1;
}

int luaUI___object___newindex(lua_State *state)
{
    /* Stack:
     *  1: self
     *  2: index
     *  3: value
     */
    if (lua_gettop(state) != 3 || !lua_istable(state, 1) || !lua_isstring(state, 2) || !lua_isstring(state, 3))
    {
        lua_pushstring(state, "Invalid arguments!");
        lua_error(state);
        //long jump
    }
                                        // #1: self #2: index   #-1: value
    lua_pushstring(state, "update");    // #1: self #2: index   #-2: value  #-1: "update"
    lua_rawget(state, 1);               // #1: self #2: index   #-2: value  #-1: update
    lua_pushvalue(state, 2);            // #1: self #2: index   #-3: value  #-2: update     #-1: index
    lua_pushvalue(state, 3);            // #1: self #2: index   #-4: value  #-3: update     #-2: index  #-1: value
    lua_call(state, 2, 0);              // #1: self #2: index   #-1: value
    return 0;
}

int luaUI___object___eq(lua_State *state)
{
    /* Stack:
     *  1: self
     *  2: with
     */
    if (lua_gettop(state) != 2 || !lua_istable(state, 1) || !lua_istable(state, 2))
    {
        lua_pushstring(state, "Invalid arguments!");
        lua_error(state);
        // long jump
    }

    lua_pushstring(state, "__object");   // #1: self #2: with    #-1: "__varid"
    lua_rawget(state, 1);               // #1: self #2: with    #-1: selfid
    Core::Object *obj = (Core::Object *)lua_touserdata(state, -1);
    lua_pop(state, 1);                  // #1: self #2: with
    lua_pushstring(state, "__object");   // #1: self #2: with    #-1: "__varid"
    lua_rawget(state, 2);               // #2: self #2: with    #-1: withid
    Core::Object *with = (Core::Object *)lua_touserdata(state, -1);
    lua_pop(state, 1);                  // #1: self #2: with
    lua_pushboolean(state, obj == with);
                                        // #1: self #2: with    #-1: result
    return 1;
}

int luaUI_create(lua_State *state)
{
    /* stack:
     *  1 - type, must be string which value is 'person', 'group' or 'event'.
     */
    if (lua_gettop(state) != 1 || !lua_isstring(state, 1))
    {
        lua_pushstring(state, "Invalid argument!");
        lua_error(state);
        // long jump in lua_error().
    }
    Core::Object *object = nullptr;
    if (lua_tostring(state, 1) == std::string("person"))
    {
        object = self->create<Core::Person>();
    }
    else if (lua_tostring(state, 1) == std::string("group"))
    {
        object = self->create<Core::Group>();
    }
    else if (lua_tostring(state, 1) == std::string("event"))
    {
        object = self->create<Core::Event>();
    }
    else
    {
        lua_pushstring(state, "Invalid type!");
        lua_error(state);
        // long jump
    }
    luaUI_create_lua_object(state, object);
    return 1;                                               // return object
}

int luaUI_search(lua_State *state)
{
    /* Stack:
     *  1: args
     */
    if (lua_gettop(state) != 1 || !lua_istable(state, 1))
    {
        lua_pushstring(state, "Invalid arguments!");
        lua_error(state);
        // long jump
    }
    lua_pushnil(state);
    std::map<std::string, boost::any> args;
    while(lua_next(state, 1))
    {
        if (!lua_isstring(state, -2) || !lua_isstring(state, -1))
        {
            lua_pushstring(state, "Invalid search argument!");
            lua_error(state);
            // long jump
        }
        std::string field = lua_tostring(state, -2);
        boost::any value;
        if (lua_isnumber(state, -1))
        {
            value = (time_t) lua_tonumber(state, -1);
        }
        else
        {
            value = std::string(lua_tostring(state, -1));
        }
        args[field] = value;
        lua_pop(state, 1);
    }
    lua_pop(state, 1);
    std::vector<Core::Object *> vector = self->search(args);
    lua_createtable(state, 0, 0);
    int i = 0;
    for (Core::Object *obj : vector)
    {
        lua_pushnumber(state, ++i);
        luaUI_create_lua_object(state, obj);
        lua_settable(state, -3);
    }
    return 1;
}

int luaUI_remove(lua_State *state)
{
    /* Stack:
     *  1: object
     */
    if (lua_gettop(state) != 1 || !lua_istable(state, 1))
    {
        lua_pushstring(state, "Invalid argument!");
        lua_error(state);
        // long jump
    }
    lua_pushstring(state, "__object");
    lua_rawget(state, 1);
    self->remove((Core::Object *)lua_touserdata(state, -1));
    return 0;
}

int luaUI___cache___index(lua_State *state)
{
    /* Stack:
     *  1: cache
     *  2: index
     */
    if (lua_gettop(state) != 2 || !lua_isnumber(state, 2))
    {
        lua_pushstring(state, "Invalid argument!");
        lua_error(state);
        // long jump
    }
    try
    {
        luaUI_create_lua_object(state, self->cache().at(lua_tonumber(state, 2) - 1));
    }
    catch (std::out_of_range)
    {
        lua_pushnil(state);
    }
    return 1;
}

int luaUI___cache___newindex(lua_State *state)
{
    /* Stack:
     *  1: cache
     *  2: index
     *  3: value
     */
    if (lua_gettop(state) != 3 || !lua_isnumber(state, 2) || !lua_istable(state, 3))
    {
        lua_pushstring(state, "Invalid argument!");
        lua_error(state);
        // long jump
    }
    lua_pushstring(state, "__object");
    lua_rawget(state, 3);
    self->cache()[lua_tonumber(state, 2) - 1] = (Core::Object *)lua_touserdata(state, -1);
    return 0;
}

int luaUI___cache___len(lua_State *state)
{
    /* Stack:
     *  1: cache
     */
    lua_pushnumber(state, self->cache().size());
    return 1;
}

int luaUI___cache___next(lua_State *state)
{
    /* Stack:
     * 1: cache
     * 2: previous_key
     */
    if (lua_gettop(state) != 2 || !lua_istable(state, 1) || !(lua_isnumber(state, 2) || lua_isnil(state, 2)))
    {
        lua_pushstring(state, "Invalid argument!");
        lua_error(state);
        // long jump
    }
    int key;
    if (lua_isnumber(state, 2))
    {
        key = lua_tonumber(state, 2) + 1;
    }
    else
    {
        key = 1;
    }
    if (self->cache().size() + 1 < key)
    {
        lua_pushnil(state);
        return 1;
    }
    lua_pushnumber(state, key);
    try {
    luaUI_create_lua_object(state, self->cache().at(key - 1));
    }
    catch (std::out_of_range)
    {
        lua_pushnil(state);
        return 1;
    }
    return 2;
}

int luaUI___cache___ipairs(lua_State *state)
{
    if (lua_gettop(state) != 1)
    {
        lua_pushstring(state, "Invalid argument!");
        lua_error(state);
        // long jump
    }
    lua_pushcfunction(state, luaUI___cache___next);
    lua_pushvalue(state, 1);
    lua_pushnil(state);
    return 3;
}

static int luaUI_next(lua_State *state)
{
    if (lua_gettop(state) != 2)
    {
        lua_pushstring(state, "Invalid argument!");
        lua_error(state);
        // long jump
    }
    luaL_getmetafield(state, 1, "__next");
    if (lua_isnil(state, -1))
    {
        lua_pop(state, 1);
        lua_pushvalue(state, lua_upvalueindex(1));
    }
    lua_pushvalue(state, 1);
    lua_pushvalue(state, 2);
    lua_call(state, 2, 2);
    return 2;
}

static int luaUI_pairs (lua_State *state)
{
    if (lua_gettop(state) != 1)
    {
        lua_pushstring(state, "Invalid argument!");
        lua_error(state);
        // long jump
    }
    luaL_getmetafield(state, 1, "__pairs");
    if (lua_isnil(state, 1))
    {
        lua_pop(state, 1);
        lua_pushvalue(state, lua_upvalueindex(1));
    }
    lua_pushvalue(state, 1);
    lua_call(state, 1, 3);
    return 3;
}

static int luaUI_ipairs (lua_State *state)
{
    if (lua_gettop(state) != 1)
    {
        lua_pushstring(state, "Invalid argument!");
        lua_error(state);
        // long jump
    }
    luaL_getmetafield(state, 1, "__ipairs");
    if (lua_isnil(state, 1))
    {
        lua_pop(state, 1);
        lua_pushvalue(state, lua_upvalueindex(1));
    }
    lua_pushvalue(state, 1);
    lua_call(state, 1, 3);
    return 3;
}

int luaUI::run()
{
    self = this;
    vm_ = lua_open();
   
    luaL_openlibs(vm_);

    lua_createtable(vm_, 0, 0);
                    //  __object = {
    lua_pushcfunction(vm_, luaUI___object___index);
    lua_setfield(vm_, -2, "__index");
                    //      __index = function (self, index) ... end,
    lua_pushcfunction(vm_, luaUI___object___newindex);
    lua_setfield(vm_, -2, "__newindex");
                    //      __newindex = function (self, index, value) ... end,
    lua_pushcfunction(vm_, luaUI___object___eq);
    lua_setfield(vm_, -2, "__eq");
                    //      __eq = function (self, with) ... end
    lua_setglobal(vm_, "__object");
                    // }

    lua_createtable(vm_, 0, 0);
    lua_createtable(vm_, 0, 0);
    lua_pushcfunction(vm_, luaUI___cache___index);
    lua_setfield(vm_, -2, "__index");
    lua_pushcfunction(vm_, luaUI___cache___newindex);
    lua_setfield(vm_, -2, "__newindex");
    lua_pushcfunction(vm_, luaUI___cache___len);
    lua_setfield(vm_, -2, "__len");
    lua_pushcfunction(vm_, luaUI___cache___next);
    lua_setfield(vm_, -2, "__next");
    lua_pushcfunction(vm_, luaUI___cache___ipairs);
    lua_setfield(vm_, -2, "__ipairs");
    lua_pushcfunction(vm_, luaUI___cache___ipairs);
    lua_setfield(vm_, -2, "__pairs");
    lua_setmetatable(vm_, -2);
    lua_setglobal(vm_, "cache");
                    // cache = {}

    lua_register(vm_, "create", luaUI_create);
                    // function create (type) ... end
    lua_register(vm_, "search", luaUI_search);
                    //function search (args) ... end
    lua_register(vm_, "remove", luaUI_remove);
                    //function remove(object) ... end
    lua_getglobal(vm_, "next");
    lua_pushcclosure(vm_, luaUI_next, 1);
    lua_setglobal(vm_, "next");
    lua_getglobal(vm_, "pairs");
    lua_pushcclosure(vm_, luaUI_pairs, 1);
    lua_setglobal(vm_, "pairs");
    lua_getglobal(vm_, "ipairs");
    lua_pushcclosure(vm_, luaUI_ipairs, 1);
    lua_setglobal(vm_, "ipairs");

    luaL_loadfile(vm_, script_.c_str());
    if (lua_pcall(vm_, 0, LUA_MULTRET, 0))
    {
        std::cerr << lua_tostring(vm_, -1) << std::endl;
    }
    
    lua_close(vm_);

    return 0;
}

extern "C" {

void init(std::vector<Core::Module *>* modules, void *handle)
{
    new luaUI(modules, handle);
}

};


