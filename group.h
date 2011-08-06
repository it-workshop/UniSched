#ifndef _GROUP_H_
#define _GROUP_H_

    #include <string>
    #include <vector>

    #include <person.h>

    class Group {
    private:
        std::string name_;
        std::vector<class Person*> people_;

    public:
        Group(std::string);
        ~Group(void);

        std::string get_Name(void);

        std::vector<Person*> *get_People(void);
        void add_Person(Person*);
	void delete_Person(Person*);
	
    };

#endif /* _GROUP_H_ */

