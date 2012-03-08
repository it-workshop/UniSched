#include "cli.hpp"

CommandLineInterface::CommandLineInterface(std::vector<Module *> *modules,
        void *handle):
    AbstractUI("CLI", modules, handle)
{}

void CommandLineInterface::init(const std::vector<std::string>& args)
{
    std::cout << "CommandLine Interface INIT" << std::endl;
    done = false;

    Commands.insert(std::make_pair("quit", &CommandLineInterface::quit));
    Commands.insert(std::make_pair("clear", &CommandLineInterface::clear));
    Commands.insert(std::make_pair("usage", &CommandLineInterface::usage));
    Commands.insert(std::make_pair("help", &CommandLineInterface::usage));
    Commands.insert(std::make_pair("history", &CommandLineInterface::history));

    Commands.insert(std::make_pair("new_person", &CommandLineInterface::new_person));
    Commands.insert(std::make_pair("new_group", &CommandLineInterface::new_group));

    std::for_each(Commands.begin(), 
        Commands.end(), 
        [this] (std::pair<const std::string, CLIMemCommand>& p) 
    { Completions.push_back(p.first); } );

    Reader.RegisterCompletions(Completions);
}

void CommandLineInterface::quit(const std::vector<std::string>& unused) {
    done = true;
}

void CommandLineInterface::clear(const std::vector<std::string>& unused) {
    Reader.ClearHistory();
}

void CommandLineInterface::history(const std::vector<std::string>& unused) {
    std::cout << "TODO: implement history listing" << std::endl;
    //reader.save_history(std::cout);
}

void CommandLineInterface::usage(const std::vector<std::string>& unused) {
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

void CommandLineInterface::new_group(const std::vector<std::string>& fields) {
    std::cout << "TODO: implement" << std::endl;
}

void CommandLineInterface::new_person(const std::vector<std::string>& fields) {
    std::cout << "TODO: implement" << std::endl;
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
        if (Commands.find(input) != Commands.end()) {
            // DON'T TOUCH THE LINE BELOW, MOTHERFUCKER
            std::vector<std::string> v; v.push_back("test");
            (this->*Commands[input])(v);
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

