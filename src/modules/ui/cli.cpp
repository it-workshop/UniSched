#include <abstractui.h>

#include <iostream>
#include <malloc.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "Readline.hpp"

class CommandLineInterface;
typedef void (CommandLineInterface::*CLIMemFunc)(void);

class CommandLineInterface: public Core::AbstractUI {

private:
    std::map<std::string, CLIMemFunc> NoArgsCommands;
    bool done;
    readlinecpp::Readline reader;

public:
    void init (const std::vector< std::string > &args);
    void usage();
    void quit();
    void history();
    int run();
    CommandLineInterface(std::vector<Module *> *modules, void *handle);
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
    NoArgsCommands.insert(std::make_pair("usage", &CommandLineInterface::usage));
    NoArgsCommands.insert(std::make_pair("help", &CommandLineInterface::usage));
    NoArgsCommands.insert(std::make_pair("history", &CommandLineInterface::history));
}

void CommandLineInterface::quit() {
    done = true;
}

void CommandLineInterface::history() {
    std::cout << "Historrrrry: " << std::endl;
    reader.save_history(std::cout);
}

void CommandLineInterface::usage() {
    std::cout << "Usage information on our little UniSched Sandbox Edition\n";
    std::cout << "Not so much so far! :]\n";
    std::cout << "\n";
    std::cout << " quit -- quit\n";
    std::cout << " help -- this text\n";
    std::cout << " usage -- this text.\n";
    std::cout << " history -- commands history.\n";
    std::cout << "\n";
    std::cout << " See? Told you so!" << std::endl;
}

int CommandLineInterface::run()
{
    std::string input;
    std::string prompt = "RASPISATOR-REX>> ";
    do {
        input = reader.readline(prompt, done);
        if(done) break;
        if(input.empty()) continue;
        if (NoArgsCommands.find(input) != NoArgsCommands.end()) {
            // DON'T TOUCH THE LINE BELOW, MOTHERFUCKER
            (this->*NoArgsCommands[input])();
            continue;
        }
        std::cout << "Unknown command: " << input << std::endl;
    } while(!done);
}

extern "C" {

void init(std::vector<Core::Module *> *modules, void *handle)
{
    new CommandLineInterface(modules, handle);
}

};

