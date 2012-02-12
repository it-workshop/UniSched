#pragma once

#include <string>
#include <sstream>
#include <vector>

#include <managersobject.h>
#include <usersobject.h>
#include <abstractgroup.h>

namespace Core {

/** @class Person
 * @brief Class keeps person unique data.
 */
class Person: public ManagersObject, public UI::UsersObject {
friend class AbstractGroup;
public:
    /** @enum Sex enum of sex */
    enum Sex {
        MALE,
        FEMALE
    };

    static const Sex _(const std::string str)
        { return (str == "MALE") ? MALE : FEMALE; }
                            /**< Small function to easy type casting.
                             * @param [in] str String to cast.
                             * @return MALE if string equals to "MALE" else FEMALE.
                             */

    static const std::string _(const Sex sex)
        { return (sex == MALE) ? "MALE" : "FEMALE"; }
                            /**< Small function to easy type casting.
                             * @param [in] sex enum to cast.
                             * @return "MALE" if enum equals to MALE else FEMALE.
                             */

private:
    std::string name_;
                            /**< Name of the person. */
    std::string surname_;
                            /**< Surname of the person. */
    enum Sex sex_;
                            /**< Person's sex. */
    time_t birthday_;
                            /**< Person birthday. Time in seconds from 00:00:00, 1 Jan, 1900. */

    std::vector<class AbstractGroup *> groups_;
                            /**< Person's groups. */

protected:
    void add_group(class AbstractGroup * group)
            { groups_.push_back(group); }
                            /**< Add group to person, call in AbstractGroup::add_person()
                             * @param [in] group to add.
                             */

    void del_group(class AbstractGroup const * group);
                            /**< Delete group from person.
                             * @param [in] group.
                             */

    void save();
                            /**< Save all data into manager. Virtual in Core::ManagersObject. */
    void load();
                            /**< Load all data from starage. Viltual in Core::ManagersObject. */

public:
    Person(const int id, Manager& manager):
            ManagersObject(id, manager)
            {}
                            /**< Constructor. Call at Core::Manager::create<Person>().
                             * @param [in] id Person's identificator.
                             * @param [in] manager Data manager.
                             */

    Person(const int id, Manager& manager,
        const std::string name, const std::string surname,
        const enum Sex sex, const time_t birthday):
            ManagersObject(id, manager), name_(name),
            surname_(surname), sex_(sex), birthday_(birthday)
            {}
    						/**< @deprecated Constructor.
    						 * @param [in] id Person's identificator.
                             * @param [in] manager Data manager.
    						 * @param [in] name Person's name.
    						 * @param [in] surname Person's surname.
    						 * @param [in] sex Person's sex.
    						 * @param [in] birthday Person's birthday.
    						 */

    const std::string name() const { return name_; }
                            /**< @deprecated Get name of person.
    						 * @return name of person.
    						 */

    const std::string surname() const { return surname_; }
                            /**< @deprecated Get surname of person.
    						 * @return surname of person.
    						 */

    const enum Sex sex() const { return sex_; }
                            /**< @deprecated Get sex of person.
    						 * @return person's sex.
    						 */

    const time_t birthday() const { return birthday_; }
                            /**< @deprecated Get birthday of person.
    						 * @return person's birthday.
    						 */

    const std::vector<class AbstractGroup *>& groups()
            { return groups_; }
                            /**< @deprecated Get person's groups.
                             * @return person's groups.
                             */
    
    virtual const std::string read() const;

    virtual const int read_int(const std::string name) const throw (std::bad_cast);
    virtual const std::string read_string(const std::string name) const throw (std::bad_cast);
    virtual const time_t read_time(const std::string name) const throw (std::bad_cast);
    virtual const std::string read_enum(const std::string name) const throw (std::bad_cast);
    virtual const std::vector<UI::UsersObject *> read_vector(const std::string name) const throw(std::bad_cast);

    virtual void update(const std::string name, const int value) throw (std::bad_cast);
    virtual void update(const std::string name, const std::string value) throw (std::bad_cast);
    virtual void update(const std::string name, const time_t value) throw (std::bad_cast);
    virtual void update_enum(const std::string, const std::string value) throw (std::bad_cast);
    virtual void update(UsersObject *, bool linked) throw (std::bad_cast);
};

};
