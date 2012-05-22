#include <iostream>

#include <locale.h>

#include <abstractui.h>
#include <abstractstorage.h>
#include <module.h>
#include <utils.h>

#include <version.h>

int
main(int argc, char *argv[])
{
    std::cout << "UniSched Version: " << UNISCHED_VERSION << std::endl;
    Core::AbstractUI *ui = nullptr;
    Core::AbstractStorage *storage = nullptr;
    std::vector<std::string> args;
    for (unsigned int i = 1; i < argc; i++)
        { args.push_back(std::string(argv[i])); }
    setlocale(LC_ALL, "");
    std::string confname;
    for ( auto it = args.begin(); it != args.end(); it++)
    {
        if (*it == "-f")
        {
            confname = *++it;
            break;
        }
    }
    if (confname.empty())
    {
        confname = std::string(getenv("HOME")) + "/.unisched/rc.lua";
    }
    Core::Config conf(confname);

    Core::Module::load_modules(conf);
    if (utils::select_modules(&ui, &storage, conf, args))
    {
        return -1;
    }
    if (storage)
    {
        storage->set_UI(ui);
        storage->connect();
    }
    ui->init_algorithms();
    int code = ui->run();
    ui->deinit_algorithms();
    if (storage)
    {
        storage->disconnect();
    }
    Core::Module::unload_modules();
    return code;
}

