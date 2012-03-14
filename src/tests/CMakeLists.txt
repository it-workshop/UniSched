cmake_minimum_required (VERSION 2.8)

if (WITH_TESTS_CORE)
    add_executable (tester tester.cpp)
    target_link_libraries (tester core)

    add_library (create_person SHARED create_person.cpp)
    add_test (create_person_test tester --iface TESTINGUI_CREATE_PERSON)

    add_library (create_group SHARED create_group.cpp)
    add_test (create_group_test tester --iface TESTINGUI_CREATE_GROUP)

    add_library (create_event SHARED create_event.cpp)
    add_test (create_event_test tester --iface TESTINGUI_CREATE_EVENT)

    add_library (set_defined_field_right SHARED set_defined_field_right.cpp)
    add_test (set_defined_field_right_test tester --iface TESTINGUI_SET_DEFINED_FIELD_RIGHT)

    add_library (set_defined_field_wrong SHARED set_defined_field_wrong.cpp)
    add_test (set_defined_field_wrong_test tester --iface TESTINGUI_SET_DEFINED_FIELD_WRONG)
    
    add_library (set_undefined_field_right SHARED set_undefined_field_right.cpp)
    add_test (set_undefined_field_right_test tester --iface TESTINGUI_SET_UNDEFINED_FIELD_RIGHT)

    add_library (set_undefined_field_wrong SHARED set_undefined_field_wrong.cpp)
    add_test (set_undefined_field_wrong_test tester --iface TESTINGUI_SET_UNDEFINED_FIELD_WRONG)
    
    add_library (set_link_field SHARED set_link_field.cpp)
    add_test (set_link_field_test tester --iface TESTINGUI_SET_LINK_FIELD)
    
    add_library (connect_person SHARED connect_person.cpp)
    add_test (connect_person_test tester --iface TESTINGUI_CONNECT_PERSON)
    
    add_library (connect_group SHARED connect_group.cpp)
    add_test (connect_group_test tester --iface TESTINGUI_CONNECT_GROUP)
    
    add_library (connect_event SHARED connect_event.cpp)
    add_test (connect_event_test tester --iface TESTINGUI_CONNECT_EVENT)
    
    add_library (disconnect_person SHARED disconnect_person.cpp)
    add_test (disconnect_person_test tester --iface TESTINGUI_DISCONNECT_PERSON)
    
    add_library (disconnect_group SHARED disconnect_group.cpp)
    add_test (disconnect_group_test tester --iface TESTINGUI_DISCONNECT_GROUP)
    
    add_library (disconnect_event SHARED disconnect_event.cpp)
    add_test (disconnect_event_test tester --iface TESTINGUI_DISCONNECT_EVENT)
    
    add_library (remove_person SHARED remove_person.cpp)
    add_test (remove_person_test tester --iface TESTINGUI_REMOVE_PERSON)

endif (WITH_TESTS_CORE)
