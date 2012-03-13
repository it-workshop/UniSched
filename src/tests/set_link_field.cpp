#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <person.h>

#define TESTINGUI_NAME "TESTINGUI_SET_LINK_FIELD"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *object = create<Core::Person>();
    assert(object);

    try
    {
        object->update("groups", std::string("Why can not I set this field?"));
    }
    catch (boost::bad_any_cast& e)
    {
        std::cout << "Exception is catched :) " << e.what() << std::endl;
        return 0;
    }

    std::cout << "Exception is not catched." << std::endl;

    return 1;
}

