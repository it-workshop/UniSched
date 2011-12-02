#pragma once

#include <abstractgroup.h>
#include <storage.h>

namespace Core {

class Event: public AbstractGroup {
private:
    const time_t begin_;
    const time_t duration_;

protected:
public:
    Event (const int id, Storage::AbstractStorage& storage,
        const std::string name, const time_t begin, const time_t duration):
            AbstractGroup(id, storage, name), begin_(begin),
            duration_(duration) {}

    const time_t begin() const { return begin_; }
    const time_t duration() const { return duration_; }
    const time_t end() const { return begin_ + duration_; }
};

};

