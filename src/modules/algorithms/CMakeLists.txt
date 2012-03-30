cmake_minimum_required(VERSION 2.8)

if (WITH_ALG_REPEAT)
    add_library (repeat SHARED repeat.cpp)
    target_link_libraries (repeat core)
endif (WITH_ALG_REPEAT)
