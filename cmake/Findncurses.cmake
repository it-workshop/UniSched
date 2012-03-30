find_path(NCURSES_INCLUDE_DIR ncurses.h)
find_library(NCURSES_LIBRARY NAMES ncurses3)

if (NCURSES_INCLUDE_DIR AND NCURSES_LIBRARY)
    set(NCURSES_FOUND TRUE)
endif (NCURSES_INCLUDE_DIR AND NCURSES_LIBRARY)

if (NCURSES_FOUND)
    if (NOT ncurses_FIND_QUIETLY)
        message(STATUS "Found ncurses: ${NCURSES_LIBRARY}")
    endif (NOT ncurses_FIND_QUIETLY)
else (NCURSES_FOUND)
    message(FAIL_ERROR "ncurses was not found on your system, but ncurses module build requested.")
endif (NCURSES_FOUND)

