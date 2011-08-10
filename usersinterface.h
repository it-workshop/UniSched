#ifndef _USERSINTERFACE_H_
#define _USERSINTERFACE_H_

    #include <iostream>
    #include <string>
    #include <vector>
    #include <time.h>

    #include <person.h>
    #include <group.h>
    #include <event.h>
    #include <calendar.h>

    enum default_format {
        ASCII//,
        //RUS
    };

    class UsersInterface {
    private:
        enum default_format def_format;
    public:
        UsersInterface(void);
        ~UsersInterface(void);

        void set_format(enum default_format);
        enum default_format get_format(void);
        void format(time_t *);
        void format_ASCII(time_t *);
        //std::string format_RUS(time_t *);

        void print_person(Person *);
        void print_group(Group *);
        void print_event(Event *);
        void print_calendar(Calendar *);

        //Person *in_person(void);
        //Group *in_group(void);
        //Event *in_event(void);
        //Calendar *in_calendar(void);
    };

#endif /* _USERSINTERFACE_H_ */
