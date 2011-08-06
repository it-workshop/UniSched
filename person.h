#ifndef _PERSON_H_
#define _PERSON_H_

    #include <string>
    #include <vector>

    #include <group.h>
    #include <calendar.h>
    #include <event.h>

    class Person {
    private:
        std::string name_;
	std::string surname_;
        std::vector<class Group*> groups_;
        class Calendar *events_;

    public:
        Person(std::string, std::string);
	~Person(void);

	std::string get_Name(void);
	std::string get_Surname(void);

        std::vector<Group*> *get_Groups(void);
        void add_Group(Group*);
        void delete_Group(Group*);

        Calendar *get_Calendar(void);
        void add_Event(class Event*);
        void delete_Event(class Event*);
    };

#endif /* _PERSON_H_ */

