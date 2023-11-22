#pragma once

#include <mysql.h>
#include <sstream>

// Connection with MySQL

#define HOST "127.0.0.1"
#define USER "root"
#define PASS					/*put the password of MySQL in here between ""*/
#define DATABASE "skischool"	/*put the name of database in here between ""*/
#define PORT 3306

// MYSQL - declaration 

extern MYSQL* connection;
extern MYSQL_RES* res_set;
extern MYSQL_ROW row;

extern std::stringstream stmt;
extern const char* q;
extern std::string query;