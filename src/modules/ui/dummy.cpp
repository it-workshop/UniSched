#include "dummy.hpp"

void DummyInterface::init(const std::vector<std::string>& args)
{
    std::cout << "Dummy Interface INIT" << std::endl;
}

DummyInterface::DummyInterface(std::vector<Module *>* modules, void *handle):
    AbstractUI("DummyUI", modules, handle)
{
    std::cout << "(Dummy Interface constructor) ";
}

void DummyInterface::test_person() {

    auto person = create<Core::Person>();
    person->update("name", std::string("John"));
    person->update("surname", std::string("Connor"));
    person->update("sex", std::string("MALE"));
    person->update("birthday", time_t(300400));

    std::map<std::string, boost::any> fields;
    fields["name"] = std::string("Harry");
    fields["surname"] = std::string("Potter");
    fields["sex"] = std::string("MALE");
    fields["birthday"] = time_t(19283740);

    auto pers = create<Core::Person>();
    pers->update(fields);
}

void DummyInterface::test_group() {
    auto g = create<Core::Group>();
    g->update("name", std::string("Miles Davis band"));

    auto suppa_truppa = create<Core::Group>();
    suppa_truppa->update("name", std::string("Suppa-pa... Truppa-pa..."));
}

void DummyInterface::test_connect() {
    auto g = create<Core::Group>();
    g->update("name", std::string("SW gang")); // Sounds like Swamp Soft, rip

    auto r2d2 = create<Core::Person>();
    r2d2->update("name", std::string("r2"));
    r2d2->update("surname", std::string("d2"));
    r2d2->update("sex", std::string("MALE"));
    r2d2->update("birthday", time_t(100500));

    auto c3po = create<Core::Person>();
    c3po->update("name", std::string("c3"));
    c3po->update("surname", std::string("po"));
    c3po->update("sex", std::string("MALE"));
    c3po->update("birthday", time_t(300700));

    g->connect(r2d2);
    g->connect(c3po);
}

void DummyInterface::show_objects() {
    auto rez = this->search();

    for (auto o : rez) {
        std::cout << "--OBJ--\n";
        for (auto f : o->read()) {
            if (typeid(std::string) == f.second.type()) {
                std::cout << boost::format("%s: %s\n") % f.first % boost::any_cast<std::string>(f.second);
            }
            else if (typeid(std::vector<Core::Object *>) == f.second.type()) {
                auto vect = boost::any_cast<std::vector<Core::Object *>&>(f.second);
                std::cout << f.first << ":\n";
                for (auto& item : vect) {
                    std::cout << "\t" << boost::any_cast<std::string>(item->read("name")) << "\n";
                }
            }
        }
    }

}

int DummyInterface::run()
{
    std::cout << "[DummyInterface::run] testing...\n";
#ifdef WITH_TESTS_CORE
    test_person();
    std::cout << "[DummyInterface::test_person] PERSON CREATION works!\n";
    
    test_group();
    std::cout << "[DummyInterface::test_group] GROUP CREATION works!\n";

    test_connect();
    std::cout << "[DummyInterface::test_connect] CONNECT works!" << std::endl;

    show_objects();
    std::cout << "[DummyInterface::show_objects] SEARCH works!" << std::endl;
#endif

    return 0;
}

extern "C" {

void init(std::vector<Core::Module *> *modules, void *handle)
{
    new DummyInterface(modules, handle);
}

};

