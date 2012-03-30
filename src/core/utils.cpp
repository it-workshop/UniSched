#include <utils.h>

#include <iconv.h>
#include <langinfo.h>

#include <module.h>

static iconv_t output_conversion;
static iconv_t input_conversion;

void utils::init_iconv()
{
    char *codeset = nl_langinfo(CODESET);
    output_conversion = iconv_open(codeset, "UTF32");
    input_conversion = iconv_open("UTF32", codeset);
}

void utils::deinit_iconv()
{
    iconv_close(output_conversion);
    iconv_close(input_conversion);
}

char *utils::iconv(wchar_t * string)
{
    size_t length = wcslen(string)*4+1;
    size_t out_size = length;
    char *output = new char[length];
    char *ptr = output;
    ::iconv(output_conversion, (char **)&string, &length, &ptr, &out_size);
    char *ret = const_cast<char *>(std::string(output).c_str());
    delete output;
    return ret;
}

const char *utils::iconv(const wchar_t * string)
{
    return iconv(const_cast<wchar_t *>(string));
}

wchar_t *utils::iconv(char * string)
{
    size_t length = strlen(string)+1;
    size_t out_size = length+1;
    wchar_t *output = new wchar_t[length];
    char *ptr = (char *)output;
    ::iconv(input_conversion, &string, &length, &ptr, &out_size);
    wchar_t *ret = const_cast<wchar_t *>(std::wstring(output).c_str());
    delete output;
    return ret;
}

const wchar_t *utils::iconv(const char * string)
{
    return iconv(const_cast<char *>(string));
}

char *utils::iconv(std::wstring& string)
{
    return iconv(const_cast<wchar_t *>(string.c_str()));
}

const char *utils::iconv(const std::wstring& string)
{
    return iconv(const_cast<wchar_t *>(string.c_str()));
}

wchar_t *utils::iconv(std::string& string)
{
    return iconv(const_cast<char *>(string.c_str()));
}

const wchar_t *utils::iconv(const std::string& string)
{
    return iconv(string.c_str());
}

bool
utils::select_modules (Core::AbstractUI **ui, Core::AbstractStorage **storage,
               std::vector<std::wstring>& args)
{
    *ui = nullptr;
    *storage = nullptr;
    std::wstring uiname;
    std::wstring storagename;
    for (auto it = args.begin(); it != args.end(); it++)
    {
        if (*it == L"--iface")
        {
            uiname = *++it;
        }
        if (*it == L"--storage")
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
                std::wcerr << L"Warning: invalid storage module!" << e.what() <<
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
                std::wcerr << L"Warning: invalid ui module!" << e.what() <<
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
        std::wcerr << L"Error: ui module not found!" << std::endl;
    }

    if (!storagename.empty() && !*storage)
    {
        error = true;
        std::wcerr << L"Error: Requested storage module not found!" << std::endl;
    }

    return error;
}


