cmake_minimum_required(VERSION "2.6")

## Retrive version information from git repository.
function(git_version dir version_var)
    if (EXISTS "${dir}/.git")
        execute_process (COMMAND git describe --tags --abbrev=0
                        OUTPUT_VARIABLE GIT_TAG
                        WORKING_DIRECTORY "${dir}")
        string(REGEX REPLACE "\n" "" GIT_TAG "${GIT_TAG}")
        set(GIT_TAG "${GIT_TAG}" PARENT_SCOPE)
        execute_process (COMMAND git log "${GIT_TAG}" -1 --pretty=format:%H
                        OUTPUT_VARIABLE GIT_TAG_COMMIT
                        WORKING_DIRECTORY "${dir}")
        set(GIT_TAG_COMMIT "${GIT_TAG_COMMIT}" PARENT_SCOPE)
        execute_process (COMMAND git log -1 --pretty=format:%H
                        OUTPUT_VARIABLE GIT_COMMIT
                        WORKING_DIRECTORY "${dir}")
        set(GIT_COMMIT "${GIT_COMMIT}" PARENT_SCOPE)
        string(REGEX REPLACE "-.+" "" GIT_VERSION "${GIT_TAG}")
        set(GIT_VERSION "${GIT_VERSION}" PARENT_SCOPE)
        string(REGEX REPLACE ".+-" "" GIT_NAME "${GIT_TAG}")
        set(GIT_NAME "${GIT_NAME}" PARENT_SCOPE)
        execute_process (COMMAND git describe
                        OUTPUT_VARIABLE GIT_DESCRIBE
                        WORKING_DIRECTORY "${dir}")
        string(REGEX REPLACE "\n" "" GIT_DESCRIBE "${GIT_DESCRIBE}")
        set(GIT_DESCRIBE "${GIT_DESCRIBE}" PARENT_SCOPE)
        if ("${GIT_TAG_COMMIT}" STREQUAL "${GIT_COMMIT}")
            set(${version_var} "${GIT_TAG}" PARENT_SCOPE)
        else ("${GIT_TAG_COMMIT}" STREQUAL "${GIT_COMMIT}")
            set(${version_var} "${GIT_TAG}-${GIT_COMMIT}" PARENT_SCOPE)
        endif ("${GIT_TAG_COMMIT}" STREQUAL "${GIT_COMMIT}")
    endif (EXISTS "${dir}/.git")
endfunction(git_version)

