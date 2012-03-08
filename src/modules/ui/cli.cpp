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
    Commands.insert(std::make_pair("exit", &CommandLineInterface::quit));
    Commands.insert(std::make_pair("clear", &CommandLineInterface::clear));
    Commands.insert(std::make_pair("usage", &CommandLineInterface::usage));
    Commands.insert(std::make_pair("help", &CommandLineInterface::usage));
    Commands.insert(std::make_pair("history", &CommandLineInterface::history));
    Commands.insert(std::make_pair("toggle_debug", &CommandLineInterface::toggle_debug));

    Commands.insert(std::make_pair("new_person", &CommandLineInterface::new_person));
    Commands.insert(std::make_pair("new_group", &CommandLineInterface::new_group));

    std::for_each(Commands.begin(), 
        Commands.end(), 
        [this] (std::pair<const std::string, CLIMemCommand>& p) 
    { Completions.push_back(p.first); } );

    Reader.RegisterCompletions(Completions);
}

int CommandLineInterface::quit(const std::vector<std::string>& unused) {
    done = true;
    return 0;
}

int CommandLineInterface::toggle_debug(const std::vector<std::string>& unused) {
    debug = !debug;
    if (debug) {
        std::cout << "DEBUG ON" << std::endl;
    }
    else {
        std::cout << "DEBUG OFF" << std::endl;
    }
}

int CommandLineInterface::clear(const std::vector<std::string>& unused) {
    Reader.ClearHistory();
    return 0;
}

int CommandLineInterface::history(const std::vector<std::string>& unused) {
    std::cout << "TODO: implement history listing" << std::endl;
    return 0;
    //reader.save_history(std::cout);
}

int CommandLineInterface::usage(const std::vector<std::string>& unused) {
    std::cout << "Usage information on our little UniSched Sandbox Edition\n"
        << "Not so much so far! :]\n"
        << "\n"
        << " quit,exit -- quit\n"
        << " help,usage -- this text\n"
        << " toggle_debug -- show additional info\n"
        << " new_person name surname sex -- create new person sex = MALE || FEMALE\n"
        << " new_group name -- create new group with name 'name'\n"
        << " history -- commands history.\n"
        << "\n"
        << " See? Told you so!" << std::endl;
    return 0;
}

int CommandLineInterface::new_person(const std::vector<std::string>& tokens) {
    if (tokens.size() != 4) {
        std::cout << boost::format("Weird amount of args (was hoping for 3, got %s)\n") % (tokens.size() - 1)
            << std::endl;
        return -1;
    }

    if ((tokens[3] != "MALE") && (tokens[3] != "FEMALE")) {
        std::cout << "Bad gender. Expected MALE or FEMALE" << std::endl;
        return -2;
    }

    auto p = create<Core::Person>();
    p->update("name", tokens[1]);
    p->update("surname", tokens[2]);
    p->update("sex", tokens[3]);

    if (debug) {
        std::cout << "CREATED NEW PERSON\n"
            << "Name: " << boost::any_cast<std::string>(p->read("name"))
            << "\nSurname: " << boost::any_cast<std::string>(p->read("surname"))
            << "\nSex: " << boost::any_cast<std::string>(p->read("sex"))
            << std::endl;
    }

    return 0;
}

int CommandLineInterface::new_group(const std::vector<std::string>& tokens) {
    if (tokens.size() != 2) {
        std::cout << boost::format("Weird amount of args (was hoping for 1, got %s)") % (tokens.size() - 1)
            << std::endl;
        return -1;
    }

    auto g = create<Core::Group>();
    g->update("name", tokens[1]);

    if (debug) {
        std::cout << "CREATED NEW GROUP\n"
            << "Name: " << boost::any_cast<std::string>(g->read("name"))
            << std::endl;
    }

    return 0;
}


int CommandLineInterface::run()
{
    std::vector<std::string> tokens(4);
    const std::string prompt = "RASPISATOR-REX>> ";
    const std::string history_path = "/tmp/raspisator"; // NB should be customizable

    Reader.LoadHistory(history_path);
    do {
        Reader.GetLine(prompt, tokens, done);
        if(done) break;
        if(tokens.empty()) continue;
        if(debug) {
            std::cout << "[DEBUG] Tokens: \n";
            std::for_each(tokens.begin(), 
                tokens.end(), 
                [&] (std::string s) 
            { std::cout << "\t" << s << "\n"; } );
            std::cout << std::endl;
        }
        if (Commands.find(tokens[0]) != Commands.end()) {
            (this->*Commands[tokens[0]])(tokens);
            continue;
        }
        std::cout << "Unknown command: " << tokens[0] << std::endl;
    } while(!done);

    Reader.SaveHistory(history_path);
}

extern "C" {

void init(std::vector<Core::Module *> *modules, void *handle)
{
    new CommandLineInterface(modules, handle);
}

};

