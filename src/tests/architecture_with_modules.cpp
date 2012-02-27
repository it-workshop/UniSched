#include <abstractui.h>
#include <abstractui.h>
#include <module.h>

#include <iostream>

bool
load_modules (Storage::AbstractStorage **storage, UI::AbstractUI **ui,
               std::vector<std::string>& args)
{
    *storage = nullptr;
    *ui = nullptr;
    for (Module *module: modules())
    {
        if (*storage && *ui)
        {
            break;
        }

        if (module->type() == Module::STORAGE)
        {
            if (*storage)
            {
                continue;
            }
            try
            {
                *storage = dynamic_cast<Storage::AbstractStorage *>(module);
                module->init(args);
            }
            catch (std::bad_cast e)
            {
                std::cerr << "Warning: invalid storage module!" << e.what() <<
		    std::endl;
                *storage = nullptr;
            }
            continue;
        }

        if (module->type() == Module::UI)
        {
            if (*ui)
            {
                continue;
            }
            try
            {
                *ui = dynamic_cast<UI::AbstractUI *>(module);
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
    if (!*storage)
    {
        error = true;
        std::cerr << "Error: storage module not found!" << std::endl;
    }
    if (!*ui)
    {
        error = true;
        std::cerr << "Error: ui module not found!" << std::endl;
    }

    return error;
}

int
main(int argc, char *argv[])
{
    Storage::AbstractStorage *storage = nullptr;
    UI::AbstractUI *ui = nullptr;

    std::vector<std::string> args;
    for (unsigned int i = 1; i < argc; i++)
        { args.push_back(std::string(argv[i])); }

    if (load_modules(&storage, &ui, args))
    {
        return -1;
    }

    return 0;
}

