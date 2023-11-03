#pragma once

#include <iostream>
#include <algorithm>
#include <array>

void cinIgnore();

extern std::array<std::string, 7> daysOfWeek;
extern std::array<std::string, 8> workingHours;

inline void pressToContinue()
{
	std::cout << "\n\nPress Enter to continue... ";
	getchar();
}

void upperCase(std::string& str);		// make string upper case
void capitalize(std::string& str);		// make string capitalize