#include <string>

#include "types.h"
#include "group.h"
#include "person.h"

using std::string;

struct Group_Content_ {
    Group *group;					/**< Group. */
    Person *person;					/**< Person. */
    string status;					/**< Person's status in this group. */
}; /**< @struct Group_Content */
