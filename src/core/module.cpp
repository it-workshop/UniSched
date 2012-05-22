#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

#ifndef _USE_WINDOWS_SPIKE_
#include <dlfcn.h>
#else /* _USE_WINDOWS_SPIKE_ */
#include <windows-spike.h>
#endif /* _USE_WINDOWS_SPIKE_ */

#include <sstream>
#include <iostream>

#include <module.h>
#ifdef WITH_EXT_PYTHON_CLI
#include <cli_py_names.hpp>
#endif

using namespace Core;

Module::Module (const enum Type type, const std::string& name,
        std::vector<Module *>* modules, void * handle):
    type_(type), name_(name), handle_(handle)
{
    modules->push_back(this);
}

static std::vector<Module *> modules_;

static bool has_ending(std::string input, std::string ending) {
    return (input.rfind(ending) != std::string::npos);
}

static const bool is_module_name(const std::string& name) {
#ifdef WITH_EXT_PYTHON_CLI
    if (name.find(CLI_PY_LIB_NAME) != std::string::npos)
    {
        return false;
    }
#endif
    if (!has_ending(name, ".so"))
    {
        return false;
    }
    return '.' != *(name.c_str());
}

void Module::load_modules(Core::Config& conf)
{
    std::stringstream modules_path;
    setenv("UNISCHED_MODULES_PATH", ".", 0);
    modules_path << getenv("UNISCHED_MODULES_PATH");
    lua_getglobal(conf.vm(), "config");
    lua_getfield(conf.vm(), -1, "modules_path");
    if (lua_isstring(conf.vm(), -1))
    {
        modules_path << ':' << lua_tostring(conf.vm(), -1);
    }
    lua_pop(conf.vm(), 3);
    char dir_name[4096];
    for (modules_path.getline(dir_name, 4096, ':'); *dir_name || !modules_path.eof();
        modules_path.getline(dir_name, 4096, ':'))
    {
        if (!*dir_name)
        {
            continue;
        }
        DIR * dir = opendir(dir_name);
        if (!dir)
        {
            perror(dir_name);
            continue;
        }
        for (struct dirent *entry = readdir(dir); entry; entry = readdir(dir))
        {
            if (!is_module_name(entry->d_name))
            {
                //std::cout << "Skipping " << entry->d_name << "\n";
                continue;
            }
            std::cout << "Loading " << entry->d_name << "\t";
            std::string module_name = std::string(dir_name) + "/" + entry->d_name;
            void *module_handle = dlopen(module_name.c_str(), RTLD_NOW);
            if (!module_handle)
            {
                std::cout << "FAIL" << std::endl << dlerror() << std::endl;
                continue;
            }
            void (*module_loader)(std::vector<Module *>*, void*) =
                (void (*)(std::vector<Module *>*, void*))
                    dlsym(module_handle, "init");
            if (!module_loader)
            {
                std::cout << "FAIL" << std::endl << dlerror() << std::endl;
                dlclose(module_handle);
                continue;
            }
            (*module_loader)(&modules_, module_handle);
            std::cout << "OK" << std::endl;
        }
        closedir(dir);
    }
}

void Module::unload_modules() {
    for (auto it = modules_.begin(); it != modules_.end();
        it = modules_.erase(it))
    {
        void *module_handle = (*it)->handle_;
        delete *it;
        dlclose(module_handle);
    }
}

std::vector<Module *> * Module::modules()
{
    return &modules_;
}

