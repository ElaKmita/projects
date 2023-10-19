#pragma once
#include <string>
#include <map>

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
	static int instructors;			// counts every instructor
	static int PZNInstructors;		// counts instructors that have PZN title

	std::map<std::string, double> rateDict;		// dictionary with title-rate dependencies

	void setPercent(std::string&);	// sets percent - depends on title

public:
	Instructor();																	// default constructor
	Instructor(std::string& _name, std::string&, std::string&, std::string&);		// parametrized constructor

	int getId() { return id; }
	std::string getName() { return name; }
	std::string getSurname() { return surname; }
	std::string getDisplayedName() { return displayedName; }
	std::string getTitle() { return title; }
	double getPertcent() { return percent; }
	int getWorkedHours() { return workedHours; }
	int getSalary() { return salary; }
	static int getInstAmount() { return instructors; }	// returns amount of all instructors
	static int getPZNInstAmount() { return PZNInstructors; }

	void displayData();				// shows instructor's data
	void showInstructors();			// shows all instructors existing in database
	void changeData();				// modifies selected instructor's data
};

