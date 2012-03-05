cmake_minimum_required (VERSION 2.8.3)

if (WITH_DUMMYUI)
    add_library (dummyui SHARED dummy.cpp)
    target_link_libraries (dummyui)
endif (WITH_DUMMYUI)
