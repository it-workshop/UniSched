
#pragma once

#include <string>
#include <vector>
#include <time.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include "types.h"
#include "group_content.h"
#include "group.h"
#include "calendar.h"
#include "event.h"

/** @class Person
 * @brief Class keeps person unique data.
 */
class Person {
public:
    /** @enum Sex enum of sex */
    enum Sex {
        MALE,
        FEMALE
    };

    Person(id_type id, std::string name, std::string surname, enum Sex sex, time_t birthday);
    						/**< Constructor.
    						 * @param [in] id Person's identificator.
    						 * @param [in] name Person's name.
    						 * @param [in] surname Person's surname.
    						 * @param [in] sex Person's sex.
    						 * @param [in] birthday Person's birthday.
    						 */
    ~Person();					/**< Destructor. */


    id_type get_id();				/**< Get id of person in database.
    						 * @return id of person.
    						 */
    void set_id (id_type id);			/**< Set id of person in database.
    						 * @param [in] id Person's id.
						 */
    std::string get_name();				/**< Get name of person.
    						 * @return name of person.
    						 */
    std::string get_surname();			/**< Get surname of person.
    						 * @return surname of person.
    						 */
    enum Sex sex();				/**< Get sex of person.
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
private:
    id_type id_;				/**< Person's identificator in the database. */
    std::string name_;				/**< Name of the person. */
    std::string surname_;			/**< Surname of the person. */
    std::vector<Group_Content *> groups_;	/**< Groups contains this person. */
    enum Sex sex_;				/**< Person's sex. */
    time_t birthday_;				/**< Person birthday. Time in seconds from 00:00:00, 1 Jan, 1900. */

};

