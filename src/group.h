#ifndef _GROUP_H_
#define _GROUP_H_

#include <iostream>
#include <string>
#include <vector>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <types.h>
#include <group_content.h>
#include <calendar.h>
#include <person.h>

using std::string;
using std::vector;

/**< @class Group
 * @brief Class keeps information about group of people.
 */
class Group {
private:
    id_type id_;					/**< Group's identificator in the database. */
    string name_;					/**< Group's name. */
    string description_;				/**< Group's description. */
    vector<Group_Content *> people_;			/**< People in this group. */
    Calendar *calendar_;				/**< Group's calendar. */

public:
    Group(id_type id, string name, string description);
    						/**< Constructor.
    						 * @param [in] id Group's identificator in the database.
    						 * @param [in] name Group's name.
    						 * @param [in] description Group's description.
    						 */
    Group(id_type id, Group * group);		/**< Constructor.
    						 * @param [in] id Group's identificator in the database.
    						 * @param [in] group Group from which get information.
    						 */
    ~Group();					/**< Destructor. */

    string get_name();				/**< Get group's name.
    						 * @return Group's name. */
    id_type get_id();				/**< Get group's identificator.
    						 * @return Group's identificator.
    						 */
    string get_description();			/**< Get group's description.
    						 * @return Group's description.
    						 */
    Calendar *get_calendar();			/**< Get group's calendar.
    						 * @return Group's calendar.
    						 */
    void add_event(Event *event, string status);/**< Add event to the group's calendar.
    						 * @param [in] event Event to add.
						 * @param [in] status Status of link.
    						 */
    void delete_event(Event *event);		/**< Delete event from group's calendar.
    						 * @param [in] event Event to delete.
    						 */

    vector<Group_Content *> *get_people();
    						/**< Get group's people.
    						 * @return group's people.
    						 */
    void merge_group(Group *group);			/**< Merge group with this.
    						 * @param group Group to merge.
    						 */
    void exclude_group(Group *group);		/**< Exclude group from this.
    						 * @param group Group to exclude.
    						 */
    void include_group(Group *group);		/**< Select includes in group.
    						 * @param group Group to include.
    						 */
    void add_person(Person *person, string status);	
    						/**< Add person to the group.
    						 * @param person Person to add.
    						 * @param status Person's status in this group.
    						 */
    void delete_person(Person *person);		/**< Delete person from group.
    						 * @param person Person to delete.
    						 */
};

#endif /* _GROUP_H_ */

