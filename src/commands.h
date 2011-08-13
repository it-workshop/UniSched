#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include <string>
#include <vector>
#include <iostream>

#include <types.h>
#include <userinterface.h>

using std::string;
using std::cin;
using std::cout;
using std::vector;
using std::endl;

/** @namespace uiconsole Namespace of console user interface. */
namespace uiconsole {

    /** @class Command
     * @brief Abstract class of console command.
     */
    class Command {
    protected:
        UserInterface *ui;			/**< Pointer to user interface object. */
        string name;				/**< Name of command. */
        string description;			/**< Description of command. */
        string help;				/**< Help to the command. */
    public:
        Command(UserInterface *ui);		/**< Constructor.
						 * @param [in] ui pointer to UserInterface.
						 */
        ~Command();				/**< Destructor. */

        string get_name();			/**< Get name of command.
						 * @return name of command.
						 */
        string get_description();		/**< Get description of command.
						 * @return description of command.
						 */
        string get_help();			/**< Get help of command.
						 * @return help of command.
						 */
        virtual void run(vector<string> args) = 0;
						/**< Virtual method called at the execution of command
						 * @param [in] args Vector of strings used in function
						 */
    };

    /** @class Command_Exit
     * @brief Class of ,,exit`` command.
     */
    class Command_Exit: protected Command {
    public:
        Command_Exit(UserInterface *ui);	/**< Constructor.
						 * @param [in] ui pointer to UserInterface.
						 */
        void run(vector<string> args);		/**< Exit from programm.
						 * @param [in] args Vector {"exit"}.
						 */
    };

    /** @class Command_All
     * @brief Class of ,,all (s)`` command.
     */
    class Command_All: protected Command {
    public:
        Command_All(UserInterface *ui);		/**< Constructor.
						 * @param [in] ui pointer to UserInterface.
						 */
        void run(vector<string> args);		/**< Print all objects of a class (s).
						 * @param [in] args Vector {"all", "(s)"}.
						 */
    };

    /** @class Command_Help
     * @brief Class of ,,help`` command.
     */
    class Command_Help: protected Command {
    public:
        Command_Help(UserInterface *ui);	/**< Constructor.
						 * @param [in] ui pointer to UserInterface.
						 */
        void run(vector<string> args);		/**< Print all help strings.
						 * @param [in] args Vector {"help"(, "(command)")}.
						 */
    };

    void execute(vector<string> args);		/**< Executes user request.
						 * @param [in] args User request.
						 */
    void initiate(UserInterface *ui);		/**< Initiates all commands.
						 * @param [in] ui Pointer to UserInterface.
						 */

}

#endif /* _COMMANDS_H_ */

