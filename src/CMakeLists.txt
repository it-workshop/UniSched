cmake_minimum_required(VERSION 2.8)

#add_subdirectory (storage)
add_subdirectory (ui)
add_subdirectory (core)
add_subdirectory (backends)

add_subdirectory (tests)

add_library (backend SHARED backend.cpp)

add_executable (raspisator main.cpp)

target_link_libraries (raspisator backend core ui)
if (HAVE_SQLITE)
    target_link_libraries (raspisator sqlitestorage)
endif (HAVE_SQLITE)

