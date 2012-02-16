#pragma once

#include <string>
#include <utility>
#include <vector>
#include <typeinfo>
#include <object.h>

namespace Core {

class Field {
public:
    enum Type {
        STRING,
        TIME,
        ENUM,
        LINK,
        VECTOR
    };

private:
    const std::string name_;
    const enum Type type_;

protected:
public:
    Field(const Type type, const std::string& name) throw ():
        type_(type), name_(name)
    {}

    const std::string& name() const throw()
    {
        return name_;
    }

    const Type type() const throw()
    {
        return type_;
    }

    virtual const Field& operator=(const Field& field)
            throw (std::bad_cast) = 0;
    virtual const bool operator==(const Field& field) const
            throw (std::bad_cast) = 0;
};

class FieldString : public Field {
private:
    std::string value_;
protected:
public:
    FieldString(const std::string& name, const std::string& value = "")
        throw ():
        Field(STRING, name), value_(value)
    {}

    const std::string& value(const std::string& value) throw ()
    {
        return value_ = value;
    }

    const std::string& value() const throw ()
    {
        return value_;
    }

    virtual Field& operator=(const Field& field) throw (std::bad_cast)
    {
        value(dynamic_cast<const FieldString&>(field).value());
        return *this;
    }

    virtual const bool operator==(const Field& field) const throw (std::bad_cast)
    {
        return (value() == dynamic_cast<const FieldString&>(field).value() 
                && name() == field.name());
    }
};

class FieldTime : public Field {
private:
    time_t value_;
protected:
public:
    FieldTime(const std::string& name, const time_t& value = 0)
        throw ():
        Field(TIME, name), value_(value)
    {}

    const time_t value(const time_t& value) throw ()
    {
        return value_ = value;
    }

    const time_t value() const throw ()
    {
        return value_;
    }

    virtual const Field& operator=(const Field& field) throw (std::bad_cast)
    {
        value(dynamic_cast<const FieldTime&>(field).value());
        return *this;
    }

    virtual const bool operator==(const Field& field) const throw (std::bad_cast)
    {
        return (value() == dynamic_cast<const FieldTime&>(field).value()
                && name() == field.name());
    }
};

class FieldEnum : public Field {
private:
    std::string value_;

protected:
public:
    FieldEnum(const std::string& name, const std::string& value) throw ():
        Field(ENUM, name), value_(value)
    {}

    const std::string& value(const std::string& value) throw ()
    {
        return value_ = value;
    }

    const std::string& value() const throw ()
    {
        return value_;
    }

    virtual const Field& operator=(const Field& field) throw (std::bad_cast) 
    {
        value(dynamic_cast<const FieldEnum&>(field).value());
        return *this;
    }

    virtual const bool operator==(const Field& field) const throw (std::bad_cast)
    {
        return (value() == dynamic_cast<const FieldEnum&>(field).value()
                && name() == field.name());
    }
};

class FieldLink : public Field {
private:
    std::pair<Object *, bool> value_;

protected:
public:
    FieldLink(const std::string& name,
                const std::pair<Object *, bool>& value) throw():
        Field(LINK, name), value_(value)
    {}

    
    std::pair<Object *, bool>
    value(const std::pair<Object *, bool>& value) throw()
    {
        return value_ = value;
    }

    std::pair<Object *, bool>
    value() const throw()
    {
        return value_;
    }

    virtual const Field& operator=(const Field& field) throw (std::bad_cast)
    {
        value(dynamic_cast<const FieldLink&>(field).value());
        return *this;
    }

    virtual const bool operator==(const Field& field) const throw (std::bad_cast)
    {
        return (value() == dynamic_cast<const FieldLink&>(field).value()
                && name() == field.name());
    }
};

class FieldVector : public Field {
private:
    std::vector<Object *> vector_;
protected:
public:
    FieldVector(const std::string& name,
                const std::vector<Object *>& vector) throw():
        Field(VECTOR, name), vector_(vector)
    {}

    FieldVector(const std::string& name) throw():
        Field(VECTOR, name)
    {}

    const std::vector<Object *>&
    vector(const std::vector<Object *>& vector) throw()
    {
        return vector_ = vector;
    }

    const std::vector<Object *>& vector() const throw()
    {
        return vector_;
    }

    virtual const Field& operator=(const Field& field) throw (std::bad_cast)
    {
        vector(dynamic_cast<const FieldVector&>(field).vector());
        return *this;
    }

    virtual const bool operator==(const Field& field) const throw (std::bad_cast)
    {
        throw std::bad_cast();
    }

    void add(Object * object)
    {
        for (Object *obj : vector_)
        {
            if (obj == object)
            {
                return;
            }
        }
        vector_.push_back(object);
    }

    void del(Object * object)
    {
        for (auto it = vector_.begin(); it != vector_.end(); it++)
        {
            if (*it == object)
            {
                vector_.erase(it);
                return;
            }
        }
    }

    void commit(const FieldLink& field)
    {
        if (field.value().second)
            this->add(field.value().first);
        else
            this->del(field.value().first);
    }
};

}

