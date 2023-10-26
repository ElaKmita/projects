#pragma once

#include <mysql.h>
#include <sstream>

// Connection with MySQL

#define HOST "127.0.0.1"
#define USER "root"
#define PASS "2_KLZBRMQ1_pass" /*put the password of MySQL in here between ""*/
#define DATABASE "skischool"
#define PORT 3306
//#define PASSWORD 1234 /*Set a Numeric Password for Your Application

// MYSQL - declaration 

extern MYSQL* connection;
extern MYSQL_RES* res_set;
extern MYSQL_ROW row;

extern std::stringstream stmt;
extern const char* q;
extern std::string query;