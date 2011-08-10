#ifndef _GROUP_H_
#define _GROUP_H_

    #include <string>
    #include <vector>

    #include <group_content.h>
    #include <calendar.h>
    #include <person.h>

    class Group {
    private:
        std::string id_;
        std::string name_;
        std::string description_;
        std::vector<struct Group_Content_*> people_;
        Calendar *calendar_;

    public:
        Group(std::string, std::string, std::string);
        ~Group();

        std::string get_name();
        std::string get_id();
        std::string get_description();

        Calendar *get_calendar();
        void add_event(Event*);
        void delete_event(Event*);

        std::vector<struct Group_Content_*> *get_people();
        void merge_group(Group *adding);
        void add_person_nocollision(Person*, std::string);
        void add_person(Person*, std::string);
	void delete_person(Person*);
	
    };

#endif /* _GROUP_H_ */

