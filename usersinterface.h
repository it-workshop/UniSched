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

        void out_Person(Person *);
        void out_Group(Group *);
        void out_Event(Event *);
        void out_Calendar(Calendar *);

        //Person *in_Person(void);
        //Group *in_Group(void);
        //Event *in_Event(void);
        //Calendar *in_Calendar(void);
    };

#endif /* _USERSINTERFACE_H_ */
