cmake_minimum_required(VERSION 2.8)

add_subdirectory (core)
add_subdirectory (modules)

add_subdirectory (tests)

add_library (module module.cpp)

add_executable (raspisator main.cpp)

target_link_libraries (raspisator module core)
if (HAVE_SQLITE)
    target_link_libraries (raspisator sqlitestorage)
endif (HAVE_SQLITE)
if (WITH_DUMMYUI)
    target_link_libraries (raspisator dummyui)
    add_test (dummyui-test raspisator --iface DummyUI)
endif (WITH_DUMMYUI)

