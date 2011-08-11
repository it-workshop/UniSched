#ifndef _EVENT_H_
#define _EVENT_H_

    #include <string>
    #include <vector>
    #include <time.h>

    #ifdef HAVE_CONFIG_H
    #include <config.h>
    #endif /* HAVE_CONFIG_H */

    #include <group.h>
    #include <person.h>
    #include <calendar.h>

    class Event {
    private:
        unsigned long long int id_;
        std::string name_;
        std::string description_;
        time_t begin_;
        time_t end_;
        class Group *people_;
        std::vector<class Calendar*> used_in_;

    public:
        Event(unsigned long long int, std::string, time_t, time_t, std::string);
        ~Event();

        unsigned long long int get_id();
        std::string get_name();
        std::string get_description();
        time_t *get_begin();
        time_t *get_end();
        Group *get_group();
        std::vector<Calendar*> *get_used_in();

        void add_use(Calendar*);
        void delete_use(Calendar*);
        void add_person(class Person*, std::string);
        void delete_person(class Person*);
    };

#endif /* _EVENT_H_ */

