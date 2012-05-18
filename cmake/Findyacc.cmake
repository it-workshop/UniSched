cmake_minimum_required(VERSION 2.6)

find_program(YACC bison yacc)

if(YACC)
    message (STATUS "yacc: ${YACC}")
    set(HAVE_YACC ON)
else(YACC)
    message (STATUS "yacc: no")
    set(HAVE_YACC OFF)
endif(YACC)

