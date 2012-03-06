#include <abstractui.h>

#include <iostream>
#include <malloc.h>
#include <readline/readline.h>
#include <readline/history.h>

class CommandLineInterface;
typedef int (CommandLineInterface::*CLIMemFunc)(void);

class CommandLineInterface: public Core::AbstractUI {

private:
    std::map<std::string, CLIMemFunc> commands;
    bool done;

public:
    void init (const std::vector< std::string > &args);
    int usage();
    int quit();
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
    commands.insert(std::make_pair("quit", &CommandLineInterface::quit));
    commands.insert(std::make_pair("usage", &CommandLineInterface::usage));
    commands.insert(std::make_pair("help", &CommandLineInterface::usage));
}

int CommandLineInterface::quit() {
    done = true;
    return 0;
}

int CommandLineInterface::usage() {
    std::cout << "Usage information on our little UniSched Sandbox Edition\n";
    std::cout << "Not so much so far! :]\n";
    std::cout << "\n";
    std::cout << " quit -- quit\n";
    std::cout << " help -- this text\n";
    std::cout << " usage -- this text.\n";
    std::cout << "\n";
    std::cout << " See? Told you so!" << std::endl;
    return 0;
}

int CommandLineInterface::run()
{
    // Nasty nasty C-style
    char *buf;
    while (!done) {
        if ((buf = readline("\n >> ")) == NULL)  {
            done = true;
            break; // Зачем тебе в программе два JMP подряд?
                   // а вдруг первый не сработает...
        }

        if(buf[0] != 0) {
            add_history(buf);
        }

        std::cout << " << " << buf << std::endl;

        if (commands.find(buf) != commands.end()) {
            // DON'T TOUCH THE LINE BELOW, MOTHEFUCKER
            (this->*commands[buf])();
        }
        free (buf);
    }

    return 0;
}

extern "C" {

void init(std::vector<Core::Module *> *modules, void *handle)
{
    new CommandLineInterface(modules, handle);
}

};

