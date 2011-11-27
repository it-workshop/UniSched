#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

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

    #ifdef _COMMANDS_CPP_
    #define _EXTERN_
    #else /* _COMMANDS_CPP_ */
    #define _EXTERN_ extern
    #endif /* !_COMMANDS_CPP_ */
    _EXTERN_ vector<uiconsole::Command *> commands;
    #undef _EXTERN_
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

    /** @class Command_Print
     * @brief Class of ,,print (s)(id)`` command.
     */
    class Command_Print: protected Command {
    public:
        Command_Print(UserInterface *ui);	/**< Constructor.
						 * @param [in] ui pointer to UserInterface.
						 */
        void run(vector<string> args);		/**< Print object of a class (s) and with id (id).
						 * @param [in] args Vector {"print", "(s)(id)"}.
						 */
    };

    /** @class Command_Help
     * @brief Class of ,,help (command)`` command.
     */
    class Command_Help: protected Command {
    public:
        Command_Help(UserInterface *ui);	/**< Constructor.
						 * @param [in] ui pointer to UserInterface.
						 */
        void run(vector<string> args);		/**< Print all description or more detailized help about command.
						 * @param [in] args Vector {"help"(, "(command)")}.
						 */
    };

    /** @class Command_Clone
     * @brief Class of ,,clone (s)(id)`` command.
     */
    class Command_Clone: protected Command {
    public:
        Command_Clone(UserInterface *ui);	/**< Constructor.
						 * @param [in] ui pointer to UserInterface.
						 */
	void run(vector<string> args);		/**< Clone object of a class (s) and with id (id).
						 * @param [in] args Vector {"clone", "(s)(id)"}.
						 */
    };

    /** @class Command_Merge
     * @brief Class of ,,merge (s)(id) (s)(id)`` command.
     */
    class Command_Merge: protected Command {
    public:
        Command_Merge(UserInterface *ui);	/**< Constructor.
						 * @param [in] ui pointer to UserInterface.
						 */
        void run(vector<string> args);		/**< Merge two objects of class (s) with id's (id0) (id1).
						 * @param [in] args Vector {"merge", "(s)(id0)", "(s)(id1)"}.
						 */
    };

    /** @class Command_Exclude
     * @brief Class of ,,exclude (s)(id) (s)(id)`` command.
     */
    class Command_Exclude: protected Command {
    public:
        Command_Exclude(UserInterface *ui);	/**< Constructor.
						 * @param [in] ui pointer to UserInterface.
						 */
        void run(vector<string> args);		/**< Exclude group (id1) from group (id0).
						 * @param [in] args Vector {"exclude", "(s)(id0)", "(s)(id1)"}.
						 */
    };

    /** @class Command_Include
     * @brief Class of ,,include (s)(id) (s)(id)`` command.
     */
    class Command_Include: protected Command {
    public:
        Command_Include(UserInterface *ui);	/**< Constructor.
						 * @param [in] ui pointer to UserInterface.
						 */
        void run(vector<string> args);		/**< Include group (id1) and group (id0).
						 * @param [in] args Vector {"include", "(s)(id0)", "(s)(id1)"}.
						 */
    };

    /** @class Command_Add
     * @brief Class of ,,add (s)`` command.
     */
    class Command_Add: protected Command {
    public:
        Command_Add(UserInterface *ui);		/**< Constructor.
						 * @param [in] ui pointer to UserInterface.
						 */
        void run(vector<string> args);		/**< Add object of class s.
						 * @param [in] args Vector parametres.
						 */
    };

    /** @class Command_Link
     * @brief Class of ,,link (s0)(id0) (s1)(id1)`` command.
     */
    class Command_Link: protected Command {
    public:
        Command_Link(UserInterface *ui);	/**< Constructor.
						 * @param [in] ui pointer to UserInterface.
						 */
        void run(vector<string> args);		/**< Link two objects.
						 * @param [in] args Vector {"link", "(s0)(id0)", "(s1)(id1)"}.
						 */
    };

    /** @class Command_Delete
     * @brief Class of ,,delete (s)(id)`` command.
     */
    class Command_Delete: protected Command {
    public:
        Command_Delete(UserInterface *ui);	/**< Constructor.
						 * @param [in] ui pointer to UserInterface.
						 */
        void run(vector<string> args);		/**< Delete one object.
						 * @param [in] args Vector {"delete", "(s)(id)"}.
						 */
    };

    /** @class Command_Dequeue
     * @brief Class of ,,dequeue &(id0) @(id1)`` command.
     */
    class Command_Dequeue: protected Command {
    public:
        Command_Dequeue(UserInterface *ui);	/**< Constructor.
						 * @param [in] ui pointer to UserInterface.
						 */
        void run(vector<string> args);		/**< Dequeue one group from queue.
						 * @param [in] args Vector {"dequeue", "&(id0)", "&(id1)"}.
						 */
    };

    /** @class Command_Select
     * @brief Class of ,,select @(id0) @(id1) (N) &(id2)`` command.
     */
    class Command_Select: protected Command {
    public:
        Command_Select(UserInterface *ui);	/**< Constructor.
						 * @param [in] ui pointer to UserInterface.
						 */
        void run(vector<string> args);		/**< Select N people from group.
						 * @param [in] args Vector {"select", "@(id0)", "@(id1)", "(N)", "&(id2)"}.
						 */
    };

   /** * @class Command_Generate
     * @brief Class of ,,generate @(id) (begin)`` command.
     
    class Command_Generate: protected Command {
    public:
        Command_Generate(UserInterface *ui);	*< Constructor.
						 * @param [in] ui pointer to UserInterface.
						 
        void run(vector<string> args);		*< Delete one object.
						 * @param [in] args Vector {"generate", "@(id)", "(begin)"}.
						 */
    //};

    /** @class Command_Enqueue
     * @brief Class of ,,enqueue &(id0) @(id1)`` command.
     */
    class Command_Enqueue: protected Command {
    public:
        Command_Enqueue(UserInterface *ui);	/**< Constructor.
						 * @param [in] ui pointer to UserInterface.
						 */
        void run(vector<string> args);		/**< Enqueue group.
						 * @param [in] args Vector {"enqueue", "&(id0)", "@(id1)"}.
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

