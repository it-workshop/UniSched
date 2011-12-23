cmake_minimum_required (VERSION 2.8.3)

add_library (sqlitestorage sqlite.cpp)
target_link_libraries (sqlitestorage sqlite3)

