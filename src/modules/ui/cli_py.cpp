#include <boost/python.hpp>

#include <cli_py_names.hpp>


char const* greet()
{
    return "Test python bindings";
}

BOOST_PYTHON_MODULE(CLI_PY_LIB_CLEAN_NAME)
{
    using namespace boost::python;
    def("greet", greet);
}
