#ifndef _CALENDAR_H_
#define _CALENDAR_H_

    #include <vector>
    #include <string>

    #ifdef HAVE_CONFIG_H
    #include <config.h>
    #endif /* HAVE_CONFIG_H */

    #include <event.h>

    using std::string;
    using std::vector;

    /** @class Calendar
     * @brief Class keeps information about calendar.
     */
    class Calendar {
    private:
        unsigned long long int id_;				/**< Calendar's identificator in the database. */
        vector<class Event*> events_;				/**< Calendar's events. */

    public:
        Calendar(unsigned long long int id);			/**< Constructor.
								 * @param [in] id Calendar's identificator in the database.
								 */
        Calendar(unsigned long long int id, Calendar *calendar);/**< Constructor.
								 * @param [in] id Calendar's identificator in the database.
								 * @param [in] calendar Calendar to clone.
								 */
        ~Calendar();						/**< Destructor. */

        unsigned long long int get_id();			/**< Get Calendar's identificator.
								 * @return Calendar's identificator in the database.
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

#endif /* _CALENDAR_H_ */

