#ifndef _CALENDAR_H_
#define _CALENDAR_H_

    #include <vector>

    #include <event.h>

    class Calendar {
    private:
        std::vector<class Event*> events_;

    public:
        Calendar(void);
        ~Calendar(void);

        std::vector<Event*> *get_Events(void);
        void add_Event(Event*);
        void delete_Event(Event*);
    };

#endif /* _CALENDAR_H_ */

