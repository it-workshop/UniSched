#ifndef _USERSINTERFACE_H_
#define _USERSINTERFACE_H_

    #include <iostream>
    #include <string>
    #include <vector>
    #include <time.h>

    #include <group_content.h>
    #include <person.h>
    #include <group.h>
    #include <event.h>
    #include <calendar.h>

    using std::cout;
    using std::endl;
    using std::vector;

    enum default_format {
        ASCII//,
        //RUS
    };

    class UsersInterface {
    private:
        enum default_format def_format;
    public:
        UsersInterface();
        ~UsersInterface();

        void set_format(enum default_format);
        enum default_format get_format();
        void format(time_t *);
        void format_ASCII(time_t *);
        //std::string format_RUS(time_t *);

        void print_person(Person *);
        void print_group(Group *);
        void print_event(Event *);
        void print_calendar(Calendar *);

        //Person *in_person();
        //Group *in_group();
        //Event *in_event();
        //Calendar *in_calendar();
    };

#endif /* _USERSINTERFACE_H_ */
