#ifndef _DATASTORAGE_H_
#define _DATASTORAGE_H_

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "include/person.h"

//	Errors
#define NOERR	0; //UNKNOWN ERROR
//#define LOADERR 1;
//#define SAVEERR 2;
#define SCVERR 3; //SetCellValue()
#define GCVERR 5;
#define UNKNERR 4;
#define LOADERR 6;
#define SAVEERR 7;

using namespace std;

typedef unsigned long long int ulli;

unsigned long long int stoulli(std::string);
int vis(int val,int s);
ulli ullilen(ulli val);
string ullitos(ulli val);

enum PersonAttribute{
    paNAME = 1, paSURNAME, paBIRTH, paFEMALE, paCALENDARID
};
enum GroupAttribute{
    gaNAME = 1, gaDESC, gaCALENDARID
};
enum EventAttribute{
    eaNAME = 1, eaGROUPID, eaBEGIN, eaEND, eaDESC
};

struct CalendarBunch{
    ulli ID;
    ulli EventID;
};
struct GCBunch{
    ulli PersonID;
    ulli GroupID;
    string Status;
};
struct dsrow{
	std::vector<std::string> fields;
};

class TDataStorage{
	public:
		TDataStorage();
		bool CreateTable(int numfields);
		bool AddRow(std::string fields[]);
		bool RemRow(int row);
		std::string GetCellValue(int row, int field);
		bool SetCellValue(int row, int field, std::string);
		int GetLastError(); //Return the code error;

		bool LoadTable(char * filename);
		bool SaveTable(char * filename);

		bool LoadTable(string host, string user, string pass, string bdname);
		bool SaveTable(string host, string user, string pass, string bdname);

        ulli GetNumRows(){return this->_numrows;}
        ulli GetNumFields(){return this->_numfields;}
	private:
		int _numfields;
		int _numrows;

		int _error;

		std::vector< dsrow > _rows;

};

class RDataStorage{
    public:
        virtual bool Load() = 0;
        virtual bool Save() = 0;
        virtual void SetUp(string location, string user, string pass, string bdname) = 0;

        // People
        vector<ulli> GetPersonIDList();

        string GetPersonAttr(PersonAttribute attr, ulli id);
        void SetPersonAttr(PersonAttribute attr, ulli id, string value);

        void AddPerson(ulli id);
        void RemovePerson(ulli id);

        // Group
        vector<ulli> GetGroupIDList();

        string GetGroupAttr(GroupAttribute attr, ulli id);
        void SetGroupAttr(GroupAttribute attr, ulli id, string value);

        void AddGroup(ulli id);
        void RemoveGroup(ulli id);

        // Event
        vector<ulli> GetEventIDList();

        string GetEventAttr(EventAttribute attr, ulli id);
        void SetEventAttr(EventAttribute attr, ulli id, string value);

        void AddEvent(ulli id);
        void RemoveEvent(ulli id);

        // Calendars
        ulli GetNumCalendarBunches();
        CalendarBunch GetCalendarBunch(ulli num);
        void RemoveCalendarBunch(ulli num);
        void AddCalendarBuch(CalendarBunch bnch);

        // Group Content
        ulli GetNumGCBunches();
        GCBunch GetGCBunch(ulli num);
        void RemoveGCBunch(ulli num);
        void AddGCBunch(GCBunch bnch);

    protected:
        TDataStorage _people;
        TDataStorage _groups;
        TDataStorage _events;
        TDataStorage _group_content;
        TDataStorage _calendars;
};
class RFileStorage: public RDataStorage{
    public:
        void SetUp(string, string, string, string);
        bool Load();
        bool Save();
    private:
        string _path;
};
#endif /* _DATASTORAGE_H_ */
