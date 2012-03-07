#include <iostream>
#include <malloc.h>

#include <boost/format.hpp>

#include <abstractui.h>
#include <person.h>
#include <field.h>

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
    void test_person();
};


CommandLineInterface::CommandLineInterface(std::vector<Module *> *modules,
        void *handle):
    AbstractUI("CLI", modules, handle)
{}

void CommandLineInterface::init(const std::vector<std::string>& args)
{
    std::cout << "CommandLine Interface INIT" << std::endl;
    done = false;
    NoArgsCommands.insert(std::make_pair("quit", &CommandLineInterface::quit));
    NoArgsCommands.insert(std::make_pair("clear", &CommandLineInterface::clear));
    NoArgsCommands.insert(std::make_pair("usage", &CommandLineInterface::usage));
    NoArgsCommands.insert(std::make_pair("help", &CommandLineInterface::usage));
    NoArgsCommands.insert(std::make_pair("history", &CommandLineInterface::history));
    NoArgsCommands.insert(std::make_pair("test_person", &CommandLineInterface::test_person));

    std::for_each(NoArgsCommands.begin(), 
        NoArgsCommands.end(), 
        [this] (std::pair<const std::string, CLIMemFunc>& p) 
    { Completions.push_back(p.first); } );


    Reader.RegisterCompletions(Completions);
}

void CommandLineInterface::quit() {
    done = true;
}

void CommandLineInterface::clear() {
    Reader.ClearHistory();
}

void CommandLineInterface::history() {
    std::cout << "Historrrrry listing not working yet :)" << std::endl;
    //reader.save_history(std::cout);
}

void CommandLineInterface::usage() {
    std::cout << "Usage information on our little UniSched Sandbox Edition\n";
    std::cout << "Not so much so far! :]\n";
    std::cout << "\n";
    std::cout << " quit -- quit\n";
    std::cout << " help -- this text\n";
    std::cout << " usage -- this text.\n";
    std::cout << " test_person -- this text.\n";
    std::cout << " history -- commands history.\n";
    std::cout << "\n";
    std::cout << " See? Told you so!" << std::endl;
}

void CommandLineInterface::test_person() {
    std::vector<Core::FieldString> args;
    args.push_back(Core::FieldString("name", "Test"));
    args.push_back(Core::FieldString("surname", "Test"));
    args.push_back(Core::FieldString("sex", "Male"));
    // faaaaaail
    //Core::AbstractUI::create<Core::Person>(args);
    std::cout << "Sorry. Some mess with the creation" << std::endl;
}

int CommandLineInterface::run()
{
    std::string input;
    const std::string prompt = "RASPISATOR-REX>> ";
    const std::string history_path = "/tmp/raspisator"; // NB should be customizable
    Reader.LoadHistory(history_path);
    do {
        input = Reader.GetLine(prompt, done);
        if(done) break;
        if(input.empty()) continue;
        if (NoArgsCommands.find(input) != NoArgsCommands.end()) {
            // DON'T TOUCH THE LINE BELOW, MOTHERFUCKER
            (this->*NoArgsCommands[input])();
            continue;
        }
        std::cout << "Unknown command: " << input << std::endl;
    } while(!done);

    Reader.SaveHistory(history_path);
}

extern "C" {

void init(std::vector<Core::Module *> *modules, void *handle)
{
    new CommandLineInterface(modules, handle);
}

};

