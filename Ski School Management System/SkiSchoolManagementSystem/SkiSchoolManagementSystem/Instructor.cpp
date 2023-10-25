#include <iostream>
#include <map>
#include <sstream>
#include <iomanip>

#include "Instructor.h"
#include "mysqlConnection.h"

using std::cout;
using std::cin;
using std::endl;

// functions' declarations

void upperCase(std::string& str);
void displayIndividualView(MYSQL_ROW& row);
void displayTableView();
void modification(std::string colName, std::string newVal, int id);
void instModificationMenu();
void isInstrKnown(Instructor* instr);


// Instructor's methods

double Instructor::setPercent(std::string& _title)
{
	std::map<std::string, double> rateDict;		// dictionary with title-rate dependencies
	rateDict["I"] = 0.4;			// Instructor after un
	rateDict["AI SITN"] = 0.45;		// Assistant Instructor SITN
	rateDict["I SITN"] = 0.5;		// Instructor SITN
	rateDict["AI PZN"] = 0.55;		// Assistant Instructor PZN 
	rateDict["I PZN"] = 0.6;		// Instructor PZN

	return rateDict[_title];		// returns percent that depends on title
}

void Instructor::addInstructor()
{
	cout << "\nEnter data\n";
	cout << "Name: ";
	std::getline(cin, name);
	cout << "Surname: ";
	std::getline(cin, surname);
	cout << "Displayed name: ";
	std::getline(cin, displayedName);
	cout << "Title (I, AI SITN, I SITN, AI PZN, I PZN): ";
	std::getline(cin, title);
	upperCase(title);

	while (title != "I" && title != "AI SITN" && title != "I SITN" && title != "AI PZN" && title != "I PZN")
	{
		cout << "Incorrect title \nChoose one of the given options\n";
		cout << "Title (I, AI SITN, I SITN, AI PZN, I PZN): ";
		std::getline(cin, title);
		upperCase(title);
	}
	percent = setPercent(title);

	stmt.str("");
	stmt << "INSERT INTO instructor(name, surname, displayedName, title, percent) VALUES('" << name << "','" << surname << "','" << displayedName << "','" << title << "', " << percent << ");";
	query = stmt.str();				// convert to string
	q = query.c_str();				// convert to const char *

	if (mysql_query(connection, q) == 0)			// mysql_query - sends query to the database
	{
		cout << endl << endl << "New Instructor Inserted Successfully" << endl << endl << endl;
	}
	else {
		cout << endl << endl << "Entry ERROR !" << endl << "Contact Technical Team " << endl << endl << endl;
	}
}

void Instructor::displayAll()
{
	std::string query = "SELECT * FROM instructor;";
	q = query.c_str();
	mysql_query(connection, q);
	res_set = mysql_store_result(connection);

	char ans;
	cout << "\nDisplay views:\n";
	cout << "1. Individual View\n2. Table View\n\n";
	cout << "Select display view: ";
	cin >> ans;

	switch (ans)
	{
	case '1':
	{
		cout << "\n--- INSTRUCTORS ---\n";
		while ((row = mysql_fetch_row(res_set)) != NULL)
		{
			displayIndividualView(row);
		}
		break;
	}
	case '2':
		displayTableView();
		break;
	default:
		displayTableView();
		break;
	}
	cout << endl;
}

void Instructor::findInstructor()
{
	std::string searchData;
	cout << "\nEnter search data (name or surname or displayed name): ";
	std::getline(cin, searchData);
	stmt.str("");
	stmt << "SELECT * FROM instructor WHERE name = '" << searchData << "' OR surname = '" << searchData << "' OR displayedName = '" << searchData << "';";
	query = stmt.str();
	q = query.c_str();
	mysql_query(connection, q);
	res_set = mysql_store_result(connection);

	bool match = false;
	while ((row = mysql_fetch_row(res_set)) != NULL)
	{
		match = true;
		displayIndividualView(row);
	}
	cout << (match ? "\n" : "\nNo items match your search\n\n");
}

void Instructor::modifyData()
{
	char ans;
	cout << "\nModyfying instructor data\n\n";
	isInstrKnown(this);
	cout << endl << "Enter instructor id: ";
	cin >> id;
	instModificationMenu();
	//cin >> ans;
	std::string column, newValue;
	while (cin >> ans)		// ans != '0'
	{
		switch (ans)
		{
		case '0':
			break;
		case '1':
		{
			cin.get();
			column = "name";
			cout << "Enter new name: ";
			std::getline(cin, newValue);
			modification(column, newValue, id);
			break;
		}
		case '2':
		{
			cin.get();
			column = "surname";
			cout << "Enter new surname: ";
			std::getline(cin, newValue);
			modification(column, newValue, id);
			break;
		}
		case '3':
		{
			cin.get();
			column = "displayedName";
			cout << "Enter new displayed name: ";
			std::getline(cin, newValue);
			modification(column, newValue, id);
			break;
		}
		case '4':
		{
			cin.get();
			column = "title";
			cout << "Enter new title (I, AI SITN, I SITN, AI PZN, I PZN): ";
			std::getline(cin, newValue);
			upperCase(newValue);

			while (newValue != "I" && newValue != "AI SITN" && newValue != "I SITN" && newValue != "AI PZN" && newValue != "I PZN")
			{
				cout << "Incorrect title \nChoose one of the given options\n";
				cout << "Title (I, AI SITN, I SITN, AI PZN, I PZN): ";
				std::getline(cin, newValue);
				upperCase(newValue);
			}
			percent = setPercent(newValue);
			modification(column, newValue, id);
			modification("percent", std::to_string(percent), id);
			break;
		}
		default:
			cout << "Incorrect number\n\n";
			break;
		}

		if (ans == '0')
		{
			cout << endl << endl;
			break;
		}

		instModificationMenu();
	}
}

void Instructor::deleteInstructor()
{
	char ans;
	cout << "\nRemoving instructor from the database\n\n";
	isInstrKnown(this);
	cout << endl << "Enter instructor id: ";
	cin >> id;
	cout << endl << "Are you sure that you want delete this instructor? (y/n) ";
	cin >> ans;
	if (ans == 'y')
	{
		stmt.str("");
		stmt << "DELETE FROM instructor WHERE id = " << id << ";";
		query = stmt.str();
		q = query.c_str();
		if (mysql_query(connection, q) == 0)			// mysql_query - sens query to the database
		{
			cout << endl << endl << "Instructor Deleted Successfully" << endl << endl << endl;
		}
		else {
			cout << endl << endl << "Entry ERROR !" << endl << "Contact Technical Team " << endl << endl << endl;
		}
	}
	else
	{
		cout << "\nInstructor has not been deleted\n\n";
	}
}


// additional functions

void upperCase(std::string& str)
{
	for (char& ch : str) {
		if (std::islower(ch))
			ch = std::toupper(ch);
	}
}

void displayIndividualView(MYSQL_ROW& row)			// displays instructors' data in individual view
{
	cout << endl;
	cout << "Id\t\t" << row[0] << endl;
	cout << "Name:\t\t" << row[1] << " " << row[2] << endl;
	cout << "Displayed as:\t" << row[3] << endl;
	cout << "Title:\t\t" << row[4] << endl;
	cout << "Worked hours:\t" << row[6] << endl;
	cout << "Salary:\t\t" << row[7] << endl;
}

void displayTableView()				// displays instructors' data in table view
{
	cout << "\n\n\t" << std::setw(54) << "--- INSTRUCTORS--- \n\n";
	cout << "\t" << std::left << std::setw(8) << "Id" << std::setw(20) << "Name" << std::setw(20) << "Surname" << std::setw(20) << "Displayed name" << std::setw(10) << "Title" << std::setw(8) << "h" << std::setw(8) << "PLN" << endl << endl;
	while ((row = mysql_fetch_row(res_set)) != NULL)
	{ 
		cout << "\t" << std::left << std::setw(8) << row[0] << std::setw(20) << row[1] << std::setw(20) << row[2] << std::setw(20) << row[3] << std::setw(10) << row[4] << std::setw(8) << row[6] << std::setw(8) << row[7];
		cout << endl;
	}
}

void instModificationMenu()
{
	cout << endl << "- Data -\n";
	cout << "1. Name" << endl;
	cout << "2. Surname" << endl;
	cout << "3. Displayed name" << endl;
	cout << "4. Title" << endl;
	cout << "0. END MODIFICATION";
	cout << "\n\nChoose the data that you want modify (1-4), press 0 to escape: ";
}

void isInstrKnown(Instructor* instr)
{
	char ans;
	cout << "Do you know instructor id? (y/n) ";
	cin >> ans;
	if (ans == 'n')
	{
		char num;
		cout << "\n1. Find instructor\n2. Display all\n\nChoose option: ";
		cin >> num;
		switch (num)
		{
		case '1':
		{
			cin.get();
			instr->findInstructor();
			break;
		}
		case '2':
			instr->displayAll();
			break;
		default:
		{
			cout << "Incorrect number\n\n";
			instr->displayAll();
			break;
		}
		}
	}
}

void modification(std::string colName, std::string newVal, int id)
{
	stmt.str("");
	stmt << "UPDATE instructor SET " << colName << " = '" << newVal << "' WHERE id = " << id << ";";
	query = stmt.str();
	q = query.c_str();
	if (mysql_query(connection, q) == 0)			// mysql_query - sens query to the database
	{
		cout << endl << endl << "Modification Successfully Completed" << endl << endl << endl;
	}
	else {
		cout << endl << endl << "ERROR !" << endl << "Contact Technical Team " << endl << endl << endl;
	}
}