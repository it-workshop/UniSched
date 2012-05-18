cmake_minimum_required (VERSION 2.8.3)
project (UniSched CXX)

if ("${PROJECT_BINARY_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")
    message (SEND_ERROR "Building in sources not allowed.")
endif ("${PROJECT_BINARY_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")

# UI Options
option(WITH_DUMMYUI "Build with DummyUI support." Y)
option(WITH_CLI "Build with CLI support." Y)
option(WITH_LUAUI "Build lua frontend." Y)

# Storage Options
option(WITH_STORAGE_TEXTFILE "Build with storage features: YAML-formated plain text files as database." N)
option(WITH_STORAGE_SQLITE "Build with storage features: SQLite database." Y)

# Unit Test Options
option(WITH_TESTS_CXX11 "Check if the compiler handles the C++11 stuff right." Y)
option(WITH_TESTS_CORE "Build with Core tests." N)
option(WITH_EXT_PYTHON_CLI "Экспериментальные питоновские биндинги к CLI. (лучше просто пройди мимо)" N)


add_definitions (-std=c++0x)
include (cmake/c++11/CheckCXX11Features.cmake)

if (NOT HAS_CXX11_AUTO OR
    NOT HAS_CXX11_NULLPTR OR
    NOT HAS_CXX11_LAMBDA OR
    NOT HAS_CXX11_RVALUE_REFERENCES)
    message(SEND_ERROR "Needed C++11 features not supported (auto, nullptr, lambda, rvalue reerences).")
endif (NOT HAS_CXX11_AUTO OR
       NOT HAS_CXX11_NULLPTR OR
       NOT HAS_CXX11_LAMBDA OR
       NOT HAS_CXX11_RVALUE_REFERENCES)

include (CheckIncludeFileCXX)
configure_file(src/modules/paths.hpp.in ${PROJECT_SOURCE_DIR}/src/include/paths.hpp)

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    add_definitions (-D_USE_WINDOWS_SPIKE_)
    set (USE_WINDOWS_SPIKE)
endif ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

include (git)
git_version("${CMAKE_SOURCE_DIR}" UniSched_VERSION)
if (UniSched_VERSION)
    option(BUILD_TARBALL "Append version info to the source directory. Clean worktree after this." N)
    if (BUILD_TARBALL)
        configure_file("${CMAKE_SOURCE_DIR}/version.h.in" "${CMAKE_SOURCE_DIR}/version.h")
        include_directories("${CMAKE_SOURCE_DIR}")
    else (BUILD_TARBALL)
        configure_file("${CMAKE_SOURCE_DIR}/version.h.in" "${CMAKE_BINARY_DIR}/version.h")
        include_directories("${CMAKE_BINARY_DIR}")
    endif (BUILD_TARBALL)
else (UniSched_VERSION)
    if (EXISTS "${CMAKE_SOURCE_DIR}/version.h")
        include_directories("${CMAKE_SOURCE_DIR}")
    else (EXISTS "${CMAKE_SOURCE_DIR}/version.h")
        message(SEND_ERROR "Neither git repository nor version.h was not found.")
    endif (EXISTS "${CMAKE_SOURCE_DIR}/version.h")
endif (UniSched_VERSION)


find_package (Boost REQUIRED)
find_package (lua REQUIRED)

if (WITH_NCURSES)
    find_package (ncurses REQUIRED)
endif (WITH_NCURSES)

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

