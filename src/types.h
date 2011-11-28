
#pragma once

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
class Event_Template;
class Group;
class Calendar;
class Queue;
class Event_Template;
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

namespace storage {
    enum Errors {
        NO_ERR,
        SET_CELL_VALUE_ERR,
        GET_CELL_VALUE_ERR,
        UNKOWN_ERR,
        LOAD_ERR,
        SAVE_ERR
    };

    enum PersonAttribute {
        paNAME = 1,
        paSURNAME,
        paBIRTHDAY,
        paSEX
    };

    enum GroupAttribute {
        gaNAME = 1,
        gaDESCRIPTION,
        gaCALENDAR
    };

    enum EventAttribute {
        eaNAME = 1,
	eaGROUP,
        eaBEGIN, 
        eaEND,
        eaDESCRIPTION
    };

    enum EventTemplateAttribute {
        taNAME = 1,
        taSCRIPT,
	taDURATION
    };

    enum QueueAttribute {
        qaNAME = 1
    };

    class TableDataStorage;
    class DataStorage;
    class FileStorage;

    typedef struct QueueBunch_ QueueBunch;
    typedef struct GroupBunch_ GroupBunch;
    typedef struct CalendarBunch_ CalendarBunch;
    typedef struct dsrow_ dsrow;
};

