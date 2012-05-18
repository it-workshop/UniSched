cmake_minimum_required(VERSION 2.6)

find_library(LEX_LIBRARY NAMES l fl)
find_program(LEX lex flex)

if (LEX AND LEX_LIBRARY)
    message(STATUS "lex: ${LEX}")
    set(HAVE_LEX ON)
else (LEX AND LEX_LIBRARY)
    message(STATUS "lex: no.")
    set(HAVE_LEX OFF)
endif (LEX AND LEX_LIBRARY)

