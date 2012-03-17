#include <iostream>

#include "../paths.hpp"

#include <abstractui.h>

#include "yaml.h"

class FileStorage : public Core::AbstractStorage {
private:
    inline void link(const std::map<Core::Object *, std::vector<Core::objid_t>>& connections);
                        /**< @brief Connects sequence of objects from
                         * the UI to a sequence of sequences of other UI's
                         * objects.
                         * @param [in] map with connections.
                         *
                         * This method expects a map as input data format, 
                         * containing pairs: (objid_t A, vector<objid_t> B),
                         * where object with id A connects all objects with
                         * ids from vector B.
                         */
                         
     Core::Object * find_object(const Core::objid_t key_id);

public:
    FileStorage(std::vector<Module *>* modules, void *handle);
    
    void dump(const std::string& dbase_fname);
    bool load(const std::string& dbase_fname);
    
    void push(const Core::objid_t id, const std::string& name, const boost::any& value);
    void connect();
    void disconnect();
    void create(const Core::Object *object);
    void remove(const Core::objid_t id);
    
    
    void init (const std::vector<std::string>& args);
};

