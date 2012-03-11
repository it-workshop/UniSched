#include "dummy.hpp"


void DummyInterface::init(const std::vector<std::string>& args)
{
    std::cout << "Dummy Interface INIT" << std::endl;
}

DummyInterface::DummyInterface(std::vector<Module *>* modules, void *handle):
    AbstractUI("DummyUI", modules, handle)
{
    std::cout << "Hello constructor!" << std::endl;
}

void DummyInterface::test_person() {

    auto person = create<Core::Person>();
    person->update("name", std::string("John"));
    person->update("surname", std::string("Connor"));
    person->update("sex", std::string("MALE"));

    auto pers = create<Core::Person>();
    pers->update("name", std::string("Harry"));
    pers->update("surname", std::string("Potta"));
    pers->update("sex", std::string("MALE"));

}

#ifdef WITH_YAML
bool DummyInterface::yaml_load() {
    return load(DATABASE_YAML);
}

void DummyInterface::yaml_dump() {

    auto person = create<Core::Person>();
    person->update("name", std::string("John"));
    person->update("surname", std::string("Connor"));
    person->update("sex", std::string("MALE"));
    
    auto g = create<Core::Group>();
    g->update("name", std::string("Miles Davis band"));
  
    //g->connect(person);

    dump("new_database.yaml");
}
#endif

void DummyInterface::test_group() {
    auto g = create<Core::Group>();
    g->update("name", std::string("Miles Davis band"));

    auto suppa_truppa = create<Core::Group>();
    suppa_truppa->update("name", std::string("Suppa-pa... Truppa-pa..."));

}

void DummyInterface::test_connect() {
    auto g = create<Core::Group>();
    g->update("name", std::string("SW gang"));

    auto r2d2 = create<Core::Person>();
    r2d2->update("name", std::string("r2"));
    r2d2->update("surname", std::string("d2"));
    r2d2->update("sex", std::string("MALE"));

    auto c3po = create<Core::Person>();
    r2d2->update("name", std::string("c3"));
    r2d2->update("surname", std::string("po"));
    r2d2->update("sex", std::string("MALE"));

    g->connect(r2d2);
    g->connect(c3po);
}

void DummyInterface::show_objects() {
    auto rez = this->search();

    for (auto o : rez) {
        std::cout << "--OBJ--\n";
        for (auto f : o->read()) {
            if (f.first != "groups" && f.first != "people") {
                std::cout << boost::format("%s: %s\n") % f.first % boost::any_cast<std::string>(f.second);
            }
        }
    }

}

int DummyInterface::run()
{
    std::cout << "[DummyInterface::run] testingi...\n";
#ifdef WITH_TESTS_CORE
    test_person();
    std::cout << "[DummyInterface::test_person] PERSON CREATION works!\n";
    
    test_group();
    std::cout << "[DummyInterface::test_group] GROUP CREATION works!\n";

    test_connect();
    std::cout << "[DummyInterface::test_connect] CONNECT works!" << std::endl;

    show_objects();
    std::cout << "[DummyInterface::show_objects] SEARCH works!" << std::endl;
#else
#ifdef WITH_YAML
    if (yaml_load())
        std::cout << "[DummyInterface::yaml_load] YAML LOAD works!\n";
    else {
        std::cout << "[DummyInterface::yaml_load] YAML LOAD FAILED :(\n";
    }
    yaml_dump();
    std::cout << "[DummyInterface::yaml_dump] YAML DUMP works! check out 'new_database.yaml'" << std::endl;
#endif
#endif
    return 0;
}

extern "C" {

void init(std::vector<Core::Module *> *modules, void *handle)
{
    new DummyInterface(modules, handle);
}

};

