
#pragma once

#include <string>
#include <vector>
#include <time.h>
#include <stdio.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include "types.h"
#include "commands.h"
#include "queue.h"
#include "group_content.h"
#include "person.h"
#include "group.h"
#include "event.h"
#include "calendar.h"
#include "data_storage.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

/** @enum defaul_format Time format types. */
enum default_format {
    ASCII,					/**< ASCII Time format. */
    DATE					/**< Date Time format. */
};

/** @class UserInterface
 * @brief Class provides user interface.
 */
class UserInterface {
private:
    bool done;						/**< True when interactive command line mode ends */
    enum default_format def_format;			/**< Default time format. */

    storage::DataStorage *db_;				/**< Storage object. */
public:
    UserInterface();				/**< Constructor. */
    ~UserInterface();				/**< Destructor. */
    void set_db (storage::DataStorage *db);	/**< Set storage object.
    						 * @param [in] db Storage object.
						 */
    storage::DataStorage *get_db ();		/**< Get storage object.
    						 * @return Storage object.
						 */

    void listen();				/**< Interactive command line mode. */

    vector<string> get_request();		/**< Get request of user.
						 * @return Vector of words inputed bu user.
						 */

    void exit();                                /**< Exit from interactive command line mode. */

    void set_format(enum default_format format);/**< Set default time format.
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
    void format_DATE(time_t time);		/**< Print only date.
						 * @param [in] time Time to print.
						 */
    time_t get_time(string time);		/**< Get time_t from ASCII formated string.
						 * @param [in] time Formated string.
						 * @return time_t
						 */
    time_t get_birthday(string time);		/**< Get time_t from DATE formated string.
						 * @param [in] time Formated string.
						 * @return time_t
						 */
    void print_person(Person *person);		/**< Print person's information.
    						 * @param [in] person Person to print.
    						 */
    void print_group(Group *group);		/**< Print group's information.
    						 * @param [in] group Group to print.
    						 */
    void print_event(Event *event);			/**< Print event's information.
    						 * @param [in] event Event to print.
    						 */
    void print_calendar(Calendar *calendar);	/**< Print calendar's information.
    						 * @param [in] calendar Calendar to print.
    						 */
};

