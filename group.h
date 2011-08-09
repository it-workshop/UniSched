#ifndef _GROUP_H_
#define _GROUP_H_

    #include <string>
    #include <vector>

    #include <calendar.h>
    #include <person.h>

    class Group {
    private:
        std::string ID_;
        std::string name_;
        std::string description_;
        std::vector<class Person*> people_;
        Calendar *calendar_;

    public:
        Group(std::string, std::string, std::string);
        ~Group(void);

        bool real(void);
        std::string get_Name(void);
        std::string get_ID(void);
        std::string get_Description(void);

        Calendar *get_Calendar(void);
        void add_Event(Event*);
        void delete_Event(Event*);

        std::vector<Person*> *get_People(void);
        void add_Person(Person*);
	void delete_Person(Person*);
	
    };

#endif /* _GROUP_H_ */

