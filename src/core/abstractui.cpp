#include <abstractui.h>
#include <person.h>
#include <group.h>
#include <event.h>

#include <sys/types.h>
#include <dirent.h>
#include <stdexcept>

using namespace Core;

static const bool operator==(const boost::any& lhs, const boost::any& rhs)
    throw (boost::bad_any_cast)
{
    if (lhs.empty() != rhs.empty())
    {
        return false;
    }
    if (typeid(std::string) == lhs.type())
    {
        return boost::any_cast<std::string>(lhs)
            == boost::any_cast<std::string>(rhs);
    }
    if (typeid(time_t) == lhs.type())
    {
        return boost::any_cast<time_t>(lhs)
            == boost::any_cast<time_t>(rhs);
    }
    throw boost::bad_any_cast();
}

std::vector<Object *> AbstractUI::search(const std::map<std::string, boost::any>& parameters)
{
    std::vector<Object *> results;
    for(auto object : objects_)
    {
        results.push_back(object.second);
    }
    for (auto p: parameters)
    {
        for (auto it = results.begin(); it != results.end(); it++)
        {
            try
            {
                if (p.second == (*it)->read(p.first))
                {
                    continue;
                }
            }
            catch (std::bad_cast)
            {}
            it = results.erase(it);
            it--;
        }
    }
    return results;
}

void AbstractUI::push(const int id, const std::string& name,
        const boost::any& value)
{
    if (storage_)
    {
        storage_->push(id, name, value);
    }
}

void AbstractUI::push(Object * object, Object * with, bool connect)
{
    if (storage_)
    {
        storage_->push_connect(object->id(), with->id(), connect);
    }
}

void AbstractUI::remove(Object *object)

{
    int id = object->id();
    objects_.erase(objects_.find(id));
    object->cleanup();
    delete object;
    if (storage_)
    {
        storage_->remove(id);
    }
}

static AbstractUI *self = nullptr;

int AbstractUI::_lua___object___index(lua_State *state)
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

int AbstractUI::_lua___object___newindex(lua_State *state)
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

int AbstractUI::_lua___object___eq(lua_State *state)
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

int AbstractUI::_lua_object_type(lua_State *state)
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

void AbstractUI::lua_create_lua_object(lua_State *state, Core::Object *object)
{
    lua_createtable(state, 0, 0);                           // #-1: object

    lua_pushlightuserdata(state, object);
    lua_pushcclosure(state, _lua_object_type, 1);          // #-2: object, #-1: [id]type()
    lua_setfield(state, -2, "type");                        // #-1: object
    
    lua_pushlightuserdata(state, object);
    lua_pushcclosure(state, _lua_object_read, 1);          // #-2: object, #-1: [id]read()
    lua_setfield(state, -2, "read");                        // #-1: object

    lua_pushlightuserdata(state, object);
    lua_pushcclosure(state, _lua_object_update, 1);        // #-2: object, #-1: [id]update()
    lua_setfield(state, -2, "update");                      // #-1: object
    
    lua_pushlightuserdata(state, object);
    lua_pushcclosure(state, _lua_object_connect, 1);       // #-2: object, #-1: [id]connect()
    lua_setfield(state, -2, "connect");                     // #-1: object

    lua_pushlightuserdata(state, object);
    lua_pushcclosure(state, _lua_object_disconnect, 1);    // #-2: object, #-1: [id]disconnect()
    lua_setfield(state, -2, "disconnect");                  // #-1: object

    lua_pushlightuserdata(state, object);
    lua_setfield(state, -2, "__object");                     // #-1: object

    lua_getglobal(state, "__object");                       // #-2: object, #-1: __object
    lua_setmetatable(state, -2);                            // #-1: object
}

int AbstractUI::_lua_object_read(lua_State *state)
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
                    lua_create_lua_object(state, obj);
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
            lua_create_lua_object(state, obj);
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

int AbstractUI::_lua_object_update(lua_State *state)
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

int AbstractUI::_lua_object_connect(lua_State *state)
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

int AbstractUI::_lua_object_disconnect(lua_State *state)
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

int AbstractUI::_lua_create(lua_State *state)
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
    lua_create_lua_object(state, object);
    return 1;                                               // return object
}

int AbstractUI::_lua_search(lua_State *state)
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
        lua_create_lua_object(state, obj);
        lua_settable(state, -3);
    }
    return 1;
}

int AbstractUI::_lua_remove(lua_State *state)
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

bool is_algorithm_name(std::string name)
{
    if (name.c_str()[0] == '.')
    {
        return false;
    }
    return name.rfind(".lua") != std::string::npos
        || name.rfind(".so") != std::string::npos;
}

void AbstractUI::init_algorithms()
{
    self = this;
    vm_ = lua_open();
   
    luaL_openlibs(vm_);

    lua_createtable(vm_, 0, 0);
                    //  __object = {
    lua_pushcfunction(vm_, _lua___object___index);
    lua_setfield(vm_, -2, "__index");
                    //      __index = function (self, index) ... end,
    lua_pushcfunction(vm_, _lua___object___newindex);
    lua_setfield(vm_, -2, "__newindex");
                    //      __newindex = function (self, index, value) ... end,
    lua_pushcfunction(vm_, _lua___object___eq);
    lua_setfield(vm_, -2, "__eq");
                    //      __eq = function (self, with) ... end
    lua_setglobal(vm_, "__object");
                    // }

    lua_register(vm_, "create", _lua_create);
                    // function create (type) ... end
    lua_register(vm_, "search", _lua_search);
                    //function search (args) ... end
    lua_register(vm_, "remove", _lua_remove);
                    //function remove(object) ... end

    std::stringstream modules;
    setenv("UNISCHED_ALGORITHMS", "", 0);
    lua_getglobal(vm_, "package");
    lua_getfield(vm_, -1, "path");
    std::stringstream path;
    path << lua_tostring(vm_, -1) << ';' << getenv("UNISCHED_ALGORITHMS_PATH");
    lua_pop(vm_, 1);
    lua_pushstring(vm_, path.str().c_str());
    lua_setfield(vm_, -2, "path");
    modules << getenv("UNISCHED_ALGORITHMS");
    char module[4096];
    for (modules.getline(module, 4096, ','); !modules.eof() || *module;
        modules.getline(module, 4096, ','))
    {
        std::cout << "Loading " << module << "\t";
        lua_getglobal(vm_, "require");
        lua_pushstring(vm_, module);
        if (lua_pcall(vm_, 1, 0, 0))
        {
            std::cout << "FAIL\n" << lua_tostring(vm_, -1) << std::endl;
            lua_pop(vm_, 1);
        }
        else
        {
            std::cout << "OK" << std::endl;
        }
    }
}

void AbstractUI::deinit_algorithms()
{
    lua_close(vm_);
}

void AbstractUI::create_in_storage(const Object *object)
{
    if (storage_)
    {
        storage_->create(object);
    }
}

