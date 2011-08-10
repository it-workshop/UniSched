#ifndef _GROUP_H_
#define _GROUP_H_

    #include <string>
    #include <vector>

    #include <calendar.h>
    #include <person.h>

    class Group {
    private:
        std::string id_;
        std::string name_;
        std::string description_;
        std::vector<class Person*> people_;
        Calendar *calendar_;

    public:
        Group(std::string, std::string, std::string);
        ~Group(void);

        std::string get_name(void);
        std::string get_id(void);
        std::string get_description(void);

        Calendar *get_calendar(void);
        void add_event(Event*);
        void delete_event(Event*);

        std::vector<Person*> *get_people(void);
        void merge_group(Group *adding);
        void add_person_nocollision(Person*);
        void add_person(Person*);
	void delete_person(Person*);
	
    };

#endif /* _GROUP_H_ */

