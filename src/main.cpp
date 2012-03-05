#include <abstractui.h>
#include <abstractui.h>
#include <module.h>

#include <iostream>

bool
select_modules (Core::AbstractUI **ui,
               std::vector<std::string>& args)
{
    *ui = nullptr;
    std::string uiname;
    for (auto it = args.begin(); it != args.end(); it++)
    {
        if (*it == "--iface")
        {
            uiname = *++it;
        }
    }
    for (Core::Module *module: *Core::Module::modules())
    {
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

    return error;
}

int
main(int argc, char *argv[])
{
    Core::AbstractUI *ui = nullptr;
    std::vector<std::string> args;
    for (unsigned int i = 1; i < argc; i++)
        { args.push_back(std::string(argv[i])); }
    Core::Module::load_modules();
    if (select_modules(&ui, args))
    {
        return -1;
    }
    int code = ui->run();
    Core::Module::unload_modules();
    return code;
}

