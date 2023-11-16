#pragma once

#include <iostream>
#include <map>
#include <sstream>
#include <iomanip>

#include "mysqlConnection.h"
#include "additionalFunctions.h"

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

	double setPercent(std::string&);	// sets percent - depends on title

public:
	void addInstructor();			// adds new instructor to the database
	void displayAll();				// displays all instructors
	void findInstructor();			// finds instructor in the database
	void modifyData();				// modifies instructor's data
	void deleteInstructor();		// deletes instructor from database
	// void countPZNInstructors;	// counts instructors with PNZ title
	void checkAvailability();
	void changeAvailability();		// changes instructor's availability
};

// functions' declarations
void displayIndividualView(MYSQL_ROW& row);
void displayTableView();
void modification(std::string colName, std::string newVal, int id);
void instModificationMenu();
void isInstrKnown(Instructor* instr);
void initializeAvailability();
void deleteAvailability(const int& id);
void showAvailability(const int& id);
void sendQuery(std::string successAnnouncement);
void sendMultiQuery(std::string successAnnouncement);
void weekChange(const int& id);
void dayChange(const int& id);
void hourChange(const int& id);
int checkifSkiInstructorExist(const int& instrId);
