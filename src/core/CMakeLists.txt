cmake_minimum_required(VERSION 2.8)

add_library (core SHARED person.cpp abstractgroup.cpp group.cpp event.cpp
            object.cpp abstractui.cpp module.cpp abstractstorage.cpp)

target_link_libraries (core dl ${Boost_LIBRARIES})

if (WITH_YAML)
    add_library (yaml yaml.cpp)
    target_link_libraries (core yaml yaml-cpp)
endif (WITH_YAML)

