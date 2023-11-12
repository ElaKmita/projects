#pragma once

#include <iostream>
#include <algorithm>
#include <array>

#include "mysqlConnection.h"

using std::cout;
using std::cin;
using std::endl;

// sendQuery - function that should be used when only one query is sent
void sendQuery(std::string successAnnouncement);
void sendQuery(std::string successAnnouncement, bool& isTrue);

// sendMuliQuery - function that should be used when more than one query is sent
void sendMultiQuery(std::string successAnnouncement);

void cinIgnore();

extern std::array<std::string, 7> daysOfWeek;
extern std::array<std::string, 8> workingHours;

inline void pressToContinue()
{
	cinIgnore();
	std::cout << "\n\nPress Enter to continue... ";
	getchar();
}

void upperCase(std::string& str);		// make string upper case
void capitalize(std::string& str);		// make string capitalize