#include <file_storage.h>

using namespace storage;

FileStorage::FileStorage ()
{
}

FileStorage::~FileStorage ()
{
}



void FileStorage::setup(string location, string, string, string)
{
    path_ = location;
}

bool FileStorage::load()
{
    string pth = path_;

    if (!people_.load_table(pth.append("people.csv")))
        return false;
    pth = path_;

    if (!groups_.load_table(pth.append("groups.csv")))
        return false;
    pth = path_;

    if (!events_.load_table(pth.append("events.csv")))
        return false;
    pth = path_;

    if (!group_content_.load_table(pth.append("group_content.csv")))
        return false;
    pth = path_;

    if (!calendars_.load_table(pth.append("calendars.csv")))
        return false;

    return true;
}

bool FileStorage::save()
{
    string pth = path_;

    people_.save_table(pth.append("people.csv"));
    pth = path_;

    groups_.save_table(pth.append("groups.csv"));
    pth = path_;

    events_.save_table(pth.append("events.csv"));
    pth = path_;

    group_content_.save_table(pth.append("group_content.csv"));
    pth = path_;

    calendars_.save_table(pth.append("calendars.csv"));
    pth = path_;

    return true;
}


