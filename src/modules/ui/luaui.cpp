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
private:
    std::string script_;
    lua_State *vm_;
    std::vector<Core::Object *> objects_;
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
    switch (self->objects_.at(lua_tonumber(state, lua_upvalueindex(1)))->type())
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
    int id = self->objects_.size();
    self->objects_.push_back(object);               // Stack:
    lua_createtable(state, 0, 0);                           // #-1: object

    lua_pushnumber(state, id);                              // #-2: object, #-1: id
    lua_pushcclosure(state, luaUI_object_type, 1);          // #-2: object, #-1: [id]type()
    lua_setfield(state, -2, "type");                        // #-1: object
    
    lua_pushnumber(state, id);                              // #-2: object, #-1: id
    lua_pushcclosure(state, luaUI_object_read, 1);          // #-2: object, #-1: [id]read()
    lua_setfield(state, -2, "read");                        // #-1: object

    lua_pushnumber(state, id);                              // #-2: object, #-1: id
    lua_pushcclosure(state, luaUI_object_update, 1);        // #-2: object, #-1: [id]update()
    lua_setfield(state, -2, "update");                      // #-1: object
    
    lua_pushnumber(state, id);                              // #-2: object, #-1: id
    lua_pushcclosure(state, luaUI_object_connect, 1);       // #-2: object, #-1: [id]connect()
    lua_setfield(state, -2, "connect");                     // #-1: object

    lua_pushnumber(state, id);                              // #-2: object, #-1: id
    lua_pushcclosure(state, luaUI_object_disconnect, 1);    // #-2: object, #-1: [id]disconnect()
    lua_setfield(state, -2, "disconnect");                  // #-1: object

    lua_pushnumber(state, id);                              // #-2: object, #-1: id
    lua_setfield(state, -2, "__varid");                     // #-1: object

    lua_getglobal(state, "__object");                       // #-2: object, #-1: __object
    lua_setmetatable(state, -2);                            // #-1: object
}

int luaUI_object_read(lua_State *state)
{
    /* Stack:
     *  1: index
     *  lua_upvalueindex(1): varid
     */
    if (lua_gettop(state) != 1 || !lua_isstring(state, 1))
    {
        lua_pushstring(state, "Invalid arguments!");
        lua_error(state);
        // long jump
    }
    std::string field = lua_tostring(state, 1);
    Core::Object *object = self->objects_.at(lua_tonumber(state, lua_upvalueindex(1)));
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
        for (Core::Object *obj : vector)
        {
            lua_createtable(state, 0, 0);
            luaUI_create_lua_object(state, obj);
            lua_pushnumber(state, ++i);
            lua_settable(state, -2);
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
    return 0;
}

int luaUI_object_connect(lua_State *state)
{
    return 0;
}

int luaUI_object_disconnect(lua_State *state)
{
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

    lua_pushstring(state, "__varid");   // #1: self #2: with    #-1: "__varid"
    lua_rawget(state, 1);               // #1: self #2: with    #-1: selfid
    int selfid = lua_tonumber(state, -1);
    lua_pop(state, 1);                  // #1: self #2: with
    lua_pushstring(state, "__varid");   // #1: self #2: with    #-1: "__varid"
    lua_rawget(state, 2);               // #2: self #2: with    #-1: withid
    int withid = lua_tonumber(state, -1);
    lua_pop(state, 1);                  // #1: self #2: with
    lua_pushboolean(state, self->objects_.at(selfid) == self->objects_.at(withid));
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
    return 0;
}

int luaUI_remove(lua_State *state)
{
    return 0;
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
    lua_setglobal(vm_, "cache");
                    // cache = {}

    lua_register(vm_, "create", luaUI_create);
                    // function create (type) ... end
    lua_register(vm_, "search", luaUI_search);
                    //function search (args) ... end
    lua_register(vm_, "remove", luaUI_remove);
                    //function remove(object) ... end

    luaL_loadfile(vm_, script_.c_str());
    lua_pcall(vm_, 0, LUA_MULTRET, 0);
    
    lua_close(vm_);

    return 0;
}

extern "C" {

void init(std::vector<Core::Module *>* modules, void *handle)
{
    new luaUI(modules, handle);
}

};


