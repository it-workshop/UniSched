cmake_minimum_required (VERSION 2.8.3)

if (WITH_STORAGE_SQLITE)
    add_library (sqlitestorage SHARED sqlite.cpp)
    target_link_libraries (sqlitestorage sqlite3)
endif (WITH_STORAGE_SQLITE)

