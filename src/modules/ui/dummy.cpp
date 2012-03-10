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
    dump("new_database.yaml");
}
#endif

void DummyInterface::test_group() {
    auto g = create<Core::Group>();
    g->update("name", std::string("Miles Davis band"));

    auto suppa_truppa = create<Core::Group>();
    suppa_truppa->update("name", std::string("Suppa-pa... Truppa-pa..."));

}

void DummyInterface::show_objects() {
    auto rez = this->search();

    for (auto o : rez) {
        std::cout << "--OBJ--\n";
        for (auto f : o->read()) {
            std::cout << boost::format("%s: %s\n") % f.first % boost::any_cast<std::string>(f.second);
        }
    }

}

int DummyInterface::run()
{
    std::cout << "[DummyInterface::run] testing\n";

    test_person();
    std::cout << "[DummyInterface::test_person] PERSON CREATION works!\n";
    
    test_group();
    std::cout << "[DummyInterface::test_group] GROUP CREATION works!\n";

    show_objects();
    std::cout << "[DummyInterface::show_objects] SEARCH works!" << std::endl;

#ifdef WITH_YAML
    if (yaml_load())
        std::cout << "[DummyInterface::yaml_load] YAML LOAD works!\n";
    else {
        std::cout << "[DummyInterface::yaml_load] YAML LOAD FAILED :(\n";
    }
    yaml_dump();
    std::cout << "[DummyInterface::yaml_dump] YAML DUMP works! check out 'new_database.yaml'" << std::endl;
#endif

    return 0;
}

extern "C" {

void init(std::vector<Core::Module *> *modules, void *handle)
{
    new DummyInterface(modules, handle);
}

};

