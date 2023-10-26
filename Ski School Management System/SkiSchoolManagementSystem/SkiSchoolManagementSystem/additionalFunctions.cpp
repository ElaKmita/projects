#include "additionalFunctions.h"


// make string upper case
void upperCase(std::string& str)
{
	for (char& ch : str) {
		ch = std::toupper(ch);
	}
}


// make string capitalize
void capitalize(std::string& str)
{
	if (!str.empty())						// check if string is not empty
	{
		str[0] = std::toupper(str[0]);		// change first letter for the upper case
		
		if (str.size() > 1)					// check if str contains more than one leter
		{
			std::transform(str.begin() + 1, str.end(), str.begin() + 1, ::tolower);		// change other letters to lower
		}
	}
}
