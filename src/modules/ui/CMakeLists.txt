cmake_minimum_required (VERSION 2.8.3)

if (WITH_DUMMYUI)
    add_library (dummyui SHARED dummy.cpp)
#    target_link_libraries (dummyui)
endif (WITH_DUMMYUI)

if (WITH_CLI)
    find_package (Readline REQUIRED)

    if (READLINE_FOUND)
        add_library (cli SHARED cli.cpp)
        target_link_libraries (cli core readline ${Boost_LIBRARIES})
    else (READLINE_FOUND)
        message (FAIL_ERROR " readline not found, but cli build requested.")
    endif (READLINE_FOUND)

endif (WITH_CLI)

if (WITH_GTK)
    SET(module_name gtkui)
    SET(interface_files gtkui.i)
    SET(src_files gtkui.cpp gtkui.hpp SReadline.h)

    FIND_PACKAGE(SWIG REQUIRED)
    INCLUDE(${SWIG_USE_FILE})

    FIND_PACKAGE(PythonLibs)
    INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

    SET(CMAKE_SWIG_FLAGS "")

    SET_SOURCE_FILES_PROPERTIES(cli.i PROPERTIES CPLUSPLUS ON)
    SET_SOURCE_FILES_PROPERTIES(cli.i PROPERTIES SWIG_FLAGS "-includeall")
    SWIG_ADD_MODULE(${module_name} python ${interface_files} ${src_files})
    SWIG_LINK_LIBRARIES(cli ${PYTHON_LIBRARIES})
ENDIF(WITH_GTK)
