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
    Core::Module::load_modules();
    if (utils::select_modules(&ui, &storage, args))
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

