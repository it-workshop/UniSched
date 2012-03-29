#include <utils.h>

#include <iconv.h>
#include <langinfo.h>

#include <module.h>

static iconv_t output_conversion;
static iconv_t input_conversation;

void utils::init_iconv()
{
    char *codeset = nl_langinfo(CODESET);
    output_conversion = iconv_open(codeset, "UTF32");
    input_conversation = iconv_open("UTF32", codeset);
}

void utils::deinit_iconv()
{
    iconv_close(output_conversion);
    iconv_close(input_conversation);
}

char *utils::to_char(wchar_t * string)
{
    char *output;
    size_t size = wcslen(string);
    iconv(output_conversion, (char **)&string, &size, &output, nullptr);
    return output;
}

const char *utils::to_char(const wchar_t * string)
{
    return to_char(const_cast<wchar_t *>(string));
}

wchar_t *utils::to_wchar(char * string)
{
    wchar_t *output;
    size_t size = strlen(string);
    iconv(input_conversation, &string, &size, (char **)&output, nullptr);
    return output;
}

const wchar_t *utils::to_wchar(const char * string)
{
    return to_wchar(const_cast<char *>(string));
}

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

            if (*storage || (!storagename.empty() && module-> name() != storagename))
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

    if (/*!storagename.empty() && */!*storage)
    {
        error = true;
        std::cerr << "Error: Requested storage module not found!" << std::endl;
    }

    return error;
}


