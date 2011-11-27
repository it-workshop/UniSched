#ifndef _GROUP_CONTENT_H_
#define _GROUP_CONTENT_H_

    #include <string>

    #ifdef HAVE_CONFIG_H
    #include <config.h>
    #endif /* HAVE_CONFIG_H */

    #include <types.h>
    #include <group.h>
    #include <person.h>

    using std::string;

    struct Group_Content_ {
        Group *group;					/**< Group. */
        Person *person;					/**< Person. */
        string status;					/**< Person's status in this group. */
    }; /**< @struct Group_Content */

#endif /* _GROUP_CONTENT_H_ */

