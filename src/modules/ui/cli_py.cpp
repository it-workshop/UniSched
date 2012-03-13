#include <boost/python.hpp>

#include <abstractui.h>
#include <abstractstorage.h>
#include <module.h>
#include <utils.h>
#include <cli_py_names.hpp>


char const* greet()
{
    return "Test python bindings";
}

int prepare_your_anus() {
    Core::AbstractUI *ui = nullptr;
    Core::AbstractStorage *storage = nullptr;
    std::vector<std::string> args;
    args.push_back("--iface");
    args.push_back("DummyUI");
    Core::Module::load_modules();
    if (utils::select_modules(&ui, &storage, args))
    {
        return -1;
    }
    int code = ui->run();
    Core::Module::unload_modules();
    return code;
}

BOOST_PYTHON_MODULE(CLI_PY_LIB_CLEAN_NAME)
{
    using namespace boost::python;
    def("greet", greet);
    def("anus_preporaro", prepare_your_anus);
}
