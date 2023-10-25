#pragma once

#include <iostream>
#include <list>

class Instructor
{
private:
	int id;
	std::string name;
	std::string surname;
	std::string displayedName;
	std::string title;
	double percent;					// depends on title 
	int workedHours;				// worked hours 
	int salary;						// depends on percent and amount of people that are taking lesson

	// std::list<std::string> titles{ "I", "AI SITN", "I SITN", "AI PZN", "I PZN" };		// list with all available titles 

	double setPercent(std::string&);	// sets percent - depends on title

public:
	void addInstructor();			// adds new instructor to the database
	void displayAll();				// displays all instructors
	void findInstructor();			// finds instructor in the database
	void modifyData();				// modifies instructor's data
	void deleteInstructor();		// deletes instructor from database
	// void countPZNInstructors;	// counts instructors with PNZ title
};

