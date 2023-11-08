#include "Instructor.h"
#include "mysqlConnection.h"
#include "additionalFunctions.h"

using std::cout;
using std::cin;
using std::endl;

// functions' declarations
void displayIndividualView(MYSQL_ROW& row);
void displayTableView();
void modification(std::string colName, std::string newVal, int id);
void instModificationMenu();
void isInstrKnown(Instructor* instr);
void initializeAvailability();
void showAvailability(const int& id);
//std::string daysMenu();
//void hoursMenu();
//bool attendanceMenu();
void sendQuery(std::string successAnnouncement);
void sendMultiQuery(std::string successAnnouncement);
void weekChange(const int& id);
void dayChange(const int& id);
void hourChange(const int& id);

// Instructor's methods

double Instructor::setPercent(std::string& _title)
{
	std::map<std::string, double> rateDict;		// dictionary with title-rate dependencies
	rateDict["I"] = 0.4;						// Instructor after course
	rateDict["AI SITN"] = 0.45;					// Assistant Instructor SITN
	rateDict["I SITN"] = 0.5;					// Instructor SITN
	rateDict["AI PZN"] = 0.55;					// Assistant Instructor PZN 
	rateDict["I PZN"] = 0.6;					// Instructor PZN

	return rateDict[_title];					// returns percent that depends on title
}

void Instructor::addInstructor()
{
	system("CLS");
	cout << "\n- Adding new instructor -\n\n";
	cout << "Enter data\n\n";
	cout << "Name: ";
	std::getline(cin, name);
	capitalize(name);
	cout << "Surname: ";
	std::getline(cin, surname);
	capitalize(surname);
	cout << "Displayed name: ";
	std::getline(cin, displayedName);
	upperCase(displayedName);
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
		cout << endl << "New Instructor Inserted Successfully" << endl;
		initializeAvailability();
	}
	else {
		cout << endl << "Entry ERROR !" << endl << "Contact Technical Team " << endl << endl;
	}
}

void Instructor::displayAll()
{
	std::string query = "SELECT * FROM instructor;";
	q = query.c_str();
	mysql_query(connection, q);
	res_set = mysql_store_result(connection);

	system("CLS");
	char ans;
	cout << "\nDisplay views:\n\n";
	cout << "1. Individual View\n2. Table View\n\n";
	cout << "Select display view: ";
	cin >> ans;

	switch (ans)
	{
	case '1':
	{
		system("CLS");
		cin.get();
		cout << "\n--- INSTRUCTORS ---\n";
		while ((row = mysql_fetch_row(res_set)) != NULL)
		{
			displayIndividualView(row);
		}
		pressToContinue();
		break;
	}
	case '2':
		system("CLS");
		cin.get();
		displayTableView();
		pressToContinue();
		break;
	default:
		system("CLS");
		cin.get();
		displayTableView();
		pressToContinue();
		break;
	}
	// system("CLS");
}

void Instructor::findInstructor()
{
	system("CLS");
	cout << "\n- Searching for instructor -\n\n";
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
	pressToContinue();
}

void Instructor::modifyData()
{
	system("CLS");
	char ans;
	cout << "\n- Modyfying instructor's data -\n\n";
	isInstrKnown(this);
	cout << endl << "Enter instructor id: ";
	cin >> id;
	system("CLS");
	instModificationMenu();
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
			capitalize(newValue);
			modification(column, newValue, id);
			break;
		}
		case '2':
		{
			cin.get();
			column = "surname";
			cout << "Enter new surname: ";
			std::getline(cin, newValue);
			capitalize(newValue);
			modification(column, newValue, id);
			break;
		}
		case '3':
		{
			cin.get();
			column = "displayedName";
			cout << "Enter new displayed name: ";
			std::getline(cin, newValue);
			upperCase(newValue);
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
	system("CLS");
	char ans;
	cout << "\n- Removing instructor from the database -\n\n";
	isInstrKnown(this);
	cout << endl << "Enter instructor id: ";
	cin >> id;
	cout << endl << "Are you sure that you want delete this instructor? (y/n) ";
	cin >> ans;
	cin.get();
	if (ans == 'y')
	{
		stmt.str("");
		stmt << "DELETE FROM instructor WHERE id = " << id << ";";
		query = stmt.str();
		q = query.c_str();
		if (mysql_query(connection, q) == 0)			// mysql_query - sens query to the database
		{
			cout << endl << endl << "Instructor Deleted Successfully" << endl << endl;
		}
		else 
		{
			cout << endl << endl << "Entry ERROR !" << endl << "Contact Technical Team " << endl << endl;
		}
	}
	else
	{
		cout << "\nInstructor has not been deleted\n\n";
	}
	pressToContinue();
}

void Instructor::checkAvailability()
{
	system("CLS");
	cout << "\n- Checking instructor's availability -\n\n";
	isInstrKnown(this);
	cout << endl << "Enter instructor id: ";
	cin >> id;
	system("CLS");
	cout << "\n- AVAILABILITY -\n";
	showAvailability(id);
	//pressToContinue();
}

void Instructor::changeAvailability()
{
	char ans = 1;
	//char repetition = 'y';
	system("CLS");
	cout << "\n- Changing instructor's availability -\n\n";
	isInstrKnown(this);
	cout << endl << "Enter instructor id: ";
	cin >> id;
	while (ans != '0')
	{
		system("CLS");
		cout << "\n- AVAILABILITY CHANGE -\n\n";
		cout << "1. Change whole week\n2. Change whole day \n3. Change specific hour\n0. EXIT\n\n";
		cin >> ans;
		switch (ans)
		{
		case '0':
			break;
		case '1':
			weekChange(id);
			break;
		case '2':
			dayChange(id);
			break;
		case '3':
			hourChange(id);
			break;
		default:
			cout << "Incorrect choice";
			break;
		}
	}
}

// additional functions

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
	cout << "\n\t\t\t\t\t" << "--- INSTRUCTORS--- \n\n";		// << std::setw(54)
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
	system("CLS");
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

	sendQuery("Modification Successfully Completed");
}

void initializeAvailability()
{
	stmt.str("");
	std::string query = "SELECT id FROM instructor ORDER BY id DESC LIMIT 1;";
	q = query.c_str();
	mysql_query(connection, q);
	res_set = mysql_store_result(connection);

	if ((row = mysql_fetch_row(res_set)) != NULL)
	{
		query = "";

		for (std::string d : daysOfWeek)
		{
			stmt.str("");
			stmt << "INSERT INTO availability (instructor_id, day) VALUES(" << row[0] << ", '" << d << "');";
			query = query + stmt.str() + "\n";
		}
		q = query.c_str();

		sendMultiQuery("Instructor's Availability Set Successfully");
	}
	else
		cout << "\nError occured while setting availability\n\n";
}

void showAvailability(const int& id)
{
	stmt.str("");
	stmt << "SELECT displayedName FROM instructor WHERE id = " << id << ";";
	query = stmt.str();
	q = query.c_str();
	mysql_query(connection, q);
	res_set = mysql_store_result(connection);
	if ((row = mysql_fetch_row(res_set)) != NULL)
	{
		cout << "\n\nInstructor: " << row[0] << "\n\n\n";

		cout << std::left << std::setw(10) << "DAY" << std::setw(5) << "8AM" << std::setw(5) << "9AM" << std::setw(5) << "10AM" << std::setw(5) << "11AM" << std::setw(5) << "12PM" << std::setw(5) << "13PM" << std::setw(5) << "14PM" << std::setw(5) << "15PM" << endl << endl;
		
		for (std::string d : daysOfWeek)
		{
			stmt.str("");
			stmt << "SELECT * FROM availability WHERE instructor_id = " << id << " AND day = '" << d << "';";
			query = stmt.str();
			q = query.c_str();
			mysql_query(connection, q);
			res_set = mysql_store_result(connection);

			if ((row = mysql_fetch_row(res_set)) != NULL)
			{
				cout << std::left << std::setw(12) << d;
				for (int i = 2; i <= 10; i++)
					cout << std::setw(5) << row[i];
				cout << endl;
			}
			else
			{
				cout << endl << endl << "Entry ERROR !" << endl << "Contact Technical Team " << endl << endl;
				break;
			}
		}
	}
	else
	{
		cout << "\n\nInstructor with this id doesn't exist.\n\n";
	}
	cin.get();
	pressToContinue();
}

int daysMenu()
{
	system("CLS");
	cout << "Choose the day:\n\n";
	int i = 1;
	for (std::string d : daysOfWeek)
	{
		cout << i << ". " << d << endl;
		i++;
	}
	cout << "0. EXIT" << endl << endl;
	// funkcja z array i obsluga blednie wprowadzonych danych
	int ans;
	cout << "Choose your option: ";
	cin >> ans;
	// OBSŁUGA BŁĘDNIE WPROWADZONYCH DANYCH
	if (ans >= 1 && ans <= daysOfWeek.size())
		return ans;
	else
		return 0;
}

int hoursMenu()
{
	system("CLS");
	cout << "Choose the hour\n\n";
	int i = 1;
	for (std::string h : workingHours)
	{
		cout << i << ". " << h << endl;
		i++;
	}
	cout << "0. EXIT" << endl << endl;
	// funkcja z array i obsluga blednie wprowadzonych danych
	int ans;
	cout << "Choose your option: ";
	cin >> ans;
	// OBSŁUGA BŁĘDNIE WPROWADZONYCH DANYCH
	if (ans >= 1 && ans <= workingHours.size())
		return ans;
	else
		return 0;
}

bool attendanceMenu()
{
	char ans;
	system("CLS");
	cout << "Change to:\n\n";
	cout << "1. Presence" << endl;
	cout << "2. Absence" << endl << endl;
	cout << "Enter the number: ";
	while (cin >> ans)
	{
		if (ans == '1')
			return 1;
		else if (ans == '2')
			return 0;
		else
		{
			cin.ignore();
			cout << "Choose your option: ";
		}
	}
}

void weekChange(const int& id)
{
	bool attendance = attendanceMenu();
	query = "";
	for (std::string h : workingHours)
	{
		stmt.str("");
		stmt << "UPDATE availability SET " << h << " = " << attendance << " WHERE instructor_id = " << id << ";";
		query = query + stmt.str() + "\n";
	}
	q = query.c_str();

	sendMultiQuery("Instructor's Availability Changed Successfully");
}

void dayChange(const int& id) 
{
	bool attendance;
	int choice = daysMenu();
	if (choice != 0)
	{
		attendance = attendanceMenu();
		query = "";
		for (std::string h : workingHours)
		{
			stmt.str("");
			stmt << "UPDATE availability SET " << h << " = " << attendance << " WHERE instructor_id = " << id << " AND day = '" << daysOfWeek[choice - 1] << "';";
			query = query + stmt.str() + "\n";
		}
		q = query.c_str();

		sendMultiQuery("Instructor's Availability Changed Successfully");
	}
};

void hourChange(const int& id) 
{
	int choiceDay = daysMenu();
	if (choiceDay != 0)
	{	
		char ans = 'y';
		bool attendance;
		while (ans == 'y')
		{
			int choiceHour = hoursMenu();
			if (choiceHour != 0)
			{
				attendance = attendanceMenu();
				query = "";
				stmt.str("");
				stmt << "UPDATE availability SET " << workingHours[choiceHour - 1] << " = " << attendance << " WHERE instructor_id = " << id << " AND day = '" << daysOfWeek[choiceDay - 1] << "';";
				query = stmt.str();
				q = query.c_str();

				sendQuery("Instructor's Availability Changed Successfully");
			}
			cout << "Do you want to change another hour this day? (y/n) ";
			cin >> ans;
		}
	}
};

// sendQuery - function that should be used when only one query is sent
void sendQuery(std::string successAnnouncement)
{
	if (mysql_query(connection, q) == 0)			// mysql_query - sends query to the database
	{
		cout << endl << successAnnouncement << endl << endl;
	}
	else 
	{
		cout << endl << "Entry ERROR !" << endl << "Contact Technical Team " << endl << endl;
	}
	cin.get();
	pressToContinue();
}

// sendMuliQuery - function that should be used when more than one query is sent
void sendMultiQuery(std::string successAnnouncement)
{
	if (mysql_query(connection, q) == 0) // mysql_query - sends query to the database
	{
		do {
			/*
			res_set = mysql_store_result(connection); // Get the result of the query
			if (res_set) {
				// Process the result
				// ...
				mysql_free_result(res_set); // Free the memory associated with the result
			}
			*/ 
		} while (mysql_next_result(connection) == 0);
		cout << endl << successAnnouncement << endl << endl;
	}
	else {
		cout << endl << "Entry ERROR !" << endl << "Contact Technical Team " << endl << endl;
	}
	pressToContinue();
}