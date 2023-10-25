#include <iostream>
#include <cstring>
#include <sstream>
#include <iomanip>

#include "SkiLearner.h"
#include "mysqlConnection.h"

using std::cout;
using std::cin;
using std::endl;

void displayIndividualViewSL(MYSQL_ROW& row);
void displayTableViewSL();
void isLearnerKnown(SkiLearner* skiLearner);

void SkiLearner::setLevel()
{
	cout << "\nLevels:\n";
	int i = 1;
	for (std::string l : levels)
	{
		cout << i << ". " << l << endl;
		i++;
	}
	int ans;
	cout << "\nSelect ski learner's level:  ";
	cin >> ans;
	while ((ans <= 0) || (ans > levels.size()))
	{
		cout << "Incorrect number.\nProvide the correct number: ";
		cin >> ans;
	}
	level = levels[ans - 1];
	cout << endl << endl;
}

void SkiLearner::setSlope()
{
	cout << "\nSlopes:\n";
	int i = 1;
	for (std::string l : slopes)
	{
		cout << i << ". " << l << endl;
		i++;
	}
	int ans;
	cout << "\nSelect slope:  ";
	cin >> ans;
	while (ans != 1 && ans != 2)
	{
		cout << "Incorrect number.\nProvide the correct number: ";
		cin >> ans;
	}
	slope = slopes[ans - 1];
	cout << endl << endl;
}

void SkiLearner::addSkiLearner()
{
	cout << "\nEnter data\n";
	cout << "Name: ";
	std::getline(cin, name);
	cout << "Surname: ";
	std::getline(cin, surname);
	cout << "Phone number: ";
	while (cin >> phoneNumber && strlen(phoneNumber) != 9)
	{
		cout << "Incorrect number.\nProvide the correct phone number: ";
	}
	setLevel();
	cout << "Level set as: " << level << endl << endl;
	setSlope();
	cout << "Slope set as: " << slope << endl << endl;

	stmt.str("");
	stmt << "INSERT INTO ski_learner(name, surname, phoneNumber, level, slope) VALUES('" << name << "','" << surname << "','" << phoneNumber << "','" << level << "','" << slope << "');";
	query = stmt.str();				// convert to string
	q = query.c_str();				// convert to const char *

	if (mysql_query(connection, q) == 0)			// mysql_query - sends query to the database
	{
		cout << endl << endl << "New Ski Learner Inserted Successfully" << endl << endl << endl;
	}
	else {
		cout << endl << endl << "Entry ERROR !" << endl << "Contact Technical Team " << endl << endl << endl;
	}
}

void SkiLearner::displayAll()
{
	std::string query = "SELECT * FROM ski_learner;";
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
		cout << "\n--- SKI LEARNERS ---\n";
		while ((row = mysql_fetch_row(res_set)) != NULL)
		{
			displayIndividualViewSL(row);
		}
		break;
	}
	case '2':
		displayTableViewSL();
		break;
	default:
		displayTableViewSL();
		break;
	}
	cout << endl;
}

void displayIndividualViewSL(MYSQL_ROW& row)			// displays ski learners' data in individual view
{
	cout << endl;
	cout << "Id\t\t" << row[0] << endl;
	cout << "Name:\t\t" << row[1] << " " << row[2] << endl;
	cout << "Phone number:\t" << row[3] << endl;
	cout << "Level:\t\t" << row[4] << endl;
	cout << "Slope:\t\t" << row[5] << endl;
	cout << "Lessons:\t" << row[6] << endl;
}

void displayTableViewSL()				// displays ski learners' data in table view
{
	cout << "\n\n\t" << std::setw(54) << "--- SKI LEARNERS --- \n\n";
	cout << "\t" << std::left << std::setw(8) << "Id" << std::setw(15) << "Name" << std::setw(15) << "Surname" << std::setw(15) << "Phone Number" << std::setw(30) << "Level" << std::setw(15) << "Slope" << std::setw(8) << "Lessons" << endl << endl;
	while ((row = mysql_fetch_row(res_set)) != NULL)
	{
		cout << "\t" << std::left << std::setw(8) << row[0] << std::setw(15) << row[1] << std::setw(15) << row[2] << std::setw(15) << row[3] << std::setw(30) << row[4] << std::setw(15) << row[5] << std::setw(8) << row[6];
		cout << endl;
	}
}

void SkiLearner::findSkiLearner()
{
	std::string searchData;
	cout << "\nEnter search data (name or surname or phone number): ";
	std::getline(cin, searchData);
	stmt.str("");
	stmt << "SELECT * FROM ski_learner WHERE name = '" << searchData << "' OR surname = '" << searchData << "' OR phoneNumber = '" << searchData << "';";
	query = stmt.str();
	q = query.c_str();
	mysql_query(connection, q);
	res_set = mysql_store_result(connection);

	bool match = false;
	while ((row = mysql_fetch_row(res_set)) != NULL)
	{
		match = true;
		displayIndividualViewSL(row);
	}
	cout << (match ? "\n" : "\nNo items match your search\n\n");
}

void SkiLearner::deleteSkiLerner()
{
	char ans;
	cout << "\nRemoving ski learner from the database\n\n";
	isLearnerKnown(this);
	cout << endl << "Enter learner id: ";
	cin >> id;
	cout << endl << "Are you sure that you want delete this learner? (y/n) ";
	cin >> ans;
	if (ans == 'y')
	{
		stmt.str("");
		stmt << "DELETE FROM ski_learner WHERE id = " << id << ";";
		query = stmt.str();
		q = query.c_str();
		if (mysql_query(connection, q) == 0)			// mysql_query - sens query to the database
		{
			cout << endl << endl << "Learner Deleted Successfully" << endl << endl << endl;
		}
		else {
			cout << endl << endl << "Entry ERROR !" << endl << "Contact Technical Team " << endl << endl << endl;
		}
	}
	else
	{
		cout << "\nLearner has not been deleted\n\n";
	}
}

void isLearnerKnown(SkiLearner* skiLearner)
{
	char ans;
	cout << "Do you know learner id? (y/n) ";
	cin >> ans;
	if (ans == 'n')
	{
		char num;
		cout << "\n1. Find learner\n2. Display all\n\nChoose option: ";
		cin >> num;
		switch (num)
		{
		case '1':
		{
			cin.get();
			skiLearner->findSkiLearner();
			break;
		}
		case '2':
			skiLearner->displayAll();
			break;
		default:
		{
			cout << "Incorrect number\n\n";
			skiLearner->displayAll();
			break;
		}
		}
	}
}