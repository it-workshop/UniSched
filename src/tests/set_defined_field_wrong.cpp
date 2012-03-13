#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <person.h>

#define TESTINGUI_NAME "TESTINGUI_SET_DEFINED_FIELD_WRONG"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *object = create<Core::Person>();

    assert(object);

    try
    {
        object->update("name", 0);
    }
    catch (boost::bad_any_cast& e)
    {   
        std::cout << "Catched exception :) "<< e.what() << std::endl;
        return 0;
    }

    return -1;
}

