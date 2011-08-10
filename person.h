#ifndef _PERSON_H_
#define _PERSON_H_

    #include <string>
    #include <vector>
    #include <time.h>

    #include <group.h>
    #include <calendar.h>
    #include <event.h>

    class Person {
    private:
        std::string id_;
        std::string name_;
        std::string surname_;
        std::vector<class Group*> groups_;
        class Calendar *events_;
        bool female_;
        time_t birthday_;

    public:
        Person(std::string, std::string, std::string, bool, time_t);
	~Person(void);

        std::string get_id(void);
        std::string get_name(void);
        std::string get_surname(void);
        bool is_female(void);
        time_t *birthday(void);

        bool in_event(class Event*);

        std::vector<Group*> *get_groups(void);
        void add_group(Group*);
        void delete_group(Group*);

        Calendar *get_calendar(void);
        void add_event(class Event*);
        void delete_event(class Event*);
    };

#endif /* _PERSON_H_ */

