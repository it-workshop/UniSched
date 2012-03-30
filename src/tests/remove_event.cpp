#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <event.h>

#define TESTINGUI_NAME "TESTINGUI_REMOVE_EVENT"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *object = create<Core::Event>();
    assert(object);
    remove(object);
    if (search(std::map<std::string, boost::any>()).size())
    {
        return -1;
    }
    return 0;
}

