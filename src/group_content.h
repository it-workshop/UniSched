#ifndef _GROUP_CONTENT_H_
#define _GROUP_CONTENT_H_

    #include <string>

    #ifdef HAVE_CONFIG_H
    #include <config.h>
    #endif /* HAVE_CONFIG_H */

    #include <group.h>
    #include <person.h>

    typedef struct Group_Content_ {
        class Group *group;
        class Person *person;
        std::string status;
    } Group_Content;

#endif /* _GROUP_CONTENT_H_ */

