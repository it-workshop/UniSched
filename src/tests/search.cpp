#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <person.h>
#include <group.h>

#define TESTINGUI_NAME "TESTINGUI_SEARCH"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *object = create<Core::Person>();
    object->update("name", std::string("John"));
    object->update("surname", std::string("Connor"));
    object->update("sex", std::string("MALE"));
    object->update("Job", std::string("none"));

    object = create<Core::Person>();
    object->update("name", std::string("Sarah"));
    object->update("surname", std::string("Connor"));
    object->update("sex", std::string("FEMALE"));
    object->update("Job", std::string("waiter"));
    
    object = create<Core::Person>();
    object->update("name", std::string("Steve"));
    object->update("surname", std::string("Jobs"));
    object->update("sex", std::string("MALE"));
    object->update("Job", std::string("CEO"));

    object = create<Core::Person>();
    object->update("name", std::string("Steve"));
    object->update("surname", std::string("Wosnyak"));
    object->update("sex", std::string("MALE"));
    object->update("Job", std::string("Enginear"));

    object = create<Core::Group>();
    object->update("name", std::string("Apple computers inc."));

    object = create<Core::Group>();
    object->update("name", std::string("Microsoft Corporation"));

    object = create<Core::Group>();
    object->update("name", std::string("XEROX PARC"));

    reset_cache();

    std::map<std::string, boost::any> args;

    if (search(args).size() != 7)
    {
        return -1;
    }

    args["name"] = std::string("Steve");

    if (search(args).size() != 2)
    {
        return -2;
    }

    args.clear();
    args["surname"] = std::string("Connor");
    args["Job"] = std::string("none");

    if (search(args).size() != 1)
    {
        return -3;
    }

    return 0;
}

