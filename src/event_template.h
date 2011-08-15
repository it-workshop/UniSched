#ifndef _EVENT_TEMPLATE_H_
#define _EVENT_TEMPLATE_H_

#include <vector>
#include <string>

#include <types.h>
#include <group.h>

using std::vector;
using std::string;

/** @class Event
 * @breif Class keeps template to event.
 */
class Event_Template {
private:
    vector<Group *> already_used_;		/**< Vector of pointers to groups of erlier used people */
    string script_;				/**< Script to return group of requered people */
    time_t duration_;				/**< Duration of event */

public:
    Event_Template(string script, time_t duration);
						/**< Constructor.
						 * @param [in] script Script.
						 * @param [in] duration Duration.
						 */
    ~Event_Template();				/** Destructor. */

    Group *get_requered_people();		/**< The set of requered people.
						 * @return group of requered people.
						 */
    Event *get_new_event(time_t begin);		/**< New event of a event template.
						 * @param [in] begin Begin of new event.
						 * @return new event.
						 */
};

#endif /* _EVENT_TEMPLATE_H_ */
