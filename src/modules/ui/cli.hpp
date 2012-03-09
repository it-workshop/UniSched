#include <iostream>
#include <malloc.h>
#include <vector>
#include <string>

#include <boost/format.hpp>

#include <abstractui.h>
#include <person.h>
#include <group.h>

#include "SReadline.h"


class CommandLineInterface;
typedef int (CommandLineInterface::*CLIMemCommand)(const std::vector<std::string> &);

class CommandLineInterface: public Core::AbstractUI {

private:
    std::map<std::string, CLIMemCommand> Commands;
    bool done;
    bool debug;
    swift::SReadline Reader;
    std::vector<std::string> Completions;

public:
    void init (const std::vector< std::string > &args);
    int run();
    CommandLineInterface(std::vector<Module *> *modules, void *handle);

    int usage(const std::vector<std::string>& unused);
    int quit(const std::vector<std::string>& unused);
    int clear(const std::vector<std::string>& unused);
    int history(const std::vector<std::string>& unused);
    int toggle_debug(const std::vector<std::string>& unused);

    int new_person(const std::vector<std::string>& tokens);
    int new_group(const std::vector<std::string>& tokens);
};

