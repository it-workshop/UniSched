#include <assert.h>

#include <iostream>
#include <typeinfo>

#include <person.h>
#include <group.h>

#define TESTINGUI_NAME "TESTINGUI_DISCONNECT_PERSON"
#include "testingui.h"


int TestingUI::run()
{
    Core::Object *John = create<Core::Person>();
    assert(John);
    Core::Object *James = create<Core::Person>();
    assert(James);
    Core::Object *group = create<Core::Group>();
    assert(group);

    John->connect(group);
    group->connect(James);

    group->disconnect(John);
    James->disconnect(group);

    if (boost::any_cast<const std::vector<Core::Object *>&>(group->read("people")).size()
        || boost::any_cast<const std::vector<Core::Object *>&>(John->read("groups")).size()
        || boost::any_cast<const std::vector<Core::Object *>&>(James->read("groups")).size())
    {
        std::cout << boost::any_cast<const std::vector<Core::Object *>&>(group->read("people")).size() << " "
            << boost::any_cast<const std::vector<Core::Object *>&>(John->read("groups")).size() << " "
            << boost::any_cast<const std::vector<Core::Object *>&>(John->read("groups")).size()
            << std::endl;
        return -1;
    }

    return 0;
}

