#ifndef _HUMAN_H_
#define _HUMAN_H_

    #include <string>
    #include <vector>

    #include <group.h>

    class Human {
    private:
        std::string name;
	std::string surname;
        std::vector<class Group*> groups;

    public:
        Human(std::string name, std::string surname);
	~Human(void);

	std::string get_Name(void);
	std::string get_SurName(void);

        void add_Group(Group*);
    };

#endif /* _HUMAN_H_ */

