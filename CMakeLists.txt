cmake_minimum_required (VERSION 2.8.3)
project (UniSched CXX)

if ("${PROJECT_BINARY_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")
    message (SEND_ERROR "Building in sources not allowed.")
endif ("${PROJECT_BINARY_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")

# UI Options
option(WITH_DUMMYUI "Build with DummyUI support." Y)
option(WITH_CLI "Build with CLI support." Y)
option(WITH_NCURSES "Build ncurses frontend." N)
option(WITH_LUAUI "Build lua frontend." Y)

# Storage Options
option(WITH_STORAGE_TEXTFILE "Build with storage features: YAML-formated plain text files as database." Y)
option(WITH_STORAGE_SQLITE "Build with storage features: SQLite database." Y)

# Unit Test Options
option(WITH_TESTS_CXX11 "Check if the compiler handles the C++11 stuff right." Y)
option(WITH_TESTS_CORE "Build with Core tests." N)
option(WITH_EXT_PYTHON_CLI "Экспериментальные питоновские биндинги к CLI. (лучше просто пройди мимо)" N)

# Algorithm Collections
option(WITH_ALG_REPEAT "Build repeat events algorithm." N)


if (WITH_TESTS_CXX11)
    include (cmake/c++11/CheckCXX11Features.cmake)
endif (WITH_TESTS_CXX11)

add_definitions (-std=c++0x)

include (CheckIncludeFileCXX)

configure_file(src/modules/paths.hpp.in ${PROJECT_SOURCE_DIR}/src/include/paths.hpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

find_package (Boost REQUIRED)

if (WITH_NCURSES)
    find_package (ncurses REQUIRED)
endif (WITH_NCURSES)

if (WITH_LUAUI)
    find_package (lua REQUIRED)
endif (WITH_LUAUI)

if (WITH_STORAGE_TEXTFILE)
    add_definitions(-DWITH_STORAGE_TEXTFILE)
    find_package (yaml-cpp REQUIRED)
endif (WITH_STORAGE_TEXTFILE)

if (WITH_STORAGE_SQLITE)
    find_package (sqlite REQUIRED)
endif (WITH_STORAGE_SQLITE)

if (WITH_TESTS_CORE)
   add_definitions(-DWITH_TESTS_CORE)
endif (WITH_TESTS_CORE)

if (WITH_EXT_PYTHON_CLI)
    add_definitions(-DWITH_EXT_PYTHON_CLI)
endif(WITH_EXT_PYTHON_CLI)


include_directories ("${Boost_INCLUDE_DIRS}")
include_directories ("${PROJECT_SOURCE_DIR}/src/include")

enable_testing()

add_subdirectory (src)

