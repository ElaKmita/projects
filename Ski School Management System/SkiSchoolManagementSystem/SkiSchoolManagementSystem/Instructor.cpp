#include "Instructor.h"

using std::cout;
using std::cin;
using std::endl;

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
	cinIgnore();
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
	pressToContinue();
}

void Instructor::displayAll()
{
	query = "SELECT * FROM instructor;";
	q = query.c_str();
	mysql_query(connection, q);
	res_set = mysql_store_result(connection);
	bool validInput = false;
	while (!validInput)
	{
		system("CLS");
		int ans;
		cout << "\nDisplay views:\n\n";
		cout << "1. Individual View\n2. Table View\n\n";
		cout << "Select display view: ";
		try
		{
			cin >> ans;
			if (cin.fail())
			{
				throw std::invalid_argument("Incorrect input");
			}
			validInput = true;
			switch (ans)
			{
			case 1:
			{
				system("CLS");
				cout << "\n--- INSTRUCTORS ---\n";
				while ((row = mysql_fetch_row(res_set)) != NULL)
				{
					displayIndividualView(row);
				}
				pressToContinue();
				break;
			}
			case 2:
				system("CLS");
				displayTableView();
				pressToContinue();
				break;
			default:
				system("CLS");
				displayTableView();
				pressToContinue();
				break;
			}
		}
		catch (const std::invalid_argument& e)
		{
			cout << "\n\nError: " << e.what() << endl;
			cin.clear();	// clear the error flags of the input stream
			pressToContinue();
		}
	}
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
	int ans;
	cout << "\n- Modyfying instructor's data -\n\n";
	isInstrKnown(this);
	cout << endl << "Enter instructor id: ";
	if (cin >> id)
	{
		if (checkifSkiInstructorExist(id))
		{
			bool validInput = false;
			while (!validInput)
			{
				system("CLS");
				instModificationMenu();
				std::string column, newValue;
				try
				{
					cin >> ans;
					if (cin.fail())
					{
						throw std::invalid_argument("Incorrect input");
					}
					switch (ans)
					{
					case 0:
						break;
					case 1:
					{
						cin.get();
						column = "name";
						cout << "\nEnter new name: ";
						std::getline(cin, newValue);
						capitalize(newValue);
						modification(column, newValue, id);
						break;
					}
					case 2:
					{
						cin.get();
						column = "surname";
						cout << "\nEnter new surname: ";
						std::getline(cin, newValue);
						capitalize(newValue);
						modification(column, newValue, id);
						break;
					}
					case 3:
					{
						cin.get();
						column = "displayedName";
						cout << "\nEnter new displayed name: ";
						std::getline(cin, newValue);
						upperCase(newValue);
						modification(column, newValue, id);
						break;
					}
					case 4:
					{
						cin.get();
						column = "title";
						cout << "\nEnter new title (I, AI SITN, I SITN, AI PZN, I PZN): ";
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
						cout << "\nIncorrect number\n";
						pressToContinue();
						break;
					}
					validInput = ans == 0 ? true : false;
				}
				catch (const std::invalid_argument& e)
				{
					cout << "\n\nError: " << e.what() << endl;
					cin.clear();	// clear the error flags of the input stream
					pressToContinue();
				}
			}
		}
		else
		{
			cout << "\nInstructor with this id doesn't exist!\n\n";
			pressToContinue();
		}
	}
	else
	{
		cout << "\nInvalid data! Expected an integer!\n";
		cin.clear();
		pressToContinue();
	}
}

void Instructor::deleteInstructor()
{
	system("CLS");
	char ans;
	cout << "\n- Removing instructor from the database -\n\n";
	isInstrKnown(this);
	cout << endl << "Enter instructor id: ";
	if (cin >> id)
	{
		if (checkifSkiInstructorExist(id))
		{
			cout << endl << "Are you sure that you want delete this instructor? (y/n) ";
			cin.width(1);
			cin >> ans;
			if (ans == 'y' || ans == 'Y')
			{
				stmt.str("");
				stmt << "DELETE FROM instructor WHERE id = " << id << ";";
				query = stmt.str();
				q = query.c_str();
				sendQuery("Instructor Deleted Successfully");
				deleteAvailability(id);
			}
			else
			{
				cout << "\nInstructor has not been deleted\n\n";
			}
		}
		else
			cout << "\nInstructor with this id doesn't exist!\n\n";
	}
	else
	{
		cout << "\nInvalid data! Expected an integer!\n";
		cin.clear();
	}
	pressToContinue();
}

void Instructor::checkAvailability()
{
	system("CLS");
	cout << "\n- Checking instructor's availability -\n\n";
	isInstrKnown(this);
	cout << endl << "Enter instructor id: ";
	if (cin >> id)
	{
		system("CLS");
		cout << "\n- AVAILABILITY -\n";
		showAvailability(id);
	}
	else
	{
		cout << "\nInvalid data! Expected an integer!\n";
		cin.clear();
		pressToContinue();
	}
}

void Instructor::changeAvailability()
{
	system("CLS");
	cout << "\n- Changing instructor's availability -\n\n";
	isInstrKnown(this);
	cout << endl << "Enter instructor id: ";
	if (cin >> id)
	{
		if (checkifSkiInstructorExist(id))
		{
			int ans = -1;
			bool validInput = false;
			while (!validInput)
			{
				while (ans != 0)
				{
					system("CLS");
					cout << "\n- AVAILABILITY CHANGE -\n\n";
					cout << "1. Change whole week\n2. Change whole day \n3. Change specific hour\n0. EXIT\n\n";
					cout << "Choose your option: ";
					try
					{
						cin >> ans;
						if (cin.fail())
						{
							throw std::invalid_argument("Incorrect input");
						}
						switch (ans)
						{
						case 0:
							break;
						case 1:
							weekChange(id);
							break;
						case 2:
							dayChange(id);
							break;
						case 3:
							hourChange(id);
							break;
						default:
							cout << "Incorrect choice";
							pressToContinue();
							break;
						}
						validInput = ans == 0 ? true : false;
					}
					catch (const std::invalid_argument& e)
					{
						cout << "\n\nError: " << e.what() << endl;
						cin.clear();	// clear the error flags of the input stream
						pressToContinue();
						ans = -1;
					}
				}
			}
		}
		else
		{
			cout << "\n\Instructor with this id doesn't exist!\n";
			pressToContinue();
		}
	}
	else
	{
		cout << "\nInvalid data! Expected an integer!\n";
		cin.clear();
		pressToContinue();
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
	cout << endl << "- Data -\n\n";
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
	cin.width(1);
	cin >> ans;
	cinIgnore();
	system("CLS");
	if (ans == 'n' || ans == 'N')
	{
		char num;
		cout << "\n1. Find instructor\n2. Display all\n\nChoose option: ";
		cin.width(1);
		cin >> num;
		cinIgnore();		// ignore residue if user's input is longer than one character
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
			instr->displayAll();
			break;
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
	pressToContinue();
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

void deleteAvailability(const int& id)
{
	stmt.str("");
	stmt << "DELETE FROM availability WHERE instructor_id = " << id << ";";
	query = stmt.str();
	q = query.c_str();
	sendQuery("Instructor's Availability Deleted Successfully");
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

int daysMenu()		// returns value from the menu (counting from 1) 
{
	system("CLS");
	cout << "Choose the day:\n\n";
	int i = 1;
	for (std::string d : daysOfWeek)
	{
		cout << i << ". " << d << endl;
		i++;
	}
	cout << "\n0. EXIT" << endl << endl;
	int ans;
	while (true)
	{
		cout << "Choose your option: ";
		if (cin >> ans && ans >= 0 && ans <= daysOfWeek.size())
			return ans;
		else
		{
			cout << "\nInvalid data! Expected number from 0 to " << daysOfWeek.size() << ".\n\n";
			cin.clear();
			cinIgnore();
		}
	}
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
	cout << "\n0. EXIT" << endl << endl;
	int ans;
	while (true)
	{
		cout << "Choose your option: ";
		if (cin >> ans && ans >= 0 && ans <= workingHours.size())
			return ans;
		else
		{
			cout << "\nInvalid data! Expected number from 0 to " << workingHours.size() << ".\n\n";
			cin.clear();
			cinIgnore();
		}
	}
}

bool attendanceMenu()
{
	int ans;
	while (true)
	{
		system("CLS");
		cout << "Change to:\n\n";
		cout << "1. Presence" << endl;
		cout << "2. Absence" << endl << endl;
		cout << "Enter your choice: ";
		try
		{
			cin >> ans;
			if (cin.fail() || (ans != 1 && ans !=2))
			{
				throw std::invalid_argument("Invalid input!\nPlease select number 1 or 2.");
			}
			if (ans == 1)
				return 1;
			else if (ans == 2)
				return 0;
		}
		catch (const std::invalid_argument& e)
		{
			cout << endl << e.what() << endl;
			cin.clear();
			pressToContinue();
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
	pressToContinue();
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
		pressToContinue();
	}
	else
	{
		cout << "\nNo changes\n";
		Sleep(1000);
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
				cout << "Do you want to change another hour this day? (y/n) ";
				cin.width(1);
				cin >> ans;
				cinIgnore();
			}
			else
			{
				cout << "\nNo changes\n";
				Sleep(1000);
				ans = 'n';
			}
		}
	}
	else
	{
		cout << "\nNo changes\n";
		Sleep(1000);
	}
};

int checkifSkiInstructorExist(const int& instrId)
{
	stmt.str("");
	stmt << "SELECT COUNT(*) FROM instructor WHERE id = " << instrId << ";";
	query = stmt.str();
	q = query.c_str();				// convert to const char *
	mysql_query(connection, q);
	res_set = mysql_store_result(connection);
	if ((row = mysql_fetch_row(res_set)) != NULL)
	{
		return std::stoi(row[0]);;		// returns 0 if instructor doesn't exist or one if instructor exists
	}
}