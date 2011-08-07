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
        std::string name_;
        time_t begin_;
        time_t end_;
        class Group *people_;
        std::vector<class Calendar*> used_in_;

    public:
        Event(std::string, time_t, time_t);
        ~Event(void);

        std::string get_Name(void);
        time_t *get_Begin(void);
        time_t *get_End(void);
        Group *get_Group(void);
        std::vector<Calendar*> *get_Used_in(void);

        void add_Use(Calendar*);
        void delete_Use(Calendar*);
        void add_Person(class Person*);
        void delete_Person(class Person*);
    };

#endif /* _EVENT_H_ */

