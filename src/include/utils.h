/**< @file
 * @brief Utilities functions definitions..
 * @author Igor Mosyagin
 * @author Arshavir Ter-Gabrielyan
 * @author Aleksander Derbenev
 * @date 2012
 */

#include <iostream>

#include <abstractui.h>
#include <abstractstorage.h>
#include <module.h>

/** @namespace utils
 * Auxiliary functions.
 */
namespace utils {

bool
select_modules (Core::AbstractUI **ui, Core::AbstractStorage **storage,
               Core::Config& conf, std::vector<std::string>& args);
                        /**< select modules objects using configuration
                         * and command line arguments.
                         * @param [out] ui Ui module instance.
                         * @param [out] storage Storage module instance.
                         * @param [in] conf Configuration.
                         * @param [in] args Command line arguments.
                         * @return True if modules are found.
                         */

}

