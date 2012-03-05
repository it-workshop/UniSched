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

CommandLineInterface _object;
