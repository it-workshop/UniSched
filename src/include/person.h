#pragma once

#include <string>
#include <sstream>
#include <vector>

#include <object.h>
#include <abstractgroup.h>

namespace Core {

/** @class Person
 * @brief Class keeps person unique data.
 */
class Person: public Object {
friend class AbstractGroup;
private:
    FieldString name_;
                            /**< Name of the person. */
    FieldString surname_;
                            /**< Surname of the person. */
    FieldEnum sex_;
                            /**< Person's sex. */
    FieldTime birthday_;
                            /**< Person birthday. Time in seconds from 00:00:00, 1 Jan, 1900. */
    FieldVector groups_;
                            /**< Person's groups. */

protected:
    void add_group(Object * group)
                            /**< Add group to person, call in AbstractGroup::add_person()
                             * @param [in] group to add.
                             */
    {
        groups_.add(group);
    }

    void del_group(Object * group)
                            /**< Delete group from person.
                             * @param [in] group.
                             */
    {
        groups_.del(group);
    }
                            /**< Load all data from starage. Viltual in Core::Object. */

public:
    Person(const int id, AbstractUI& ui) throw (std::bad_cast);
   
    virtual const Field& read(const std::string& name) const throw (std::bad_cast);
    virtual void update(const Field& field) throw (std::bad_cast);
};

};
