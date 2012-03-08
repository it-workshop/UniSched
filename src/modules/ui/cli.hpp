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
typedef void (CommandLineInterface::*CLIMemCommand)(const std::vector<std::string> &);

class CommandLineInterface: public Core::AbstractUI {

private:
    std::map<std::string, CLIMemCommand> Commands;
    bool done;
    swift::SReadline Reader;
    std::vector<std::string> Completions;

public:
    void init (const std::vector< std::string > &args);
    int run();
    CommandLineInterface(std::vector<Module *> *modules, void *handle);

    void usage(const std::vector<std::string>& unused);
    void quit(const std::vector<std::string>& unused);
    void clear(const std::vector<std::string>& unused);
    void history(const std::vector<std::string>& unused);

    void new_person(const std::vector<std::string>& fields);
    void new_group(const std::vector<std::string>& fields);
};

