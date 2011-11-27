#ifndef _EVENT_TEMPLATE_H_
#define _EVENT_TEMPLATE_H_

#include <vector>
#include <string>

#include <types.h>
#include <commands.h>
#include <group.h>

using std::vector;
using std::string;

/** @class Event_Template
 * @breif a template for events.
 *
 * This class provides methods for creating new events of people related to script.
 */
class Event_Template {
private:
    id_type id_;				/**< Id of this object. */
    string name_;				/**< Name of this object. */
    string script_;				/**< Script to return group of requered people */
    time_t duration_;				/**< Duration of event */

public:
    Event_Template(id_type id, string name, string script, time_t duration);
						/**< Constructor.
						 * @param [in] id ID.
						 * @param [in] name Name.
						 * @param [in] script Script.
						 * @param [in] duration Duration.
						 */
    ~Event_Template();				/** Destructor. */

    id_type get_id();				/**< Get id of event template.
						 * @return ID of an event template.
						 */
    void set_id(id_type id);			/**< Set id of event template.
						 * @param [in] id New id.
						 */
    string get_name();				/**< Set name of this object
						 * @return Name of this object.
						 */
    string get_script();			/**< Get script of the event template.
						 * @return script printed in string
						 */
    void get_requered_people();			/**< The set of requered people. */
};

#endif /* _EVENT_TEMPLATE_H_ */

