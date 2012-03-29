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
    std::vector<std::wstring> args;
    
    std::clog << "libc locale: " << std::setlocale(LC_ALL, "") << std::endl;
    std::locale::global(std::locale(""));
    std::clog << "stl C++ locale: " << std::locale().name() << std::endl;
    std::cout.imbue(std::locale());
    std::cerr.imbue(std::locale());
    std::clog.imbue(std::locale());
    std::cin.imbue(std::locale());
    std::wcout.imbue(std::locale());
    std::wcerr.imbue(std::locale());
    std::wclog.imbue(std::locale());
    std::wcin.imbue(std::locale());
    std::ios::sync_with_stdio(false);
    utils::init_iconv();

    for (unsigned int i = 1; i < argc; i++)
        { args.push_back(std::wstring(utils::iconv(argv[i]))); }
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
    int code = ui->run();
    if (storage)
    {
        storage->disconnect();
    }
    Core::Module::unload_modules();
    utils::deinit_iconv();
    return code;
}

