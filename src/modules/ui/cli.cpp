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

    Commands.insert(std::make_pair("person", &CommandLineInterface::new_person));
    Commands.insert(std::make_pair("search", &CommandLineInterface::dig_for_objects));
    Commands.insert(std::make_pair("group", &CommandLineInterface::new_group));
    Commands.insert(std::make_pair("event", &CommandLineInterface::new_event));
    Commands.insert(std::make_pair("load_csv", &CommandLineInterface::load_csv));
    Commands.insert(std::make_pair("dump_csv", &CommandLineInterface::dump_csv));

    std::for_each(Commands.begin(), 
        Commands.end(), 
        [this] (std::pair<const std::string, CLIMemCommand>& p) 
    { Completions.push_back(p.first); } );

    std::vector<std::string> dump_load_func_compl;
    dump_load_func_compl.push_back("load_csv");
    dump_load_func_compl.push_back("save_csv");
    std::vector<std::string> datatypes;
    datatypes.push_back("person");
    datatypes.push_back("group");
    datatypes.push_back("event");
    for (auto f: dump_load_func_compl)  {
        for (auto dt: datatypes) {
            Completions.push_back(boost::str(boost::format("%s %s %%file") % f % dt));
        }
    }

    Reader.RegisterCompletions(Completions);
}

int CommandLineInterface::quit(const std::vector<std::string>& unused) {
    done = true;
    return 0;
}

int CommandLineInterface::dump_csv(const std::vector<std::string>& unused) {
    std::cout << "NOT IMPLEMENTED YET" << std::endl;
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

static std::ostream&
operator<< (std::ostream& stream, const boost::any& value)
    throw (boost::bad_any_cast)
{
    if (value.type() == typeid(const std::string))
    {
        stream << boost::any_cast<const std::string&>(value);
        return stream;
    }
    if (value.type() == typeid(const time_t))
    {
        stream << boost::any_cast<const time_t>(value);
        return stream;
    }
    if (value.type() == typeid(std::vector<Core::Object *>&))
    {
        stream << boost::format("(length: %u)")
            % boost::any_cast<std::vector<Core::Object *>>(value).size();
    }
    throw boost::bad_any_cast();
}

static std::ostream&
operator<< (std::ostream& stream, const std::vector<Core::Object *>& vect)
    throw (boost::bad_any_cast)
{
    for (auto o : vect)
    {
        stream << "\n\tobject:";
        for (auto f : o->read())
        {
            stream << "\n\t\t" << f.first << ":\t" << f.second;
        }
    }
    return stream;
}

int CommandLineInterface::dig_for_objects(const std::vector<std::string>& tokens) {
    auto rez = this->search();
    for (auto o : rez) {
        std::cout << "object:";
        for (auto f : o->read()) {
            std::cout << "\n\t" << f.first << ":\t" << f.second;
        }
        std::cout << "\n";
    }
    //for(auto f = p->read().begin(); f != p->read().end(); f++) {
        //std::cout << f->first;
    std::cout << std::flush;
}

std::vector<std::string> parse_line(std::string line) {
    Tokenizer tok(line);
    std::vector<std::string> v;
    v.assign(tok.begin(), tok.end());

    return v;
}

Core::Object* CommandLineInterface::mini_conveyor(std::string product_type) {
    if (product_type == "person") {
        return create<Core::Person>();
    }
    if (product_type == "event") {
        return create<Core::Event>();
    }
    if (product_type == "group") {
        return create<Core::Group>();
    }
}

int CommandLineInterface::crazy_factory(std::string product_type, std::map<std::string, std::string> fields) {
    auto o = mini_conveyor(product_type);
    for (auto m: fields) {
        o->update(m.first, m.second);
    }
    return 0;
}

int CommandLineInterface::load_csv(const std::vector<std::string>& tokens) {

    std::ifstream in(tokens[2].c_str());

    if(!in.is_open()) {
        std::cout << boost::format("Couldn't open '%s'") % tokens[2] << std::endl;
        return -1;
    }

    std::vector<std::string> v;
    std::string line;
    std::vector<std::string> legend;

    if (std::getline(in, line)) {
        legend = parse_line(line);
        if (debug) {
            std::cout << "[DEBUG]\n got legend:\n";
            for(auto i: legend) {
                std::cout << "\t" << i << "\n";
            }
        }
    }
    else {
        std::cout << "Malformed legend (first line)" << std::endl;
    }

    auto counter = 0, notify = 10;
    while(std::getline(in, line))
    {
        if (debug) {
            counter++;
            if (!(counter % notify)) {
                std::cout << boost::format("parsing lines %s..%s\n") % counter % (counter + notify);
            }
        }
        v = parse_line(line);

        if(v.size() != legend.size()) continue;

        if (debug) {
            std::cout << "[DEBUG] fields on this line:\n";
            for(auto i: v) {
                std::cout << i << "\n";
            }
        }

        auto o = mini_conveyor(tokens[1]);

        for(auto i = 0; i < legend.size(); i++) {
            o->update(legend[i], v[i]);
        }
        
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
        std::cout << boost::format("Weird amount of args (was hoping for 3, got %s)") % (tokens.size() - 1)
            << std::endl;
        return -1;
    }

    auto p = create<Core::Person>();

    std::vector<std::string> person_fields;
    person_fields.push_back("name");
    person_fields.push_back("surname");
    person_fields.push_back("sex");

    for (int i = 0; i < 3; ++i)
    {
        try 
        {
            p->update(person_fields[i], tokens[i+1]);
        }
        catch (boost::bad_any_cast& bc)
        {
            std::cerr << boost::format("Bad cast happened in field '%s'") % (person_fields[i]) << std::endl;
            return -2;
        }
    }

    if (debug) {
        std::cout << "[DEBUG]\n";
        for(auto& f: person_fields) {
            std::cout << boost::format("%s: %s\n") % f % boost::any_cast<std::string>(p->read(f));
        }

    }

    std::cout << "CREATED NEW PERSON" << std::endl;


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

int CommandLineInterface::new_event(const std::vector<std::string>& tokens) {
    if (tokens.size() != 2) {
        std::cout << boost::format("Weird amount of args (was hoping for 1, got %s)") % (tokens.size() - 1)
            << std::endl;
        return -1;
    }

    auto g = create<Core::Group>();
    g->update("name", tokens[1]);

    if (debug) {
        std::cout << "CREATED NEW EVENT\n"
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
            for(auto& i: tokens) std::cout << "\t" << i;
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

