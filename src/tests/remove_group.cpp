#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <group.h>

#define TESTINGUI_NAME "TESTINGUI_REMOVE_GROUP"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *object = create<Core::Group>();
    assert(object);
    remove(object);

    if(search(std::map<std::string, boost::any>()).size())
    {
        return -1;
    }

    return 0;
}

