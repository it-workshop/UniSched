#include <abstractui.h>

#include <readline/readline.h>
#include <readline/history.h>

class CommandLineInterface: public Core::AbstractUI {

public:
    void init (const std::vector< std::string > &args);
    int run();
    CommandLineInterface();
};

void CommandLineInterface::init(const std::vector<std::string>& args)
{
    std::cout << "CommandLine Interface INIT" << std::endl;
}

CommandLineInterface::CommandLineInterface() : AbstractUI("CLI") {
}

int CommandLineInterface::run()
{
    std::cout << "CommandLine Interface RUN" << std::endl;
    return 0;
}

CommandLineInterface _object;
