#include <abstractui.h>

#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>

class CommandLineInterface: public Core::AbstractUI {

public:
    void init (const std::vector< std::string > &args);
    int run();
    CommandLineInterface(std::vector<Module *> *modules, void *handle);
};

void CommandLineInterface::init(const std::vector<std::string>& args)
{
    std::cout << "CommandLine Interface INIT" << std::endl;
}

CommandLineInterface::CommandLineInterface(std::vector<Module *> *modules,
        void *handle):
    AbstractUI("CLI", modules, handle)
{}

int CommandLineInterface::run()
{
    // Nasty nasty C-style
    char *buf = new char(255);
    while ((buf = readline("\n >> ")) != NULL)  {
        if (strcmp(buf, "quit") == 0) {
            break;
        }

        std::cout << " << " << buf << std::endl;

        if(buf[0] != 0) {
            add_history(buf);
        }

    }
    free (buf);

    return 0;
}

extern "C" {

void init(std::vector<Core::Module *> *modules, void *handle)
{
    new CommandLineInterface(modules, handle);
}

};

