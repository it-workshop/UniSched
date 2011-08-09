#ifndef _CALENDAR_H_
#define _CALENDAR_H_

    #include <vector>
    #include <string>

    #include <event.h>

    class Calendar {
    private:
        std::string ID_;
        std::vector<class Event*> events_;
        std::string name_;

    public:
        Calendar(std::string, std::string);
        ~Calendar(void);

        std::string get_ID(void);
        std::string get_Name(void);
        std::vector<Event*> *get_Events(void);
        //void merge_calendar(Calendar*);
        void add_Event(Event*);
        void delete_Event(Event*);
    };

#endif /* _CALENDAR_H_ */

