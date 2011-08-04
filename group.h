#ifndef _GROUP_H_
#define _GROUP_H_

    #include <string>
    #include <vector>

    #include <human.h>

    class Group {
    private:
        std::string name;
        std::vector<Human*> humans;

    public:
        Group(std::string);
        ~Group(void);

        std::string get_Name(void);

        void add_Human(Human*);
    };

#endif /* _GROUP_H_ */

