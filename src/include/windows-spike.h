/** @file
 * @brief Windows implementation of POSIX functions that we are use.
 * @author Aleksander Derbenev
 * @date 2012
 */
#pragma once

int setenv(const char *name, const char *value, int override);
                    /**< Set environment variable.
                     * @param [in] name Name of variable.
                     * @param [in] value New value of variable.
                     * @param [in] override Must be nonzero to override value.
                     * @return zero on success or -1 on error.
                     */

/** @define RTLD_NOW
 * resolve all undefined symbols before dlopen returns.
 * Not realy used, saved for capatible definition.
 */
#define RTLD_NOW 0

void *dlopen(const char *filename, int flag);
                    /**< Open shared object.
                     * @param [in] Name of the file.
                     * @param [in] flag Realy ignored.
                     * @return Handle of the shared object.
                     */

char *dlerror();
                    /**< Get error description
                     * @return Human readable string describing most recent
                     * error that occurred from dlopen(), dlsym() or dlclose().
                     */

void *dlsym(void *handle, const char *symbol);
                    /**< Get address of function in the shared object.
                     * @param [in] handle Handle of shared object.
                     * @param [in] symbol Name of the function.
                     * @return Address of function.
                     */

int dlclose(void *handle);
                    /**< Close shared object.
                     * @param [in] handle Handle of the shared object.
                     * @return 0 on success, and nonzero on error.
                     */

