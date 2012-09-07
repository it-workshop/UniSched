/** @file
 * @brief Core::Event class implementation.
 * @author Derbenev Aleksander
 * @date 2011-2012
 */

#include <event.h>

using namespace Core;

void Event::check_field(const std::string& name, const boost::any& value) const
    throw (boost::bad_any_cast)
{
    AbstractGroup::check_field(name, value);
    if ("begin" == name || "duration" == name)
    {
        boost::any_cast<time_t>(value);
        return;
    }
}

