#include <manager.h>
#include <abstractui.h>
#include <module.h>

#include <iostream>

bool
load_modules (/*Core::Manager **manager,*/ UI::AbstractUI **ui,
               std::vector<std::string>& args)
{
/*    *manager = nullptr;*/
    *ui = nullptr;
    std::string uiname;
    for (auto it = args.begin(); it != args.end(); it++)
    {
        if (*it == "--iface")
        {
            uiname = *++it;
        }
    }
    for (Module *module: modules())
    {
/*        if (*manager && *ui)
        {
            break;
        }
        if (module->type() == Module::STORAGE)
        {
            if (*manager)
            {
                continue;
            }
            try
            {
                *manager = dynamic_cast<Core::Manager *>(module);
                module->init(args);
            }
            catch (std::bad_cast e)
            {
                std::cerr << "Warning: invalid manager module!" << e.what() <<
		            std::endl;
                *manager = nullptr;
            }
            continue;
        }*/

        if (module->type() == Module::UI)
        {
            if (*ui || uiname.empty() || module->name() != uiname)
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
/*    if (!*manager)
    {
        error = true;
        std::cerr << "Error: manager module not found!" << std::endl;
    }*//* storage module is not always needed. */
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
/*    Core::Manager *manager = nullptr;*/
    UI::AbstractUI *ui = nullptr;

    std::vector<std::string> args;
    for (unsigned int i = 1; i < argc; i++)
        { args.push_back(std::string(argv[i])); }

    if (load_modules(/*&manager,*/ &ui, args))
    {
        return -1;
    }

    return ui->run();
}

