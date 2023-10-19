#include "Instructor.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;

int Instructor::instructors = 0;
int Instructor::PZNInstructors = 0;

void Instructor::setPercent(std::string& _title)
{
	rateDict["I"] = 0.4;			// Instructor after un
	rateDict["AI SITN"] = 0.45;		// Assistant Instructor SITN
	rateDict["I SITN"] = 0.5;		// Instructor SITN
	rateDict["AI PZN"] = 0.55;		// Assistant Instructor PZN 
	rateDict["I PZN"] = 0.6;		// Instructor PZN

	percent = rateDict[_title];
}

Instructor::Instructor() : name(""), surname(""), displayedName(name + surname), title(""), percent(0), salary(0), workedHours(0) 
{
	id = instructors + 1;
	instructors++;					// adds every instructor
};

Instructor::Instructor(std::string& _name, std::string& _surname, std::string& _displyedName, std::string& _title)
{
	id = instructors + 1;
	name = _name;
	surname = _surname;
	displayedName = _displyedName;
	title = _title;

	setPercent(title);

	workedHours = 0;				// worked hours 
	salary = 0;						// depends on hourlyRate and amount of people that are taking lesson
	
	instructors++;					// adds every instructor

	if (title == "AI PZN" || title == "I PZN")
	{
		++PZNInstructors;			// add if instructor has PZN title
	}
}

void Instructor::displayData()
{
	cout << "Id:\t\t" << id << endl;
	cout << "Name:\t\t" << name << endl;
	cout << "Surname:\t" << surname << endl;
	cout << "Displayed as:\t" << displayedName << endl;
	cout << "Title:\t\t" << title << endl;
	cout << "Percent:\t" << percent*100 << " %" << endl;
	cout << "Workd hours:\t" << workedHours << " h" << endl;
	cout << "Salary:\t\t" << salary << " PLN" << endl;
}

void Instructor::showInstructors()
{

}

void Instructor::changeData()
{

}
