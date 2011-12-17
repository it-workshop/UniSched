#include <abstractstorage.h>
#include <abstractui.h>
#include <backend.h>

#include <iostream>

#define _START_ERRORS_DISPATCHING \
    { \
        bool error = false;

#define _ERROR_MESSAGE(message) \
        std::cerr << "Error: " << message << std::endl

#define _CHECK_ERROR(check, message) \
        if (!check) \
        { \
            error = true; \
            _ERROR_MESSAGE(message); \
        }

#define _WARNING_MESSAGE(message) \
        std::cerr << "Warning: " << message << std::endl

#define _CHECK_WARNING(check, message) \
        if (!check) \
            { _WARNING(message); }

#define _END_ERRORS_DISPATCHING \
        if (error) \
            { abort(); } \
    }

int
main(int argc, char *argv[])
{
    // TODO: rename NULL to nullptr
    Storage::AbstractStorage *storage = NULL;
    UI::AbstractUI *ui = NULL;

    std::vector<std::string> args;
    for (unsigned int i = 1; i < argc; i++)
        { args.push_back(std::string(argv[i])); }

    for (auto it = backends.begin(); it != backends.end() && !storage && !ui; it++)
    {
        if (!storage && (*it)->type() == AbstractBackend::STORAGE)
        {
            try
            {
                storage = dynamic_cast<Storage::AbstractStorage *>(*it);
                (*it)->init(args);
            }
            catch(std::bad_cast e)
            {
                _WARNING_MESSAGE("Invalid storage backend!");
                e.what();
            }

            continue;
        }

        if ((*it)->type() == AbstractBackend::UI)
        {
            try
            {
                ui = dynamic_cast<UI::AbstractUI *>(*it);
                (*it)->init(args);
            }
            catch(std::bad_cast e)
            {
                _WARNING_MESSAGE("Invalid ui backend!");
                e.what();
            }

            continue;
        }
    }

    _START_ERRORS_DISPATCHING

    _CHECK_ERROR(storage, "Could not find any storage Backend.");

    _CHECK_ERROR(ui, "Could not find any ui backend.");

    _END_ERRORS_DISPATCHING

    return 0;
}

