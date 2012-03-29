#pragma once

#include <vector>
#include <string>
#include <string.h>

#include <iconv.h>

namespace Core {

/** @class Module
 * @brief An abstract class for module.
 *
 * Every module must be an shared object which contains static objec of
 * class implementing this one.
 */
class Module {
public:
    /** @enum Type
     * @brief Provides module type identification without typeid operator.
     */
    enum Type {
        STORAGE,
        UI
    };

private:
    const Type type_;
                        /**< Type of the module.
                         * @internal Use in the type() method and constructor
                         * only.
                         */
    const std::wstring name_;
                        /**< Name of the module.
                         * @internal Use in the name() method and constructor
                         * only.
                         */
    void *handle_;

    iconv_t in_conv_;
    iconv_t out_conv_;

protected:
    void init_iconv(const std::string& codeset) {
        in_conv_ = iconv_open("UTF-32", codeset.c_str());
        out_conv_ = iconv_open(codeset.c_str(), "UTF-32");
    }

    char * iconv(wchar_t *string)
    {
        size_t length = wcslen(string)*4+1;
        size_t out_size = length;
        char *output = new char[length];
        ::iconv(out_conv_, (char **)&string, &length, &output, &out_size);
        char *ret = const_cast<char *>(std::string(output).c_str());
        delete output;
        return ret;
    }
    const char * iconv(const wchar_t *string)
    {
        return iconv(const_cast<wchar_t *>(string));
    }
    char * iconv(std::wstring& string)
    {
        return iconv(const_cast<wchar_t *>(string.c_str()));
    }
    const char * iconv(const std::wstring& string)
    {
        return iconv(const_cast<wchar_t *>(string.c_str()));
    }
    wchar_t * iconv(char *string)
    {
        size_t length = strlen(string)+1;
        size_t out_size = length+1;
        wchar_t *output = new wchar_t[length];
        ::iconv(in_conv_, &string, &length, (char **)&output, &out_size);
        wchar_t *ret = const_cast<wchar_t *>(std::wstring(output).c_str());
        delete output;
        return ret;
    }
    const wchar_t * iconv(const char *string)
    {
        return iconv(const_cast<char *>(string));
    }
    wchar_t * iconv(std::string& string)
    {
        return iconv(const_cast<char *>(string.c_str()));
    }
    const wchar_t * iconv(const std::string& string)
    {
        return iconv(const_cast<char *>(string.c_str()));
    }

    void deinit_iconv() {
        iconv_close(in_conv_);
        iconv_close(out_conv_);
    }

public:
    Module (const enum Type type, const std::wstring& name,
            std::vector<Module *>* modules, void *handle);
                        /**< @brief Constructor.
                         * @param [in] type Type of the module.
                         * @param [in] name Name of the module.
                         * @param [in] modules Collection of modules.
                         * @param [in] handle Handle of the module.
                         * @internal use only in the classes implementing this 
                         * one.
                         */
    
    virtual void init(const std::vector<std::wstring>& args) = 0;
                        /**< @brief Initilize required resources. Such as memory,
                         * shared objects, create auxiliary objects, etc.
                         * @param [in] args Command line program arguments.
                         */

    const Type type() const throw ()
                        /**< @brief Get type of the module.
                         * @return Type identificator.
                         */
    {
        return type_;
    }

    const std::wstring& name() const throw()
                        /**< @brief Get name of the module.
                         * @return Name of the module.
                         */
    {
        return name_;
    }

    static void unload_modules();
    static void load_modules();
    static std::vector<Module *> * modules();
};

}

