#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <person.h>

#define TESTINGUI_NAME "TESTINGUI_SET_UNDEFINED_FIELD_WRONG"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *object = create<Core::Person>();
    assert(object);

    object->update("Job", std::string("slave"));
    std::cout << object->read("Job").type().name() << std::endl;
    try
    {
        object->update("Job", time_t(0));
        std::cout << object->read("Job").type().name() << std::endl;
    }
    catch (boost::bad_any_cast& e)
    {
        std::cout << "Exception is catched :) " << e.what() << std::endl;
        return 0;
    }

    std::cout << "Exception is not catched." << std::endl;

    return 1;
}

