#ifndef _EVENT_H_
#define _EVENT_H_

    #include <string>
    #include <time.h>

    #include <group.h>

    class Required_People {
    private:
        Group *group;
        unsigned short int number;
    };

    class Event {
    private:
        std::string name;
        time_t begin;
        time_t end;
        Group *people;

    public:
        Event(std::string, time_t, time_t);
        ~Event(void);

        std::string get_Name(void);
        time_t get_Begin(void);
        time_t get_End(void);

        void add_Human(Human*);
        void set_Time(time_t, time_t);
    };

#endif /* _EVENT_H_ */

