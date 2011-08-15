#ifndef  _GLOBAL_NAMESPACE_
#define _GLOBAL_NAMESPACE_
// _________________________________
 /*                                  \
 |  This file is created to provide  |
 |  developer of the project access  |
 |  to all of required types and     |
 |  namespaces. Please use it        |
 |  carefully.                       |
 |            Created by Arsh, 2011  |
 \_________________________________ */
                                     //
/** @typedef id_t unsigned long long int */
typedef unsigned long long id_type;
/** @typedef Group_Content @struct Group_Content_ */
typedef struct Group_Content_ Group_Content;

class Person;
class Event;
class Group;
class Calendar;
class Queue;
class UserInterface;

namespace uiconsole {
    class Command;
    class Command_Add;
    class Command_All;
    class Command_Clone;
    class Command_Exclude;
    class Command_Exit;
    class Command_Help;
    class Command_Include;
    class Command_Link;
    class Command_Merge;
    class Command_Print;
};

#endif /* _GLOBAL_NAMESPACE_ */

