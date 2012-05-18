
#include <windows-spike.h>

#include <windows.h>
#include <winbase.h>

int setenv(const char *name, const char *value, int override) {
    int error = GetEnvironmentVariable(name, nullptr, 0);
    if (!error)
    {
        if (GetLastError() != ERROR_ENVVAR_NOT_FOUND)
        {
            return -1;
        }
        override = 1;
    }
    if (override)
    {
        return SetEnvironmentVariable(name, value) ? 0 : -1;
    }
    return 0;
}

void *dlopen(const char *filename, int flag)
{
    return LoadLibrary(filename);
}

char *dlerror()
{
    char *str;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER, 0, GetLastError(), 0, (LPTSTR) &str, 0, nullptr);
    return str;
}

void *dlsym(void *handle, const char *symbol)
{
    return (void *)GetProcAddress((HMODULE)handle, symbol);
}

int dlclose(void *handle)
{
    return !FreeLibrary((HMODULE)handle);
}

