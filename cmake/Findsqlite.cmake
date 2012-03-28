find_path(SQLITE_INCLUDE_DIR sqlite3.h)
find_library(SQLITE_LIBRARY NAMES sqlite3)

if (SQLITE_INCLUDE_DIR AND SQLITE_LIBRARY)
    set(SQLITE_FOUND TRUE)
endif (SQLITE_INCLUDE_DIR AND SQLITE_LIBRARY)

if (SQLITE_FOUND)
    if (NOT sqlite_FIND_QUIETLY)
        message(STATUS "Found sqlite3: ${SQLITE_LIBRARY}")
    endif (NOT sqlite_FIND_QUIETLY)
else (SQLITE_FOUND)
    message(FAIL_ERROR "sqlite3.h not found on your system, but sqlite module build requested.")
endif (SQLITE_FOUND)

