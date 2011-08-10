#ifndef _PERSON_H_
#define _PERSON_H_

    #include <string>
    #include <vector>
    #include <time.h>

    #ifdef HAVE_CONFIG_H
    #include <config.h>
    #endif /* HAVE_CONFIG_H */

    #include <group_content.h>
    #include <group.h>
    #include <calendar.h>
    #include <event.h>

    class Person {
    private:
        std::string id_;
        std::string name_;
        std::string surname_;
        std::vector<struct Group_Content_*> groups_;
        class Calendar *events_;
        bool female_;
        time_t birthday_;

    public:
        Person(std::string, std::string, std::string, bool, time_t);
        ~Person();

        std::string get_id();
        std::string get_name();
        std::string get_surname();
        bool is_female();
        time_t *birthday();

        bool in_event(class Event*);

        std::vector<struct Group_Content_*> *get_groups();
        void add_group(struct Group_Content_*);
        void delete_group(class Group*);

        Calendar *get_calendar();
        void add_event(class Event*, std::string);
        void delete_event(class Event*);
    };

#endif /* _PERSON_H_ */

