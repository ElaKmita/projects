#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <conio.h>
#include <list>
#include <map>
//#include "Instructor.h";

using std::cout;
using std::cin;
using std::endl;

// Connection with MySQL
#define HOST "127.0.0.1"
#define USER "root"
#define PASS "2_KLZBRMQ1_pass" /*put the password of MySQL in here between ""*/
#define DATABASE "skischool"
#define PORT 3306
//#define PASSWORD 1234 /*Set a Numeric Password for Your Application*/

MYSQL* connection;			
MYSQL_RES* res_set;
MYSQL_ROW row;

std::stringstream stmt;
const char* q;
std::string query;

// functions' declarations
void upperCase(std::string& str);
void displayData(MYSQL_ROW& row);
void modification(std::string colName, std::string newVal, int id);
void instModificationMenu();


/*
----------------------------------
CLASSES & METHODS
----------------------------------
*/

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

	std::list<std::string> titles{"I", "AI SITN", "I SITN", "AI PZN", "I PZN"};		// list with all available titles 

	double setPercent(std::string&);	// sets percent - depends on title

public:
	void addInstructor();			// adds new instructor to the database
	void displayAll();				// displays all instructors
	void findInstructor();			// finds instructor in the database
	void modifyData();				// modifies instructor's data
	void deleteInstructor();		// deletes instructor from database
};

// additional functions' declarations

void isInstrKnown(Instructor* instr);

// Instructor - METHODS

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
	cout << "\n--- INSTRUCTORS ---\n";
	std::string query = "SELECT * FROM instructor;";
	q = query.c_str();
	mysql_query(connection, q);
	res_set = mysql_store_result(connection);	
	
	while ((row = mysql_fetch_row(res_set)) != NULL)
	{	
		displayData(row);
		/*
		cout << endl;
		cout << "Id\t\t" << row[0] << endl;
		cout << "Name:\t\t" << row[1] << " " << row[2] << endl;
		cout << "Displayed as:\t" << row[3] << endl;
		cout << "Title:\t\t" << row[4] << endl;
		cout << "Worked hours:\t" << row[6] << endl;
		cout << "Salary:\t" << row[7] << endl;
		*/
	}
	cout << endl;
	/*
	cout << "Id\t" << "Name\t\t" << "Surname\t\t" << "Displayed name\t" << "Title\t" << "h\t" << "PLN\t" << endl << endl;
	while ((row = mysql_fetch_row(res_set)) != NULL)
	{
		cout << row[0] << "\t" << row[1] << "\t\t" << row[2] << "\t\t" << row[3] << "\t" << row[4] << "\t" << row[6] << "\t" << row[7] << "\t";
		cout << endl;
	}
	*/
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
		displayData(row);
	}
	cout << (match ? "\n" : "\nNo items match this data\n");
}

void Instructor::modifyData()
{
	char ans;
	cout << "\nModyfying instructor data\n\n";
	/*
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
			findInstructor();
			break;
		}
		case '2':
			displayAll();
			break;
		default:
		{
			cout << "Incorrect number\n\n";
			displayAll();
			break;
		}
		}
	}
	*/

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
	/*
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
			findInstructor();
			break;
		}
		case '2':
			displayAll();
			break;
		default:
		{
			cout << "Incorrect number\n\n";
			displayAll();
			break;
		}
		}
	}
	*/
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
		cout << "\nInstructor has not been deleted\n";
	}
}


// ADDITIONAL FUNCTIONS

void upperCase(std::string& str)
{
	for (char& ch : str) {
		if (std::islower(ch))
			ch = std::toupper(ch);
	}
}

void displayData(MYSQL_ROW& row)
{
	cout << endl;
	cout << "Id\t\t" << row[0] << endl;
	cout << "Name:\t\t" << row[1] << " " << row[2] << endl;
	cout << "Displayed as:\t" << row[3] << endl;
	cout << "Title:\t\t" << row[4] << endl;
	cout << "Worked hours:\t" << row[6] << endl;
	cout << "Salary:\t\t" << row[7] << endl;
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

/*
----------------------------------
MENU 
----------------------------------
*/

// MENU - Instructor

void displayMenuInst()
{
	cout << "--- INSTRUCTOR MENU ---\n\n";
	cout << "1. Add new instructor\n";
	cout << "2. Display all instructors\n";
	cout << "3. Find instructor\n";
	cout << "4. Modify instructor's data\n";
	cout << "5. Delete instructor\n";
	cout << "0. EXIT\n\n";
	cout << "Choose option: ";
}

void instructorMenu(Instructor& instr)
{
	char choice;
	displayMenuInst();

	while (cin >> choice && choice != '0')
	{
		cin.get();
		switch (choice)
		{
		case '0':
			cout << "Goodbye!\n\n";
			exit(0);
			break;
		case '1':
			instr.addInstructor();
			break;
		case '2':
			instr.displayAll();
			break;
		case '3':
			instr.findInstructor();
			break;
		case '4':
			instr.modifyData();
			break;
		case '5':
			instr.deleteInstructor();
			break;
		default:
			cout << "\nIncorrect choice.\nPlease select number from 0 to 3.\n\n";
			break;
		}
	
		displayMenuInst();
	}
}

int main()
{
	// connection initialization
	connection = mysql_init(0);
	connection = mysql_real_connect(connection, HOST, USER, PASS, DATABASE, PORT, NULL, 0);

	/*
	if (connection) {
		cout << "Successful connection to database!" << endl;
	}
	else {
		cout << "Connection to database failed: " << mysql_error(connection) << endl;
	}
	*/

	Instructor i;
	instructorMenu(i);
	//i.addInstructor();
	//i.displayAll();
	//i.deleteInstructor();
	//i.findInstructor();
	//i.modifyData();
}

