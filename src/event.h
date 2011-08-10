#ifndef _EVENT_H_
#define _EVENT_H_

    #include <string>
    #include <vector>
    #include <time.h>

    #include <group.h>
    #include <person.h>
    #include <calendar.h>

    class Event {
    private:
        std::string id_;
        std::string name_;
        std::string description_;
        time_t begin_;
        time_t end_;
        class Group *people_;
        std::vector<class Calendar*> used_in_;

    public:
        Event(std::string, std::string, time_t, time_t, std::string);
        ~Event(void);

        std::string get_id(void);
        std::string get_name(void);
        std::string get_description(void);
        time_t *get_begin(void);
        time_t *get_end(void);
        Group *get_group(void);
        std::vector<Calendar*> *get_used_in(void);

        void add_use(Calendar*);
        void delete_use(Calendar*);
        void add_person(class Person*);
        void delete_person(class Person*);
    };

#endif /* _EVENT_H_ */

