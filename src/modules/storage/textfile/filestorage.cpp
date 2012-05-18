#include <abstractstorage.h>

#include <yaml.tab.h>

extern "C" {

FILE *yyin;

extern int yyparse();

};

class FileStorage : public Core::AbstractStorage {
private:
    std::string file_;

protected:
public:

    FileStorage(std::vector<Core::Module *> *modules, void *handle);

    virtual void init(const std::vector<std::string>& args);
    virtual void connect();
    virtual void disconnect();
    virtual void create(const Core::Object *object);
    virtual void remove(const Core::objid_t id);
    virtual void push(Core::objid_t, const std::string&, const boost::any&);
    virtual void push_connect(Core::objid_t, Core::objid_t, bool);
};

FileStorage::FileStorage(std::vector<Core::Module *> *modules, void *handle):
    AbstractStorage("yaml", modules, handle)
{}

void FileStorage::init(const std::vector<std::string>& args)
{
    for (auto it = args.begin(); it != args.end(); ++it)
    {
        if (*it == "--file")
        {
            file_ = *++it;
            continue;
        }
    }
}

void FileStorage::connect()
{
    yyin = fopen(file_.c_str(), "r");
    if (!yyin)
    {
        std::cerr << "FileStorage: Could not open file!" << std::endl;
        return;
    }
    yyparse();
}

void FileStorage::disconnect()
{
}

void FileStorage::create(const Core::Object *object)
{}

void FileStorage::remove(const Core::objid_t id)
{}

void FileStorage::push(Core::objid_t, const std::string&, const boost::any&)
{}

void FileStorage::push_connect(Core::objid_t, Core::objid_t, bool)
{}

extern "C" int yyerror(const char *msg)
{
    std::cerr << msg << std::endl;
    return 0;
}

extern "C" void init(std::vector<Core::Module *> *modules, void *handle)
{
    new FileStorage(modules, handle);
}

