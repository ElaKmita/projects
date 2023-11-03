#include "additionalFunctions.h"

void cinIgnore() {

#pragma push_macro("max")
#undef max
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#pragma pop_macro("max")

}

std::array<std::string, 7> daysOfWeek = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
std::array<std::string, 8> workingHours = { "8AM", "9AM", "10AM", "11AM", "12PM", "13PM", "14PM", "15PM" };

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
