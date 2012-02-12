#include <manager.h>
#include <abstractui.h>
#include <backend.h>

#include <iostream>

bool
load_backends (Storage::AbstractStorage **storage, UI::AbstractUI **ui,
               std::vector<std::string>& args)
{
    *storage = nullptr;
    *ui = nullptr;
    for (AbstractBackend *backend: backends())
    {
        if (*storage && *ui)
        {
            break;
        }

        if (backend->type() == AbstractBackend::STORAGE)
        {
            if (*storage)
            {
                continue;
            }
            try
            {
                *storage = dynamic_cast<Storage::AbstractStorage *>(backend);
                backend->init(args);
            }
            catch (std::bad_cast e)
            {
                std::cerr << "Warning: invalid storage backend!" << e.what() <<
		    std::endl;
                *storage = nullptr;
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
    if (!*storage)
    {
        error = true;
        std::cerr << "Error: storage backend not found!" << std::endl;
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
    Storage::AbstractStorage *storage = nullptr;
    UI::AbstractUI *ui = nullptr;

    std::vector<std::string> args;
    for (unsigned int i = 1; i < argc; i++)
        { args.push_back(std::string(argv[i])); }

    if (load_backends(&storage, &ui, args))
    {
        return -1;
    }

    return 0;
}

