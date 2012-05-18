cmake_minimum_required(VERSION 2.6)

add_custom_command(OUTPUT lex.yy.c
                    COMMAND ${LEX} ${CMAKE_CURRENT_SOURCE_DIR}/yaml.l
                    DEPENDS yaml.l)
add_custom_command(OUTPUT yaml.tab.c yaml.tab.h
                    COMMAND ${YACC} -d ${CMAKE_CURRENT_SOURCE_DIR}/yaml.y
                    DEPENDS yaml.y)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_library(filestorage SHARED filestorage.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/yaml.tab.c ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)

target_link_libraries(filestorage core ${LEX_LIBRARY})

