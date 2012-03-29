#include "dummy.hpp"

void DummyInterface::init(const std::vector<std::wstring>& args)
{
}

DummyInterface::DummyInterface(std::vector<Module *>* modules, void *handle):
    AbstractUI(L"DummyUI", modules, handle)
{
}

void DummyInterface::test_person() {

    auto person = create<Core::Person>();
    person->update(L"name", std::wstring(L"John"));
    person->update(L"surname", std::wstring(L"Connor"));
    person->update(L"sex", std::wstring(L"MALE"));
    person->update(L"birthday", time_t(300400));

    std::map<std::wstring, boost::any> fields;
    fields[L"name"] = std::wstring(L"Harry");
    fields[L"surname"] = std::wstring(L"Potter");
    fields[L"sex"] = std::wstring(L"MALE");
    fields[L"birthday"] = time_t(19283740);

    auto pers = create<Core::Person>();
    pers->update(fields);
}

void DummyInterface::test_group() {
    auto g = create<Core::Group>();
    g->update(L"name", std::wstring(L"Miles Davis band"));

    auto suppa_truppa = create<Core::Group>();
    suppa_truppa->update(L"name", std::wstring(L"Suppa-pa... Truppa-pa..."));
}

void DummyInterface::test_connect() {
    auto g = create<Core::Group>();
    g->update(L"name", std::wstring(L"SW gang")); // Sounds like Swamp Soft, rip

    auto r2d2 = create<Core::Person>();
    r2d2->update(L"name", std::wstring(L"r2"));
    r2d2->update(L"surname", std::wstring(L"d2"));
    r2d2->update(L"sex", std::wstring(L"MALE"));
    r2d2->update(L"birthday", time_t(100500));

    auto c3po = create<Core::Person>();
    c3po->update(L"name", std::wstring(L"c3"));
    c3po->update(L"surname", std::wstring(L"po"));
    c3po->update(L"sex", std::wstring(L"MALE"));
    c3po->update(L"birthday", time_t(300700));

    g->connect(r2d2);
    g->connect(c3po);
}

void DummyInterface::show_objects() {
    auto rez = this->search();

    for (auto o : rez) {
        std::wcout << L"--OBJ--\n";
        for (auto f : o->read()) {
            if (typeid(std::wstring) == f.second.type()) {
                std::wcout << boost::wformat(L"%s: %s\n") % f.first % boost::any_cast<std::wstring>(f.second);
            }
            else if (typeid(std::vector<Core::Object *>) == f.second.type()) {
                auto vect = boost::any_cast<std::vector<Core::Object *>&>(f.second);
                std::wcout << f.first << L":\n";
                for (auto& item : vect) {
                    std::wcout << L"\t" << boost::any_cast<std::wstring>(item->read(L"name")) << L"\n";
                }
            }
        }
    }

}

int DummyInterface::run()
{
    std::wcout << L"[DummyInterface::run] testing...\n";
#ifdef WITH_TESTS_CORE
    test_person();
    std::wcout << L"[DummyInterface::test_person] PERSON CREATION works!\n";
    
    test_group();
    std::wcout << L"[DummyInterface::test_group] GROUP CREATION works!\n";

    test_connect();
    std::wcout << L"[DummyInterface::test_connect] CONNECT works!" << std::endl;

    show_objects();
    std::wcout << L"[DummyInterface::show_objects] SEARCH works!" << std::endl;
#endif

    return 0;
}

extern "C" {

void init(std::vector<Core::Module *> *modules, void *handle)
{
    new DummyInterface(modules, handle);
}

};

