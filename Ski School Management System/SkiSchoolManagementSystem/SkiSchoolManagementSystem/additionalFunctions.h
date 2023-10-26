#pragma once

#include <iostream>
#include <algorithm>

inline void pressToContinue()
{
	std::cout << "\n\nPress Enter to continue... ";
	getchar();
}

void upperCase(std::string& str);		// make string upper case
void capitalize(std::string& str);		// make string capitalize