#include <iostream>
#include <malloc.h>

#include <boost/format.hpp>

#include <abstractui.h>

#include "SReadline.h"


class CommandLineInterface;
typedef void (CommandLineInterface::*CLIMemFunc)(void);

class CommandLineInterface: public Core::AbstractUI {

private:
    std::map<std::string, CLIMemFunc> NoArgsCommands;
    bool done;
    swift::SReadline Reader;
    std::vector<std::string> Completions;

public:
    void init (const std::vector< std::string > &args);
    int run();
    CommandLineInterface(std::vector<Module *> *modules, void *handle);

    void usage();
    void quit();
    void clear();
    void history();
};

