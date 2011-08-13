#ifndef _PERSON_H_
#define _PERSON_H_

#include <string>
#include <vector>
#include <time.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <types.h>
#include <group_content.h>
#include <group.h>
#include <calendar.h>
#include <event.h>

/** @class Person
 * @brief Class keeps person unique data.
 */
class Person {
private:
    id_t id_;					/**< Person's identificator in the database. */
    std::string name_;				/**< Name of the person. */
    std::string surname_;			/**< Surname of the person. */
    std::vector<Group_Content *> groups_;	/**< Groups contains this person. */
    Calendar *events_;				/**< Person's calendar. */
    bool female_;				/**< Person's sex. True if female. */
    time_t birthday_;				/**< Person birthday. Time in seconds from 00:00:00, 1 Jan, 1900. */

public:
    Person(id_t id, std::string name, std::string surname, bool female, time_t birthday);
    						/**< Constructor.
    						 * @param [in] id Person's identificator.
    						 * @param [in] name Person's name.
    						 * @param [in] surname Person's surname.
    						 * @param [in] female Person's sex.
    						 * @param [in] birthday Person's birthday.
    						 */
    ~Person();					/**< Destructor. */

    id_t get_id();				/**< Get id of person in database.
    						 * @return id of person.
    						 */
    std::string get_name();				/**< Get name of person.
    						 * @return name of person.
    						 */
    std::string get_surname();			/**< Get surname of person.
    						 * @return surname of person.
    						 */
    bool is_female();				/**< Get sex of person.
    						 * @return person's sex.
    						 */
    time_t birthday();				/**< Get birthday of person.
    						 * @return person's birthday.
    						 */

    std::vector<Group_Content *> *get_groups();
    						/**< Get groups of person.
    						 * @return vector of person's groups.
    						 */
    void add_group(Group_Content * group);	/**< Add group.
    						 * @param [in] group group.
    						 */
    void delete_group(Group* group);		/**< Delete group.
    						 * @param [in] group group.
    						 */
    Calendar *get_calendar();			/**< Get calendar of person.
    						 * @return [in] calendar calendar.
    						 */
    void add_event(Event* event, std::string status);
    						/**< Add event to the person's calendar.
    						 * @param [in] event event.
    						 * @param [in] status person's status in this event.
    						 */
    void delete_event(Event* event);		/**< Delete event from the person's calendar.
    						 * @param [in] event event.
    						 */
};

#endif /* _PERSON_H_ */

