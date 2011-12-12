#include <abstractstorage.h>

class DummyStorage: public Storage::AbstractStorage {
private:
protected:
    virtual const int get_field_int(const int id, const std::string name) const throw (std::bad_cast)
            { return 0; }
    virtual const std::string get_field_string(const int id, const std::string name) const throw (std::bad_cast)
            { return ""; }
    virtual const time_t get_field_time(const int id, const std::string name) const throw (std::bad_cast)
            { return 0; }
    virtual const std::string get_field_enum(const int id, const std::string name) const throw (std::bad_cast)
            { return ""; }
    virtual Storage::StorableObject * get_field_object(const int id, const std::string name) const throw (std::bad_cast)
            { return objects_[0]; }
    virtual const std::vector<Storage::StorableObject *> get_field_vector(const int id, const std::string name) const throw (std::bad_cast)
            { return objects_; }

    virtual void set_field(const int id , const std::string name, const int value) throw (std::bad_cast)
            {}
    virtual void set_field(const int id , const std::string name, const std::string value) throw (std::bad_cast)
            {}
    virtual void set_field(const int id , const std::string name, const time_t value) throw (std::bad_cast)
            {}
    virtual void set_field_enum(const int id , const std::string name, const std::string value) throw (std::bad_cast)
            {}
    virtual void set_field(const int id , const std::string name, Storage::StorableObject * value) throw (std::bad_cast)
            {}
    virtual void set_field_vector(const int id , const std::string name, const std::vector<Storage::StorableObject *> value) throw (std::bad_cast)
            {}
public:

    virtual std::vector<Storage::StorableObject *> * search(std::vector<Argument *>&)
            { return &objects_; }
};

#include <person.h>
#include <group.h>
#include <event.h>

int main()
{
    DummyStorage storage;

    std::vector<const Storage::AbstractStorage::Argument *> parameters;

    storage.create<Core::Person>(parameters);
    storage.create<Core::Group>(parameters);
    storage.create<Core::Event>(parameters);

    return 0;
}

