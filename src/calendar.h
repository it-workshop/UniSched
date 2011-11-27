#pragma once

#include <vector>
#include <string>

#include "types.h"
#include "event.h"

using std::string;
using std::vector;

/** @class Calendar
 * @brief Class keeps information about calendar.
 */
class Calendar {
private:
    id_type id_;					/**< Calendar's identificator in the database. */
    vector<Event *> events_;				/**< Calendar's events. */

public:
    Calendar(id_type id);					/**< Constructor.
    							 * @param [in] id Calendar's identificator in the database.
    							 */
    Calendar(Calendar *calendar);			/**< Constructor.
    							 * @param [in] calendar Calendar to clone.
    							 */
    ~Calendar();						/**< Destructor. */

    id_type get_id();					/**< Get Calendar's identificator.
    							 * @return Calendar's identificator in the database.
    							 */
    void set_id (id_type id);				/**< Set Calendar's identificator in the database.
    							 * @param [in] id Calendar's id.
							 */
    vector<Event*> *get_events();				/**< Get Calendar's events.
    							 * @return Calendar's events.
    							 */
    void merge_calendar(Calendar *calendar);		/**< Merge Calendars.
    							 * @param [in] calendar Calendar to merge with.
    							 */
    bool has_event(Event *event);				/**< Tests, Is Calendar has event.
    							 * @param [in] event Event to test.
    							 * @return true if calendar contains this event.
    							 */
    void add_event(Event *event);				/**< Add event to the calendar.
    							 * @param [in] event Event to add.
    							 */
    void delete_event(Event *event);			/**< Delete event from the calendar.
    							 * @param [in] event to delete.
    							 */
};

