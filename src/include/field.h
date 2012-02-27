#pragma once

#include <string>
#include <utility>
#include <vector>
#include <typeinfo>
#include <object.h>

namespace Core {

/** @class Field
 * @brief Base class for fields of different types.
 *
 * Object consist of field name, type and value.
 * Value must be implemented in inherited classes.
 */
class Field {
public:
    /** @enum Type
     * @brief Enumeration of possible field's types.
     *
     * Used to check field type without typeid operator.
     */
    enum Type {
        STRING,
        TIME,
        ENUM,
        LINK,
        VECTOR
    };

private:
    const enum Type type_;
                        /**< Type of the field. */
    const std::string name_;
                        /**< Name of the field. */
protected:
    Field(const Type type, const std::string& name) throw ():
        type_(type), name_(name)
                        /**< @brief Constructor
                         * @param type Type of field.
                         * @param name Name of field.
                         * @internal For inherited classes only.
                         */
    {}
protected:

    const std::string& name() const throw()
                        /**< @brief Get name of the field.
                         * @return field's name.
                         */
    {
        return name_;
    }

    const Type type() const throw()
                        /**< @brief Get type of the field.
                         * @return field's type.
                         */
    {
        return type_;
    }

    virtual const Field& operator=(const Field& field)
            throw (std::bad_cast) = 0;
                        /**< @brief Assigment operator.
                         * @param field Field with value to assign.
                         * @return This field.
                         *
                         * Assign this field's value to another fields value, if
                         * they have one type.
                         */

    virtual const bool operator==(const Field& field) const
            throw (std::bad_cast) = 0;
                        /**< @brief Comparison operator.
                         * @param field Field with value to compare.
                         * @return result of comparison.
                         *
                         * Compare values of two fields, if they have one type.
                         */
};

/** @class FieldString
 * @brief Field of string type.
 *
 * Simple class contains name and std::string value.
 */
class FieldString : public Field {
private:
    std::string value_;
                        /**< Value of the field. */
protected:
public:
    FieldString(const std::string& name, const std::string& value = "")
        throw ():
        Field(STRING, name), value_(value)
                        /**< @brief Constructor.
                         * @param name Name of the field.
                         * @param value Value of the field. Empty by default.
                         */
    {}

    const std::string& value(const std::string& value) throw ()
                        /**< @brief Change value.
                         * @param New value of the field.
                         * @return Value of the field AFTER assigment.
                         */
    {
        return value_ = value;
    }

    const std::string& value() const throw ()
                        /**< @brief Get value.
                         * @return Current value of the field.
                         * 
                         * This method does not changes value.
                         */
    {
        return value_;
    }

    virtual Field& operator=(const Field& field) throw (std::bad_cast)
                        /**< @copydoc Core::Field::operator=()
                         * Implementation for std::string type.
                         */
    {
        value(dynamic_cast<const FieldString&>(field).value());
        return *this;
    }

    virtual const bool operator==(const Field& field) const throw (std::bad_cast)
                        /**< @copydoc Core::Field::operator==()
                         * Implementation for std::string type.
                         */
    {
        return (value() == dynamic_cast<const FieldString&>(field).value() 
                && name() == field.name());
    }
};

/** @class FieldTime
 * @brief field of time_t type.
 *
 * Simple class contains name and time_t value.
 */
class FieldTime : public Field {
private:
    time_t value_;
                        /**< @copydoc Core::FieldString::value_ */
protected:
public:
    FieldTime(const std::string& name, const time_t& value = 0)
        throw ():
        Field(TIME, name), value_(value)
                        /**< @brief Constructor.
                         * @param name Name of the field.
                         * @param value Value of the field. Zero by default.
                         */
    {}

    const time_t value(const time_t& value) throw ()
                        /**< @copydoc Core::FieldString::value(value) */
    {
        return value_ = value;
    }

    const time_t value() const throw ()
                        /**< @copydoc Core::FieldString::value() */
    {
        return value_;
    }

    virtual const Field& operator=(const Field& field) throw (std::bad_cast)
                        /**< @copydoc Core::Field::operator=()
                         * Implementation for time_t type.
                         */
    {
        value(dynamic_cast<const FieldTime&>(field).value());
        return *this;
    }

    virtual const bool operator==(const Field& field) const throw (std::bad_cast)
                        /**< @copydoc Core::Field::operator==()
                         * Implementation for time_t type.
                         */
    {
        return (value() == dynamic_cast<const FieldTime&>(field).value()
                && name() == field.name());
    }
};

/** @class FieldEnum
 * @brief Field of std::string type but used for enumeration.
 * @copydetails Core::FieldString
 *
 * It is fully equal to Core::FieldString, but for strong type identification
 * it is copied instead of using typedef. It has done to deny next ways of code:
 *
 * @code
 * Core::FieldString string("some_field");
 * Core::FieldEnum enum("some_enum", "some_value");
 * string = enum;
 * //---- or -------
 * string = dynamic_cast<Core::FieldString>(enum);
 * @endcode
 *
 * But next way is correct:
 *
 * @code
 * Core::FieldString string("some_field");
 * Core::FieldEnum enum("some_enum", "some_value");
 * string.value(enum.value());
 * @endcode
 *
 * Value of this class can not be empty. This class different from
 * Core::FieldString by this.
 */
class FieldEnum : public Field {
private:
    std::string value_;
                        /**< @copydoc Core::FieldString::value_ */
protected:
public:
    FieldEnum(const std::string& name, const std::string& value) throw ():
        Field(ENUM, name), value_(value)
                        /**< @brief Constructor.
                         * @param name Name of the field.
                         * @param value Value of the field.
                         */
    {}

    const std::string& value(const std::string& value) throw (std::bad_cast)
                        /**< @copydoc Core::FieldString::value(const std::string&)
                         * This method throws @c std::bad_cast exception if @a value is empty.
                         */
    {
        if (value.empty())
        {
            throw std::bad_cast();
        }
        return value_ = value;
    }

    const std::string& value() const throw ()
                        /**< @copydoc Core::FieldString::value() */
    {
        return value_;
    }

    virtual const Field& operator=(const Field& field) throw (std::bad_cast)
                        /**< @copydoc Core::FieldString::operator=() */
    {
        value(dynamic_cast<const FieldEnum&>(field).value());
        return *this;
    }

    virtual const bool operator==(const Field& field) const
        throw (std::bad_cast)
                        /**< @copydoc Core::FieldString::operator==() */
    {
        return (value() == dynamic_cast<const FieldEnum&>(field).value()
                && name() == field.name());
    }
};

/** @class FieldLink
 * @brief Link of two objects.
 *
 * Class, contains name, pointer to object and flag (link/unlink).
 * Use to change vectors of objects.
 */
class FieldLink : public Field {
private:
    std::pair<Object *, bool> value_;
                        /**< Object and link flag. */
protected:
public:
    FieldLink(const std::string& name,
                const std::pair<Object *, bool>& value) throw():
        Field(LINK, name), value_(value)
                        /**< @brief Constructor.
                         * @param name Name of the field.
                         * @param value Object and state of link.
                         */
    {}

    
    std::pair<Object *, bool>
    value(const std::pair<Object *, bool>& value) throw()
                        /**< @copydoc Core::FieldString::value(const std::string&) */
    {
        return value_ = value;
    }

    std::pair<Object *, bool>
    value() const throw()
                        /**< @copydoc Core::FieldString::value() */
    {
        return value_;
    }

    virtual const Field& operator=(const Field& field) throw (std::bad_cast)
                        /**< @copydoc Core::Field::operator=()
                         * Implementation for Link type.
                         */
    {
        value(dynamic_cast<const FieldLink&>(field).value());
        return *this;
    }

    virtual const bool operator==(const Field& field) const
        throw (std::bad_cast)
                        /**< @copydoc Core::Field::operator==()
                         * Implementation for Link type.
                         */
    {
        return (value() == dynamic_cast<const FieldLink&>(field).value()
                && name() == field.name());
    }
};

/** @class FieldVector
 * @brief Field of vector type.
 *
 * Class contains name and std::vector<Object *> vector.
 */
class FieldVector : public Field {
private:
    std::vector<Object *> vector_;
                        /**< Vector of objects. */
protected:
public:
    FieldVector(const std::string& name,
                const std::vector<Object *>& vector = std::vector<Object *>())
        throw():
            Field(VECTOR, name), vector_(vector)
                        /**< @brief Constructor.
                         * @param name Name of the field.
                         * @param vector Vector of the objects. Empty by
                         * default.
                         */
    {}

    const std::vector<Object *>&
    vector(const std::vector<Object *>& vector) throw()
                        /**< @brief Change vector.
                         * @param vector New vector.
                         * @return Vector AFTER assigment.
                         */
    {
        return vector_ = vector;
    }

    const std::vector<Object *>& vector() const throw()
                        /**< @brief Get vector.
                         * @return Current vector.
                         *
                         * This method does not change the vector.
                         */
    {
        return vector_;
    }

    virtual const Field& operator=(const Field& field) throw (std::bad_cast)
                        /**< @copydoc Core::Field::operator=() */
    {
        vector(dynamic_cast<const FieldVector&>(field).vector());
        return *this;
    }

    virtual const bool operator==(const Field& field) const throw (std::bad_cast)
                        /**< @copydoc Core::Field::operator==() */
    {
        throw std::bad_cast();
    }

    void add(Object * object)
                        /**< @brief Add object to the vector.
                         * @param object Object to add.
                         */
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
                        /**< @brief Delete object to the vector.
                         * @param object Object to delete.
                         */
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
                        /**< @brief apply link to the vector.
                         * @param field Link to apply.
                         */
    {
        if (field.value().second)
            this->add(field.value().first);
        else
            this->del(field.value().first);
    }
};

}

