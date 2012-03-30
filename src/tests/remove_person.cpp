#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <person.h>

#define TESTINGUI_NAME "TESTINGUI_REMOVE_PERSON"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *object = create<Core::Person>();
    assert(object);

    remove(object);
    if (search(std::map<std::string, boost::any>()).size())
    {
        return -1;
    }

    return 0;
}

