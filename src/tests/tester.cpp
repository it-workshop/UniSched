#include <iostream>

#include <locale.h>

#include <abstractui.h>
#include <abstractstorage.h>
#include <module.h>
#include <utils.h>


int
main(int argc, char *argv[])
{
    Core::AbstractUI *ui = nullptr;
    Core::AbstractStorage *storage = nullptr;
    std::vector<std::string> args;
    setenv("UNISCHED_MODULES_PATH", ".", 1);
    for (unsigned int i = 1; i < argc; i++)
        { args.push_back(std::string(argv[i])); }
    setlocale(LC_ALL, "");
    Core::Config conf("");
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
    int code = ui->run();
    if (storage)
    {
        storage->disconnect();
    }
    Core::Module::unload_modules();
    return code;
}

