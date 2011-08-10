#include "DataStorage.h"
#include "malloc.h"
//#define Печенье_лом 1
int vis(int val,int s){
    if(s==0)return 1;
    if(s==1)return val;
    int res=val;
    for(int i=0; i<s-1; i++){
        res*=val;
    }

    return res;
}
unsigned long long int stoulli(std::string str){
    unsigned long long int res = 0;
    for(int i = 0; i < (int)str.size(); i++){
        res+=(str[i] - '0') * vis(10, (int)str.size()-i-1);
    }
    return res;
}
ulli ullilen(ulli val){
    for(ulli k = 0; ; k++){
        val /=10;
        if(val==0) return k+1;
    }
}
string ullitos(ulli val){
    string res="";
    string app="A";
    ulli cc = 0;
    for(ulli i = ullilen(val); i > 0; i--){
        cc = val%10;
        //cout<<i;
        val/=10;
        app[0] = cc + '0';
        app[1] = '\0';
        res.append(app);
    }
    string res2 = "";
    for(int i = res.length()-1; i >= 0; i--){
        app[0] = res[i];
        app[1] = '\0';
        res2.append(app);
    }
    return res2;
}
bool stob(std::string str){
    if(str == "false" || str == "FALSE"){
        return false;
    }
    else
        return true;
}


// TDATASTORAGE //
TDataStorage::TDataStorage(){
	this->_numfields = 0;
	this->_numrows = 0;
	this->_error = 0;
	return;
}
int TDataStorage::GetLastError(){
	return this->_error;
}
bool TDataStorage::CreateTable(int numfields){
	this->_numfields = numfields;

	std::vector<dsrow> tempr;

	this->_rows = tempr;

	return true;
}
bool TDataStorage::AddRow(std::string fields[]){
	dsrow nrow;
	for(int i=0; i<this->_numfields; i++){
		nrow.fields.push_back(fields[i]);
	}
	this->_rows.push_back(nrow);
	this->_numrows++;
	return true;
}
std::string TDataStorage::GetCellValue(int row, int field){
	if(row>=this->_numrows || field>=this->_numfields){
		this->_error = GCVERR;
		return "GCVERR";
	}
	return this->_rows[row].fields[field];
}
bool TDataStorage::SetCellValue(int row, int field, std::string value){
	if(row>=this->_numrows || field>=this->_numfields){
		this->_error = SCVERR;
		return false;
	}
	this->_rows[row].fields[field] = value;
	return true;
}
bool TDataStorage::LoadTable(char * filename){
	FILE * lt = fopen(filename, "r");
	if(lt==NULL){
	    this->_error = SAVEERR;
	    return false;
	}
	dsrow * rw = new dsrow();
	std::string str;
	std::string tsym = " ";
	//fgetws(str, 10, lt);
	while(true){
	    tsym[0] = fgetc(lt);

	    if(tsym[0] == EOF)break;
	    if(tsym[0] == ';' || tsym[0] == ','){
            rw->fields.push_back(str);
            //std::cout<<"fields.push_back("<<str<<")\n";
            str="";
            tsym[0] = fgetc(lt);
	    }
	    if(tsym[0] == '\n'){
	        rw->fields.push_back(str);
	        //std::cout<<"fields.push_back("<<str<<")\nediting the row was finished\n";
            str="";
	        this->_rows.push_back(*rw);
            rw = new dsrow();
            tsym[0] = fgetc(lt);
	    }
	    if(tsym[0]!='\"')
            str.append(tsym);
	}
	//std::cout<<str<<std::endl;
    this->_numfields = this->_rows[0].fields.size();
    this->_numrows = this->_rows.size();
	return true;
}

bool TDataStorage::SaveTable(char * filename){
    FILE * lt = fopen(filename, "w");
    std::string str="";
    for(int i = 0; i < this->_numrows; i++){
        for(int d = 0; d < this->_numfields; d++){
            str = this->_rows[i].fields[d];
            fputs(str.c_str(), lt);
            if(d<this->_numfields-1)fputc(';', lt);
        }
        fputc('\n', lt);
    }
    return true;
}

bool TDataStorage::RemRow(int row){
    for(int i = row; i < this->_numrows-1; i++){
        this->_rows[i] = this->_rows[i+1];
    }
    this->_rows.resize(this->_numrows-1);
    this->_numrows--;
    return true;
}

// RDATASTORAGE

void RFileStorage::SetUp(string loc, string, string, string){
    this->_path = loc;
}

bool RFileStorage::Load(){
    std::string pth = this->_path;

    this->_people.LoadTable((char*)pth.append("people.csv").c_str());
    pth = this->_path;
    this->_groups.LoadTable((char*)pth.append("groups.csv").c_str());
    pth = this->_path;
    this->_events.LoadTable((char*)pth.append("events.csv").c_str());
    pth = this->_path;
    this->_group_content.LoadTable((char*)pth.append("group_content.csv").c_str());
    pth = this->_path;
    this->_calendars.LoadTable((char*)pth.append("calendars.csv").c_str());
    pth = this->_path;

    return true;
}
bool RFileStorage::Save(){
    string pth = this->_path;

    this->_people.SaveTable((char*)pth.append("people.csv").c_str());
    pth = this->_path;
    this->_groups.SaveTable((char*)pth.append("groups.csv").c_str());
    pth = this->_path;
    this->_events.SaveTable((char*)pth.append("events.csv").c_str());
    pth = this->_path;
    this->_group_content.SaveTable((char*)pth.append("group_content.csv").c_str());
    pth = this->_path;
    this->_calendars.SaveTable((char*)pth.append("calendars.csv").c_str());
    pth = this->_path;

    return true;
}
ulli FindNumRow(TDataStorage table, ulli id){
    for(ulli i = 0; i<table.GetNumRows(); i++){
        if(stoulli(table.GetCellValue(i, 0))==id){
            return i;
        }
    }
    return 0;
}
string RDataStorage::GetPersonAttr(PersonAttribute attr, ulli id){
    return this->_people.GetCellValue(FindNumRow(this->_people, id), attr);
}
void RDataStorage::SetPersonAttr(PersonAttribute attr, ulli id, string value){
    this->_people.SetCellValue(FindNumRow(this->_people, id), attr, value);
}
string RDataStorage::GetGroupAttr(GroupAttribute attr, ulli id){
    return this->_groups.GetCellValue(FindNumRow(this->_groups, id), attr);
}
void RDataStorage::SetGroupAttr(GroupAttribute attr, ulli id, string value){
    this->_groups.SetCellValue(FindNumRow(this->_groups, id), attr, value);
}
string RDataStorage::GetEventAttr(EventAttribute attr, ulli id){
    return this->_events.GetCellValue(FindNumRow(this->_events, id), attr);
}
void RDataStorage::SetEventAttr(EventAttribute attr, ulli id, string value){
    this->_events.SetCellValue(FindNumRow(this->_events, id), attr, value);
}

void RDataStorage::AddPerson(ulli id){
    string flds[this->_people.GetNumRows()];
    flds[0] = ullitos(id);
    for(ulli i = 1; i < this->_people.GetNumRows(); i++)
        flds[i] = "";

    this->_people.AddRow(flds);
}
void RDataStorage::AddGroup(ulli id){
    string flds[this->_groups.GetNumRows()];
    flds[0] = ullitos(id);
    for(ulli i = 1; i < this->_groups.GetNumRows(); i++)
        flds[i] = "";

    this->_groups.AddRow(flds);
}
void RDataStorage::AddEvent(ulli id){
    string flds[this->_events.GetNumRows()];
    flds[0] = ullitos(id);
    for(ulli i = 1; i < this->_events.GetNumRows(); i++)
        flds[i] = "";

    this->_events.AddRow(flds);
}

void RDataStorage::RemovePerson(ulli id){
    this->_people.RemRow(FindNumRow(this->_people, id));
}
void RDataStorage::RemoveGroup(ulli id){
    this->_groups.RemRow(FindNumRow(this->_groups, id));
}
void RDataStorage::RemoveEvent(ulli id){
    this->_events.RemRow(FindNumRow(this->_events, id));
}

vector<ulli> RDataStorage::GetPersonIDList(){
    vector<ulli> ids;
    for(ulli i = 0; i<this->_people.GetNumRows(); i++){
        ids.push_back(stoulli(this->_people.GetCellValue(i, 0)));
    }
    return ids;
}
vector<ulli> RDataStorage::GetEventIDList(){
    vector<ulli> ids;
    for(ulli i = 0; i<this->_events.GetNumRows(); i++){
        ids.push_back(stoulli(this->_events.GetCellValue(i, 0)));
    }
    return ids;
}
vector<ulli> RDataStorage::GetGroupIDList(){
    vector<ulli> ids;
    for(ulli i = 0; i<this->_groups.GetNumRows(); i++){
        ids.push_back(stoulli(this->_groups.GetCellValue(i, 0)));
    }
    return ids;
}

ulli RDataStorage::GetNumCalendarBunches(){
    return this->_calendars.GetNumRows();
}
CalendarBunch RDataStorage::GetCalendarBunch(ulli num){
    CalendarBunch res;
    res.ID = stoulli(this->_calendars.GetCellValue(num, 0));
    res.EventID = stoulli(this->_calendars.GetCellValue(num, 1));
    return res;
}
void RDataStorage::RemoveCalendarBunch(ulli num){
    this->_calendars.RemRow(num);
}
void RDataStorage::AddCalendarBuch(CalendarBunch bnch){
    string flds[2];
    flds[0] = ullitos(bnch.ID);
    flds[1] = ullitos(bnch.EventID);
    this->_calendars.AddRow(flds);
}


ulli RDataStorage::GetNumGCBunches(){
    return this->_group_content.GetNumRows();
}
GCBunch RDataStorage::GetGCBunch(ulli num){
    GCBunch res;
    res.PersonID = stoulli(this->_group_content.GetCellValue(num, 0));
    res.GroupID = stoulli(this->_group_content.GetCellValue(num, 1));
    res.Status = this->_group_content.GetCellValue(num, 2);
    return res;
}
void RDataStorage::RemoveGCBunch(ulli num){
    this->_group_content.RemRow(num);
}
void RDataStorage::AddGCBunch(GCBunch bnch){
    string flds[3];
    flds[0] = ullitos(bnch.PersonID);
    flds[1] = ullitos(bnch.GroupID);
    flds[2] = bnch.Status;
    this->_group_content.AddRow(flds);
}
