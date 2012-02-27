#pragma once

#include <object.h>
#include <manager.h>

#include <module.h>

/** @namespace UI
 * @brief UserInterface Objects.
 */
namespace UI {

/** @class AbstractUI
 * @brief Interface for frontend modules.
 */
class AbstractUI: public Module {
private:
    Core::Manager manager_;
                        /**< Manager of the objects. */
    std::vector<Core::Object *> cache_;
                        /**< Search cache. */
protected:
    std::vector<Core::Object *>& cache()
                        /**< @brief Get search cache.
                         * @return Search cache.
                         * @internal For this and inherited classes only.
                         */
    {
        return cache_;
    }

    void search(const std::vector<const Core::Field *>& parameters)
                        /**< @brief Find objects by parameters and store into
                         * the search cache.
                         * @param parameters Search parameters.
                         * @internal For this and inherited classes only.
                         *
                         * Default search algorithm in Core::Manager class
                         * looks for objects that are suitable for all
                         * parameters it can be changed later.
                         *
                         * @see Core::Manager::search()
                         */
    {
        auto tmp = manager_.search(parameters);

        for (Core::Object * object: tmp)
        {
            cache_.push_back(object);
        }
    }

    template <class T>
    void create(const std::vector<const Core::Field *>& parameters)
                        /**< @brief Tell manager to create object of T class and
                         * with given parameters.
                         * @param parameters Fields of new object.
                         * @internal For this and inherited classes only.
                         *
                         * If class T is not inherited from Core::Object then
                         * call of this method will fail program build.
                         */
    {
        cache_.push_back(manager_.create<T>());
    }

    void remove(Core::Object * object)
                        /**< @brief Tell manager to delete object.
                         * @param object Object to delete.
                         * @internal For this and inherited classes only.
                         *
                         * Manager deletes all links with other objects, object
                         * and pointer to the object in the internal collection.
                         */
    {
        for (auto it = cache_.begin(); it != cache_.end(); it++)
        {
            if (*it == object)
            {
                cache_.erase(it);
                manager_.remove(object);
                return;
            }
        }
    }

    void reset_cache() throw ()
                        /**< @brief Clears search cache.
                         * @internal For this and inherited classes only.
                         *
                         * Delete all information about objects from the cache.
                         */
    {
        cache_.clear();
    }

public:

    AbstractUI (const std::string& name):
        Module(Module::UI, name)
                        /**< @brief constructor.
                         * @param name Name of the frontend.
                         */
    {}

    Core::Manager& manager() throw ()
                        /**< @brief Get manager of objects.
                         * @return Manager object.
                         */
    {
        return manager_;
    }

    virtual int run() = 0;
                        /**< @brief Main method of frontend class. It is called
                         * from main.
                         * @return Program return code.
                         */
};

};

