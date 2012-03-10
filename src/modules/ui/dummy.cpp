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

    std::cout << "[DummyInterface::test_person] TEST PERSON CREATION works!\n"
        << "Name: " << boost::any_cast<const std::string &>(person->read("name"))
        << "\nSurname: " << boost::any_cast<const std::string &>(person->read("surname"))
        << "\nSex: " << boost::any_cast<const std::string &>(person->read("sex"))
        << std::endl;

    //dump("database.yaml");
}

void DummyInterface::test_group() {
    auto g = create<Core::Group>();
    g->update("name", std::string("Miles Davis band"));
    std::cout << "[DummyInterface::test_group] GROUP CREATION works!\n"
        << "Name: " << boost::any_cast<const std::string &>(g->read("name"))
        << std::endl;
}

void DummyInterface::show_objects() {
    auto rez = this->search();

    std::cout << "[DummyInterface::show_objects] SEARCH works!\nDumping results\n";

    for (auto o : rez) {
        std::cout << "--OBJ--\n";
        for (auto f : o->read()) {
            //std::cout << boost::any_cast<const std::string>(o->read("name")) << "\n";
            std::cout << boost::format("%s: %s\n") % f.first % boost::any_cast<std::string>(f.second);
        }
    }

    std::cout << "[DummyInterface::show_objects] DONE." << std::endl;

}

int DummyInterface::run()
{
    std::cout << "[DummyInterface::run] testing" << std::endl;
    test_person();
    test_group();
    show_objects();
    return 0;
}

extern "C" {

void init(std::vector<Core::Module *> *modules, void *handle)
{
    new DummyInterface(modules, handle);
}

};

