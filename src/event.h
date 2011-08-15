#ifndef _EVENT_H_
#define _EVENT_H_

#include <string>
#include <vector>
#include <time.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <types.h>
#include <group.h>
#include <person.h>
#include <calendar.h>

using std::string;
using std::vector;

/** @class Event
 * @brief Class keeps information about event.
 */
class Event {
private:
    id_type id_;						/**< Event's identificator in the database. */
    string name_;						/**< Event's name. */
    string description_;					/**< Event's description. */
    time_t begin_;						/**< Event's begin time. Number of seconds since the Epoch UNIX 1th Jan 1970, 00:00:00. */
    time_t end_;						/**< Event's end time. Number of seconds since the Epoch UNIX 1th JAN 1970, 00:00:00. */
    class Group *people_;					/**< Event's group. */
    vector<Calendar *> related_calendars_;			/**< Event's related calendars. */

public:
    Event(id_type id, string name, time_t begin, time_t end, string description);
    							/**< Constructor.
    							 * @param [in] id Event's identificator in the database.
    							 * @param [in] name Event's name.
    							 * @param [in] begin Event's begin time.
    							 * @param [in] end Event's end time.
    							 * @param [in] description Event's description.
    							 */
    ~Event();						/**< Destructor. */

    id_type get_id();					/**< Get event's identificator.
    							 * @return Event's identificator in the database.
    							 */
    void set_id (id_type id);				/**< Set event's identificator in the database.
    							 * @param [in] id Event's id.
							 */
    string get_name();					/**< Get event's name.
    							 * @return Event's name.
    							 */
    string get_description();				/**< Get event's description.
    							 * @return Event's description.
    							 */
    time_t get_begin();					/**< Get event's begin time.
    							 * @return Event's begin time.
    							 */
    time_t get_end();					/**< Get event's end time.
    							 * @return Event's end time.
    							 */
    Group *get_group();					/**< Get event's group.
    							 * @return Event's group.
    							 */
    vector<Calendar*> *get_related_calendars();		/**< Get event's related calendars.
    							 * @return Event's related calendars.
    							 */

    void add_related_calendar(Calendar *calendar);		/**< Add related calendar to event.
    							 * @param [in] calendar Calendar to add.
    							 */
    void delete_related_calendar(Calendar *calendar);	/**< Delete related calendar from event.
    							 * @param [in] calendar Calendar to delete.
    							 */
    void add_person(class Person *person, string status);	/**< Add person to the event's group.
    							 * @param [in] person Person to add.
    							 * @param [in] status Person's status in the event's group.
    							 */
    void delete_person(class Person *person);		/**< Delete person from the event's group.
    							 * @param [in] person Person to delete.
    							 */
};

#endif /* _EVENT_H_ */

