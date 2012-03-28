cmake_minimum_required (VERSION 2.8.3)

if (WITH_YAML)
    add_library (filestorage SHARED filestorage.cpp)
    target_link_libraries (filestorage yaml-cpp)
endif (WITH_YAML)

if (WITH_SQLITE)
    add_library (sqlitestorage SHARED sqlite.cpp)
    target_link_libraries (sqlitestorage sqlite3)
endif (WITH_SQLITE)

