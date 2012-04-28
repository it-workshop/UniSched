#include <iostream>
#include <malloc.h>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#include <boost/format.hpp>
#include <boost/tokenizer.hpp>

#include <abstractui.h>
#include <object.h>
#include <person.h>
#include <group.h>
#include <event.h>

#include "SReadline.h"


class CommandLineInterface;
typedef int (CommandLineInterface::*CLIMemCommand)(const std::vector<std::string> &);
typedef boost::tokenizer<boost::escaped_list_separator<char>> Tokenizer;

class CommandLineInterface: public Core::AbstractUI {

private:
    std::map<std::string, CLIMemCommand> Commands;
    bool done;
    bool debug;
    swift::SReadline Reader;
    std::vector<std::string> Completions;
    int crazy_factory(std::string product_type, std::map<std::string, std::string> fields);
    Core::Object* mini_conveyor(std::string product_type);

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
    int new_event(const std::vector<std::string>& tokens);
    int dig_for_objects(const std::vector<std::string>& tokens);
    int load_csv(const std::vector<std::string>& tokens);
    int dump_csv(const std::vector<std::string>& tokens);

    int cache(const std::vector<std::string>& tokens);
    int reset(const std::vector<std::string>& tokens);

    int read(const std::vector<std::string>& tokens);
    int update(const std::vector<std::string>& tokens);
    int connect(const std::vector<std::string>& tokens);
};

