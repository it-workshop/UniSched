#ifndef _CALENDAR_H_
#define _CALENDAR_H_

    #include <vector>

    #include <event.h>

    class Calendar {
    private:
        std::vector<Event*> events;

    public:
        Calendar(void);
        ~Calendar(void);

        void sort_Events(void);

        void add_Event(Event*);
    };

#endif /* _CALENDAR_H_ */

