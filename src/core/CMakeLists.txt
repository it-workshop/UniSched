cmake_minimum_required(VERSION 2.8)

add_library (core SHARED person.cpp abstractgroup.cpp group.cpp event.cpp
            object.cpp abstractui.cpp module.cpp abstractstorage.cpp utils.cpp
            algorithm.cpp)

target_link_libraries (core dl ${Boost_LIBRARIES} lua)
