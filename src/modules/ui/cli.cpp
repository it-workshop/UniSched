#include "cli.hpp"

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
    std::cout << "Usage information on our little UniSched Sandbox Edition\n"
        << "Not so much so far! :]\n"
        << "\n"
        << " quit -- quit\n"
        << " help -- this text\n"
        << " usage -- this text.\n"
        << " test_person -- this text.\n"
        << " history -- commands history.\n"
        << "\n"
        << " See? Told you so!" << std::endl;
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

