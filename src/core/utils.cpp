#include <utils.h>

#include <iconv.h>
#include <langinfo.h>

#include <module.h>

#include <algorithm.h>

bool
utils::select_modules (Core::AbstractUI **ui, Core::AbstractStorage **storage,
               std::vector<std::string>& args)
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
                module->init(args);
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
                module->init(args);
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
    return error;
}


