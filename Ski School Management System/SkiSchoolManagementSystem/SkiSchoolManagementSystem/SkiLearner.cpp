#include "SkiLearner.h"

using std::cout;
using std::cin;
using std::endl;


// SkiLearner's methods

void SkiLearner::setLevel()
{
	cout << "\nLevels:\n\n";
	int i = 1;
	for (std::string l : levels)
	{
		cout << i << ". " << l << endl;
		i++;
	}
	int ans;
	bool validInput = false;
	while (!validInput)
	{
		cout << "\nSelect ski learner's level:  ";
		try
		{
			cin >> ans;
			if (cin.fail())
			{
				throw std::invalid_argument("Invalid input!\nProvide the integer.");
			}
			if (ans <= 0 || ans > levels.size())
			{
				throw std::invalid_argument("Incorrect number.\nProvide the correct number.");
			}
			level = levels[ans - 1];
			validInput = true;
		}
		catch (const std::invalid_argument& e)
		{
			cout << endl << e.what() << endl << endl;
			cin.clear();
			cinIgnore();
		}
	}
	cout << endl << endl;
}

void SkiLearner::setSlope()
{
	cout << "\nSlopes:\n\n";
	int i = 1;
	for (std::string l : slopes)
	{
		cout << i << ". " << l << endl;
		i++;
	}
	int ans;
	bool validInput = false;
	while (!validInput)
	{
		cout << "\nSelect slope:  ";
		try
		{
			cin >> ans;
			if (cin.fail())
			{
				throw std::invalid_argument("Invalid input!\nProvide the integer.");
			}
			if (ans != 1 && ans != 2)
			{
				throw std::invalid_argument("Incorrect number.\nProvide the number 1 or 2.");
			}
			slope = slopes[ans - 1];
			validInput = true;
		}
		catch (const std::invalid_argument& e)
		{
			cout << endl << e.what() << endl << endl;
			cin.clear();
			cinIgnore();
		}
	}
	cout << endl << endl;
}

// void SkiLearner::setSlope()	// przeciazenie, samo ustawiajacy sie stok w zaleznosci od poziomu

void SkiLearner::addSkiLearner()
{
	system("CLS");
	cinIgnore();
	cout << "\n- Adding new ski learner -\n\n";
	cout << "\nEnter data\n\n";
	cout << "Name: ";
	std::getline(cin, name);
	capitalize(name);
	cout << "Surname: ";
	std::getline(cin, surname);
	capitalize(surname);

	bool validInput = false;
	while (!validInput)
	{
		try
		{
			cout << "\nPhone number (e.g. 123456789): ";
			cin.width(10);
			cin >> phoneNumber;
			if (phoneNumber[3] == '-')
			{
				throw std::invalid_argument("Invalid phone number format.\nExpected format: 123456789");
			}
			for (const char* ch = phoneNumber; ch < phoneNumber + 9; ch++)
			{
				if (!(isdigit(*ch)))
				{
					throw std::invalid_argument("Invalid phone number.\nNumber should consist of 9 digits.\nOther chars are not allowed.");
				}
			}
			validInput = true;
		}
		catch (const std::invalid_argument& e)
		{
			cout << endl << "ERROR: " << e.what() << endl;
			cin.clear();	// clear the error flags of the input stream
			cinIgnore();
		}
	}
	setLevel();
	cout << "Level set as: " << level << endl << endl;
	setSlope();
	cout << "Slope set as: " << slope << endl << endl;

	stmt.str("");
	stmt << "INSERT INTO ski_learner(name, surname, phoneNumber, level, slope) VALUES('" << name << "','" << surname << "','" << phoneNumber << "','" << level << "','" << slope << "');";
	query = stmt.str();				// convert to string
	q = query.c_str();				// convert to const char *

	sendQuery("New Ski Learner Inserted Successfully");
	pressToContinue();
}

void SkiLearner::displayAll()
{
	std::string query = "SELECT * FROM ski_learner;";
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
				cout << "\n--- SKI LEARNERS ---\n";
				while ((row = mysql_fetch_row(res_set)) != NULL)
				{
					displayIndividualViewSL(row);
				}
				pressToContinue();
				break;
			}
			case 2:
				system("CLS");
				displayTableViewSL();
				pressToContinue();
				break;
			default:
				system("CLS");
				displayTableViewSL();
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

void SkiLearner::findSkiLearner()
{
	system("CLS");
	cinIgnore();
	cout << "\n- Searching for ski learner -\n\n";
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
	pressToContinue();
}

void SkiLearner::changeLevel()
{
	system("CLS");
	int id;
	cout << "\Changing ski learner's level\n\n";
	isLearnerKnown(this);
	cout << endl << "Enter learner id: ";
	if (cin >> id)
	{
		if (checkifSkiLearnerExist(id))
		{
			system("CLS");
			setLevel();
			system("CLS");
			setSlope();

			stmt.str("");
			stmt << "UPDATE ski_learner SET level = '" << level << "', slope = '" << slope << "' WHERE id = " << id << ";";
			query = stmt.str();
			q = query.c_str();
			sendQuery("Modification Successfully Completed");
		}
		else
			cout << "\n\nLearner with this id doesn't exist!\n\n";
	}
	else
	{
		cout << "\nInvalid data! Expected an integer!\n";
		cin.clear();
	}
	pressToContinue();
}

void SkiLearner::modifyData()
{
	system("CLS");
	char ans;
	cout << "\nModyfying ski learner's data\n\n";
	isLearnerKnown(this);
	cout << endl << "Enter learner id: ";
	if (cin >> id)
	{
		if (checkifSkiLearnerExist(id))
		{
			learnerModificationMenu();
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
					modificationSL(column, newValue, id);
					break;
				}
				case '2':
				{
					cin.get();
					column = "surname";
					cout << "Enter new surname: ";
					std::getline(cin, newValue);
					modificationSL(column, newValue, id);
					break;
				}
				case '3':
				{
					cin.get();
					column = "phoneNumber";
					cout << "Enter phone number: ";
					while (cin >> phoneNumber && strlen(phoneNumber) != 9)
					{
						cout << "Incorrect number.\nProvide the correct phone number: ";
					}
					modificationSL(column, phoneNumber, id);
					break;
				}
				case '4':
				{
					cin.get();
					column = "level";
					cout << "\nSet new level\n";
					setLevel();
					modificationSL(column, level, id);
					break;
				}
				case '5':
				{
					cin.get();
					column = "slope";
					cout << "\nSet new slope\n";
					setSlope();
					modificationSL(column, slope, id);
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

				learnerModificationMenu();
			}
		}
		else
			cout << "\n\nLearner with this id doesn't exist!\n\n";
	}
	else
	{
		cout << "\nInvalid data! Expected an integer!\n";
		cin.clear();
	}

	pressToContinue();
}

void SkiLearner::deleteSkiLerner()
{
	system("CLS");
	char ans;
	cout << "\nRemoving ski learner from the database\n\n";
	isLearnerKnown(this);
	cout << endl << "Enter learner id: ";
	if (cin >> id)
	{
		if (checkifSkiLearnerExist(id))
		{
			cout << endl << "Are you sure that you want delete this learner? (y/n) ";
			cin >> ans;
			if (ans == 'y' || ans == 'Y')
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
		else
			cout << "\n\nLearner with this id doesn't exist!\n\n";
	}
	else
	{
		cout << "\nInvalid data! Expected an integer!\n";
		cin.clear();
	}
	pressToContinue();
}


// additional functions

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
	cout << "\n\n\t\t\t" << "--- SKI LEARNERS --- \n\n";
	cout << "\t" << std::left << std::setw(8) << "Id" << std::setw(15) << "Name" << std::setw(15) << "Surname" << std::setw(15) << "Phone Number" << std::setw(30) << "Level" << std::setw(15) << "Slope" << std::setw(8) << "Lessons" << endl << endl;
	while ((row = mysql_fetch_row(res_set)) != NULL)
	{
		cout << "\t" << std::left << std::setw(8) << row[0] << std::setw(15) << row[1] << std::setw(15) << row[2] << std::setw(15) << row[3] << std::setw(30) << row[4] << std::setw(15) << row[5] << std::setw(8) << row[6];
		cout << endl;
	}
}

void isLearnerKnown(SkiLearner* skiLearner)
{
	char ans;
	cout << "Do you know learner id? (y/n) ";
	cin.width(1);
	cin >> ans;
	cinIgnore();
	system("CLS");
	if (ans == 'n' || ans == 'N')
	{
		char num;
		cout << "\n1. Find learner\n2. Display all\n\nChoose option: ";
		cin.width(1);
		cin >> num;
		cinIgnore();
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

void learnerModificationMenu()
{
	cout << endl << "- Data -\n";
	cout << "1. Name" << endl;
	cout << "2. Surname" << endl;
	cout << "3. Phone Number" << endl;
	cout << "4. Level" << endl;
	cout << "5. Slope" << endl;
	cout << "0. END MODIFICATION";
	cout << "\n\nChoose the data that you want modify (1-5), press 0 to escape: ";
}

void modificationSL(std::string colName, std::string newVal, int id)
{
	stmt.str("");
	stmt << "UPDATE ski_learner SET " << colName << " = '" << newVal << "' WHERE id = " << id << ";";
	query = stmt.str();
	q = query.c_str();
	sendQuery("Modification Successfully Completed");
	pressToContinue();
}

int checkifSkiLearnerExist(const int& skiLearnerId)
{
	stmt.str("");
	stmt << "SELECT COUNT(*) FROM ski_learner WHERE id = " << skiLearnerId << ";";
	query = stmt.str();
	q = query.c_str();				// convert to const char *
	mysql_query(connection, q);
	res_set = mysql_store_result(connection);
	if ((row = mysql_fetch_row(res_set)) != NULL)
	{
		return std::stoi(row[0]);;		// returns 0 if instructor doesn't exist or one if instructor exists
	}
}