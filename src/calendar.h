#ifndef _CALENDAR_H_
#define _CALENDAR_H_

    #include <vector>
    #include <string>

    #ifdef HAVE_CONFIG_H
    #include <config.h>
    #endif /* HAVE_CONFIG_H */

    #include <event.h>

    class Calendar {
    private:
        unsigned long long int id_;
        std::vector<class Event*> events_;
        std::string name_;

    public:
        Calendar(unsigned long long int, std::string);
        Calendar(unsigned long long int, Calendar *);
        ~Calendar();

        unsigned long long int get_id();
        std::string get_name();
        std::vector<Event*> *get_events();
        void merge_calendar(Calendar*);
        bool has_event(Event *);
        void add_event_nocollision(Event*);
        void add_event(Event*);
        void delete_event(Event*);
    };

#endif /* _CALENDAR_H_ */

