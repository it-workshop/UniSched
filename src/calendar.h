#ifndef _CALENDAR_H_
#define _CALENDAR_H_

    #include <vector>
    #include <string>

    #include <event.h>

    class Calendar {
    private:
        std::string id_;
        std::vector<class Event*> events_;
        std::string name_;

    public:
        Calendar(std::string, std::string);
        ~Calendar(void);

        std::string get_id(void);
        std::string get_name(void);
        std::vector<Event*> *get_events(void);
        void merge_calendar(Calendar*);
        bool has_event(Event *);
        void add_event_nocollision(Event*);
        void add_event(Event*);
        void delete_event(Event*);
    };

#endif /* _CALENDAR_H_ */

