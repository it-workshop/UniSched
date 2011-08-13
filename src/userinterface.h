#ifndef _USERSINTERFACE_H_
#define _USERSINTERFACE_H_

#include <string>
#include <vector>
#include <time.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <types.h>
#include <commands.h>
#include <group_content.h>
#include <person.h>
#include <group.h>
#include <event.h>
#include <calendar.h>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

/** @enum defaul_format Time format types. */
enum default_format {
    ASCII						/**< ASCII Time format. */
};

/** @class UserInterface
 * @brief Class provides user interface.
 */
class UserInterface {
private:
    bool done;						/**< True when interactive command line mode ends */
    enum default_format def_format;			/**< Default time format. */
public:
    vector<Person *> *people;				/**< Pointer to vector of people */
    vector<Group *> *groups;				/**< Pointer to vector of groups */
    vector<Event *> *events;				/**< Pointer to vector of events */
    vector<Calendar *> *calendars;			/**< Pointer to vector og calendars */
    UserInterface(vector<Person *> *people, vector<Group *> *groups, vector<Event *> *events, vector<Calendar *> *calendars);
						/**< Constructor
    						 * @param [in] people All people objects in the programm.
    						 * @param [in] groups All groups objects.
    						 * @param [in] events All events objects.
    						 * @param [in] calendars All calendars objects.
 						*/
    ~UserInterface();				/**< Destructor */

    void listen();				/**< Interactive command line mode. */

    void exit();                                /**< Exit from interactive command line mode. */

    void set_format(enum default_format format);	/**< Set default time format.
    						 * @param [in] format Type of time format.
    						 */
    enum default_format get_format();		/**< Get default time format.
    						 * @return Default type of time format.
    						 */
    void format(time_t time);			/**< Print time in default format.
    						 * @param [in] time Time to print.
    						 */
    void format_ASCII(time_t time);		/**< Print time in ASCII time format.
    						 * @param [in] time Time to print.
    						 */

    void print_person(Person *person);		/**< Print person's information.
    						 * @param [in] person Person to print.
    						 */
    void print_group(Group *group);			/**< Print group's information.
    						 * @param [in] group Group to print.
    						 */
    void print_event(Event *event);			/**< Print event's information.
    						 * @param [in] event Event to print.
    						 */
    void print_calendar(Calendar *calendar);	/**< Print calendar's information.
    						 * @param [in] calendar Calendar to print.
    						 */
};

#endif /* _USERSINTERFACE_H_ */

