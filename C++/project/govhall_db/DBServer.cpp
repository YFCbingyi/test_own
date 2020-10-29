#include <iostream>

#include "DBServer.h"


DBServer::DBServer(const std::string& path):path_(path_)
{
}

DBServer::~DBServer()
{
}

bool DBServer::fixData(int start,int end,int px,int py) {
    std::string sqlstr =  "SELECT Pos,ID FROM Facilities where ID > " + std::to_string(start) + " and ID < end;";
	std::cout << sqlstr << std::endl;

	sqlite3pp::database db(local_db_path_.c_str());
	sqlite3pp::query qry(db, sqlstr.c_str());
	
	sqlite3pp::query::iterator i = qry.begin(); 
	for (; i != qry.end(); ++i) {
		present_id = (*i).get<int>(0);  
		return true;
	}

	return false;

	TRY_END();

	return false;

}