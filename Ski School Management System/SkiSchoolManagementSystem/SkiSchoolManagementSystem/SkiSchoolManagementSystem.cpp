#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <conio.h>
#include <cstdlib>

#include "menu.h"

// Connection with MySQL - definition

MYSQL* connection;			
MYSQL_RES* res_set;
MYSQL_ROW row;

std::stringstream stmt;
const char* q;
std::string query;

int main()
{
	// connection initialization
	connection = mysql_init(0);
	connection = mysql_real_connect(connection, HOST, USER, PASS, DATABASE, PORT, NULL, 0);
	mysql_set_server_option(connection, MYSQL_OPTION_MULTI_STATEMENTS_ON);		// enables sending more than one statemet to SQL 

	/*
	if (connection) {
		cout << "Successful connection to database!" << endl;
	}
	else {
		cout << "Connection to database failed: " << mysql_error(connection) << endl;
	}
	*/

	mainMenu();
}

