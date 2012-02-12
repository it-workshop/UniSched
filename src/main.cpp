#include <manager.h>
#include <abstractui.h>
#include <backend.h>

#include <iostream>

bool
load_backends (Core::Manager **manager, UI::AbstractUI **ui,
               std::vector<std::string>& args)
{
    *manager = nullptr;
    *ui = nullptr;
    for (AbstractBackend *backend: backends())
    {
        if (*manager && *ui)
        {
            break;
        }

        if (backend->type() == AbstractBackend::STORAGE)
        {
            if (*manager)
            {
                continue;
            }
            try
            {
                *manager = dynamic_cast<Core::Manager *>(backend);
                backend->init(args);
            }
            catch (std::bad_cast e)
            {
                std::cerr << "Warning: invalid manager backend!" << e.what() <<
		    std::endl;
                *manager = nullptr;
            }
            continue;
        }

        if (backend->type() == AbstractBackend::UI)
        {
            if (*ui)
            {
                continue;
            }
            try
            {
                *ui = dynamic_cast<UI::AbstractUI *>(backend);
                backend->init(args);
            }
            catch (std::bad_cast e)
            {
                std::cerr << "Warning: invalid ui backend!" << e.what() <<
                    std::endl;
                *ui = nullptr;
            }
            continue;
        }
    }

    bool error = false;
    if (!*manager)
    {
        error = true;
        std::cerr << "Error: manager backend not found!" << std::endl;
    }
    if (!*ui)
    {
        error = true;
        std::cerr << "Error: ui backend not found!" << std::endl;
    }

    return error;
}

int
main(int argc, char *argv[])
{
    Core::Manager *manager = nullptr;
    UI::AbstractUI *ui = nullptr;

    std::vector<std::string> args;
    for (unsigned int i = 1; i < argc; i++)
        { args.push_back(std::string(argv[i])); }

    if (load_backends(&manager, &ui, args))
    {
        return -1;
    }

    return ui->run();
}

