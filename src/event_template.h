#ifndef _EVENT_TEMPLATE_H_
#define _EVENT_TEMPLATE_H_

#include <vector>

#include <requerement.h>

using std::vector;

/** @class Event
 * @breif Class keeps templete to event.
 */
class Event_Template {
private:
    vector<Requerement> reqs_;
public:
    Event_Template(vector<Requerement> reqs);	/**< Constructor.
						 * @param [in] reqs Vector of requirements.
						 */
    ~Event_Template();				/** Destructor. */
};

#endif /* _EVENT_TEMPLATE_H_ */
