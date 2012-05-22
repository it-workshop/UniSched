#include <utils.h>

#include <module.h>

bool
utils::select_modules (Core::AbstractUI **ui, Core::AbstractStorage **storage,
               Core::Config& conf, std::vector<std::string>& args)
{
    *ui = nullptr;
    *storage = nullptr;
    std::string uiname;
    std::string storagename;
    for (auto it = args.begin(); it != args.end(); it++)
    {
        if (*it == "--iface")
        {
            uiname = *++it;
        }
        if (*it == "--storage")
        {
            storagename = *++it;
        }
    }
    if (uiname.empty())
    {
        lua_getglobal(conf.vm(), "config");
        lua_getfield(conf.vm(), -1, "ui");
        if (lua_isstring(conf.vm(), -1))
        {
            uiname = lua_tostring(conf.vm(), -1);
        }
        lua_pop(conf.vm(), 3);
    }
    if (storagename.empty())
    {
        lua_getglobal(conf.vm(), "config");
        lua_getfield(conf.vm(), -1, "storage");
        if (lua_isstring(conf.vm(), -1))
        {
            storagename = lua_tostring(conf.vm(), -1);
        }
        lua_pop(conf.vm(), 3);
    }

    for (Core::Module *module: *Core::Module::modules())
    {
        if (module->type() == Core::Module::STORAGE)
        {

            if (*storage || storagename.empty() || module-> name() != storagename)
            {
                continue;
            }
            try
            {
                *storage = dynamic_cast<Core::AbstractStorage *>(module);
                module->init(conf, args);
            }
            catch (std::bad_cast e)
            {
                std::cerr << "Warning: invalid storage module!" << e.what() <<
                    std::endl;
                *storage = nullptr;
            }
        }

        if (module->type() == Core::Module::UI)
        {
            if (*ui || (!uiname.empty() && module->name() != uiname))
            {
                continue;
            }
            try
            {
                *ui = dynamic_cast<Core::AbstractUI *>(module);
                module->init(conf, args);
            }
            catch (std::bad_cast e)
            {
                std::cerr << "Warning: invalid ui module!" << e.what() <<
                    std::endl;
                *ui = nullptr;
            }
            continue;
        }
    }

    bool error = false;
    if (!*ui)
    {
        error = true;
        std::cerr << "Error: ui module not found!" << std::endl;
    }

    if (!storagename.empty() && !*storage)
    {
        error = true;
        std::cerr << "Error: Requested storage module not found!" << std::endl;
    }

    if (!error)
    {
        lua_getglobal(conf.vm(), "onload");
        if (!lua_isnil(conf.vm(), -1))
        {
            if(lua_pcall(conf.vm(), 0, 0, 0))
            {
                std::cerr << lua_tostring(conf.vm(), -1) << std::endl;
                lua_pop(conf.vm(), 1);
            }
        }
        lua_pop(conf.vm(), 3);
    }

    return error;
}


