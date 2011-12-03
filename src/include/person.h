#pragma once

#include <string>
#include <vector>

#include <storage.h>
#include <abstractgroup.h>

namespace Core {

/** @class Person
 * @brief Class keeps person unique data.
 */
class Person: public Storage::StorableObject {
friend class AbstractGroup;
public:
    /** @enum Sex enum of sex */
    enum Sex {
        MALE,
        FEMALE
    };

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

    std::vector<class AbstractGroup const *>::iterator groups_iterator_;

protected:
    void add_group(class AbstractGroup const * group) { groups_.push_back(group); }
    void del_group(class AbstractGroup const * group);

    virtual void save();
    virtual void load();

public:
   Person(const int id, Storage::AbstractStorage& storage,
        const std::string name, const std::string surname,
        const enum Sex sex, const time_t birthday):
            StorableObject(id, storage), name_(name),
            surname_(surname), sex_(sex), birthday_(birthday) {}
    						/**< Constructor.
    						 * @param [in] id Person's identificator.
    						 * @param [in] name Person's name.
    						 * @param [in] surname Person's surname.
    						 * @param [in] sex Person's sex.
    						 * @param [in] birthday Person's birthday.
    						 */

    const std::string name() const { return name_; }
                            /**< Get name of person.
    						 * @return name of person.
    						 */
    const std::string surname() const { return surname_; }
                            /**< Get surname of person.
    						 * @return surname of person.
    						 */
    const enum Sex sex() const { return sex_; }
                            /**< Get sex of person.
    						 * @return person's sex.
    						 */
    const time_t birthday() const { return birthday_; }
                            /**< Get birthday of person.
    						 * @return person's birthday.
    						 */

    class AbstractGroup const * first_group() { groups_iterator_ = groups_.begin(); return *groups_iterator_++; }
    class AbstractGroup const * next_group() { return *groups_iterator_++; }
    const bool has_next_group() { return groups_iterator_ != groups_.end(); }
};

};
