#ifndef _GROUP_CONTENT_H_
#define _GROUP_CONTENT_H_

    #include <string>

    #ifdef HAVE_CONFIG_H
    #include <config.h>
    #endif /* HAVE_CONFIG_H */

    #include <group.h>
    #include <person.h>

    using std::string;

    /** @typedef @struct Group_Content_ Links between people and groups. */
    typedef struct Group_Content_ {
        class Group *group;				/**< Group. */
        class Person *person;				/**< Person. */
        string status;					/**< Person's status in this group. */
    } Group_Content; /**< @struct Group_Content */

#endif /* _GROUP_CONTENT_H_ */

