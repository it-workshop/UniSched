#pragma once

#include <string>
#include <vector>

#include <storableobject.h>
#include <usersobject.h>
#include <abstractgroup.h>

namespace Core {

/** @class Person
 * @brief Class keeps person unique data.
 */
class Person: public Storage::StorableObject, public UI::UsersObject {
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

    std::vector<class AbstractGroup const *> groups_;
                            /**< Person's groups. */

protected:
    void add_group(class AbstractGroup const * group)
            { groups_.push_back(group); }
                            /**< Add group to person, call in AbstractGroup::add_person()
                             * @param [in] group to add.
                             */

    void del_group(class AbstractGroup const * group);
                            /**< Delete group from person.
                             * @param [in] group.
                             */

    void save();
                            /**< Save all data into storage. Virtual in Storage::StorableObject. */
    void load();
                            /**< Load all data from starage. Viltual in Storage::StorableObject. */

public:
    Person(const int id, Storage::AbstractStorage& storage):
            StorableObject(id, storage)
            {}
                            /**< Constructor. Call at Storage::AbstractStorage::create<Person>().
                             * @param [in] id Person's identificator.
                             * @param [in] storage Data storage.
                             */

    Person(const int id, Storage::AbstractStorage& storage,
        const std::string name, const std::string surname,
        const enum Sex sex, const time_t birthday):
            StorableObject(id, storage), name_(name),
            surname_(surname), sex_(sex), birthday_(birthday)
            {}
    						/**< @deprecated Constructor.
    						 * @param [in] id Person's identificator.
                             * @param [in] storage Data storage.
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

    const std::vector<class AbstractGroup const *>& groups()
            { return groups_; }
                            /**< @deprecated Get person's groups.
                             * @return person's groups.
                             */
};

};
