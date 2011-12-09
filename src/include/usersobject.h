#pragma once

#include <string>
#include <vector>
#include <typeinfo>

namespace UI {

class UsersObject {
private:
protected:
public:
    virtual const std::string read() const = 0;
    virtual const int read_int(const std::string name) const throw (std::bad_cast) = 0;
    virtual const std::string read_string(const std::string name) const throw (std::bad_cast) = 0;
    virtual const time_t read_time(const std::string name) const throw (std::bad_cast) = 0;
    virtual const std::string read_enum(const std::string name) const throw (std::bad_cast) = 0;
    virtual const std::vector<UsersObject const *> * read_vector(const std::string name) const throw (std::bad_cast) = 0;

    virtual void update(const std::string name, const int value) throw (std::bad_cast) = 0;
    virtual void update(const std::string name, const std::string value) throw (std::bad_cast) = 0;
    virtual void update(const std::string name, const time_t value) throw (std::bad_cast) = 0;
    virtual void update_enum(const std::string name, const std::string value) throw (std::bad_cast) = 0;
    virtual void update(UsersObject * object, const bool linked) throw (std::bad_cast) = 0;
};

};

