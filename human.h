#ifndef _HUMAN_H_
#define _HUMAN_H_

    #include <string>
    #include <vector>

    #include <group.h>
    #include <active_time.h>

    class Human {
    private:
        std::string name;
	std::string surname;
	std::vector<Active_Time> active;
        std::vector<class Group*> groups;

    public:
        Human(std::string, std::string, Active_Time);
	~Human(void);

	std::string get_Name(void);
	std::string get_SurName(void);

        void add_Group(Group*);
	void add_Active(Active_Time);
	bool is_Active(unsigned short int);
    };

#endif /* _HUMAN_H_ */

