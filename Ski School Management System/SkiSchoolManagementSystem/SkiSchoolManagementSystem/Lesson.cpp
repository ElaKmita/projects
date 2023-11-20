#include "Lesson.h"

using std::cout;
using std::cin;
using std::endl;

int Lesson::getPrice(int learners, int hours)		// returns price for hour for one person
{
	if (learners == 1)
	{
		if (hours == 1)
			return 130;
		else if (hours == 2)
			return 115;
		else
			return 100;
	}
	else if (learners == 2)
	{
		if (hours == 1)
			return 110;
		else if (hours == 2)
			return 100;
		else
			return 90;
	}
	else
	{
		if (hours == 1)
			return 100;
		else if (hours == 2)
			return 80;
		else
			return 70;
	}
}

void Lesson::addLesson()
{
	system("CLS");
	char ans;
	SkiLearner learner;
	isLearnerKnown(&learner);
	system("CLS");
	cout << "Insert client Id: ";
	if (cin >> skiLearnerId)
	{
		if (checkifSkiLearnerExist(skiLearnerId))
		{
			cout << endl << "Insert the number of learners: ";
			while (!(cin >> learnersNum) || learnersNum <= 0 || learnersNum > 8)
			{
				if (learnersNum <= 0)
					cout << "Minimum 1 learner is required" << endl;
				else if (learnersNum > 8)
					cout << "Up to 8 learners are available" << endl;
				else
					cout << "Incorrect data" << endl;

				cout << endl << "Insert the number of learners: ";
			}

			cout << endl << "Insert the number of hours: ";
			while (!(cin >> hoursNum) || hoursNum <= 0 || hoursNum > 4)
			{
				if (hoursNum <= 0)
					cout << "Minimum 1 hour is required" << endl;
				else if (hoursNum > 4)
					cout << "Up to 4 hours are available" << endl;
				else
					cout << "Incorrect data" << endl;

				cout << endl << "Insert the number of hours: ";
			}
			day = daysOfWeek[chooseDay() - 1];

			int hourIdx = chooseHour(hoursNum) - 1;
			hour = workingHours[hourIdx];

			std::vector<int> idList;		// list of IDs that meet requirement of availability
			std::vector<std::string> nameList;
			findAvailableInst(day, hourIdx, hoursNum, idList, nameList);

			cout << "Insert instructor id: ";
			cin >> instructorId;
			bool correctID = false;
			std::string instructorName;
			int idx = 0;
			for (int i : idList)
			{
				if (i == instructorId)
				{
					correctID = true;
					instructorName = nameList[idx];
					break;
				}
				idx++;
			}

			if (correctID)
			{
				system("CLS");
				cout << "\n\t- RESERVATION -\n\n";
				price = getPrice(learnersNum, hoursNum) * hoursNum * learnersNum;
				cout << "Day:\t\t\t" << day << endl;
				cout << "Hour\t\t\t" << hour << endl;
				cout << "Instructor:\t\t" << instructorName << endl;
				cout << "Number of hours:\t" << hoursNum << endl;
				cout << "Number of learners:\t" << learnersNum << endl;
				cout << "Price:\t\t\t" << price << " PLN" << endl;
				char ans;
				cout << "\nDo you confirm the reservation? (y/n) ";
				cin >> ans;
				if (ans == 'y' || ans == 'Y')
				{
					stmt.str("");
					stmt << "INSERT INTO lesson(skiLearnerId, instructorId, day, hour, numOflearners, numOfHours, price) VALUES(" << skiLearnerId << " , " << instructorId << ",'" << day << "','" << hour << "', " << learnersNum << " , " << hoursNum << " , " << price << ");";
					query = stmt.str();
					q = query.c_str();

					bool properlyConnected;		// check if query is correctly connected with database
					sendQuery("New Lesson Successfully Added", properlyConnected);

					if (properlyConnected)
						updateData(instructorId, skiLearnerId, day, hourIdx, hoursNum, price);
				}
				else
				{
					cout << endl << "Reservation Canceled\n\n";
				}
			}
			else
			{
				cout << "\n\nIncorrect instructor Id \nThis instructor is not available in the provided hours.\n\n";
			}
		}
		else
		{
			cout << "\n\nIncorrect ski learner Id! \n\n";
		}
	}
	else
	{
		cout << "\nInvalid data! Expected an integer!\n";
		cin.clear();
	}
	pressToContinue();
}

void Lesson::findLesson()				// find the lesson by phone number or surname
{
	int ans;
	bool validInput = false;
	while (!validInput)
	{
		try
		{
			ans = -1;
			lessonsSearchingMenu();
			while (ans != 0)
			{
				cin >> ans;
				if (cin.fail())
				{
					throw std::invalid_argument("Incorrect input");
				}
				if (ans < 0 || ans > 2)
				{
					throw "\nIncorrect input. Select number from 0 to 2\n\n";
				}
				switch (ans)
				{
				case 0:
					validInput = true;
					break;
				case 1:
				{
					searchLessonByInst();
					break;
				}
				case 2:
				{
					searchLessonByLearner();
					break;
				}
				default:
					cout << "\nIncorrect input. Select number from 0 to 2: ";
				}
				lessonsSearchingMenu();
			}
		}
		catch (const std::invalid_argument& e)
		{
			cout << "\n\nError: " << e.what() << endl;
			cin.clear();	// clear the error flags of the input stream
			pressToContinue();
		}
		catch (const char* e)
		{
			cout << "\n\n" << e << endl;
			cin.clear();	// clear the error flags of the input stream
			pressToContinue();
		}
	}
}

void Lesson::displayAllLessons()		// display all lessons on a specific day
{
	int dayIdx = chooseDay() - 1;

	stmt.str("");

	stmt << "SELECT l.id, sl.name, sl.surname, sl.phoneNumber, l.hour, l.numOfHours, l.numOfLearners, i.displayedName, sl.level, sl.slope"
		" FROM lesson AS l INNER JOIN instructor as i ON l.instructorId = i.id INNER JOIN ski_learner AS sl ON l.skiLearnerId = sl.id"
		" WHERE l.day = '" << daysOfWeek[dayIdx] << "' ORDER BY l.hour ASC;";

	query = stmt.str();
	q = query.c_str();
	mysql_query(connection, q);
	res_set = mysql_store_result(connection);

	system("CLS");
	cout << "\n\t\t\t\t\t" << "--- " << daysOfWeek[dayIdx] << "'s lessons --- \n\n";
	cout << std::left << std::setw(4) << "Id" << std::setw(12) << "Name" << std::setw(12) << "Surname" << std::setw(12) << "Phone Num" << std::setw(6) << "Hour" << std::setw(7) << "hours" << std::setw(9) << "people" << std::setw(15) << "Disp Name" << std::setw(30) << "level" << std::setw(20) << "slope" << endl << endl;
	bool noItems = true;
	while ((row = mysql_fetch_row(res_set)) != NULL)
	{
		cout << std::left << std::setw(4) << row[0] << std::setw(12) << row[1] << std::setw(12) << row[2] << std::setw(12) << row[3] << std::setw(6) << row[4] << std::setw(7) << row[5] << std::setw(9) << row[6] << std::setw(15) << row[7] << std::setw(30) << row[8] << std::setw(20) << row[9];
		cout << endl;
		noItems = false;
	}
	if (noItems)
	{
		cout << "\n\t\t\t\t\tNo lessons scheduled\n\n";
	}
	pressToContinue();
}

int chooseHour(int hoursNum)	// returns value from the menu (counting from 1) 
{
	system("CLS");
	cout << "Choose the hour\n\n";
	int lastAvailableHour = workingHours.size() - (hoursNum - 1);
	int i = 1;
	for (std::string h : workingHours)
	{
		if (i > lastAvailableHour)
		{
			break;					// Stop iteration after lastAvailableHour
		}
		cout << i << ". " << h << endl;
		i++;
	}
	cout << endl;
	int ans;
	bool validInput = false;
	while (!validInput)
	{
		cout << "\nChoose the hour: ";
		try
		{
			cin >> ans;
			if (cin.fail() || ans < 1 || ans > lastAvailableHour)
			{
				throw "Incorrect input. Please select the proper number.";
			}
			validInput = true;
		}
		catch (const char* e)
		{
			cout << "\n" << e << endl;
			cin.clear();	// clear the error flags of the input stream
			cinIgnore();
		}
	}
	return ans;
}

int chooseDay()							// returns value from the menu (counting from 1) 
{
	system("CLS");
	cout << "Choose the day:\n\n";
	int i = 1;
	for (std::string d : daysOfWeek)
	{
		cout << i << ". " << d << endl;
		i++;
	}
	cout << endl;
	int ans;
	bool validInput = false;
	while (!validInput)
	{
		cout << "\nChoose the day: ";
		try
		{
			cin >> ans;
			if (cin.fail() || ans < 1 || ans > 7)
			{
				throw "Incorrect input. Please select the proper number.";
			}
			validInput = true;
		}
		catch (const char* e)
		{
			cout << "\n" << e << endl;
			cin.clear();	// clear the error flags of the input stream
			cinIgnore();
		}
	}
	return ans;
}

void findAvailableInst(const std::string& day, const int& hourIndex, const int& hoursNum, std::vector<int>& resultsList, std::vector<std::string>& nameList)
{
	system("CLS");
	query = "";
	stmt.str("");
	stmt << "SELECT instructor.displayedName, availability.* FROM instructor RIGHT JOIN availability ON availability.instructor_id = instructor.id WHERE day = '" << day << "' ";
	query = stmt.str();

	int lastIndex = hourIndex + hoursNum;

	for (int i = hourIndex; i < lastIndex; i++)
	{
		stmt.str("");
		stmt << "AND " << workingHours[i] << " = 1 ";
		query = query + stmt.str() + '\n';
	}
	query = query + ";";
	q = query.c_str();
	mysql_query(connection, q);
	res_set = mysql_store_result(connection);

	cout << "\n\n\t" << "--- AVAILABLE INSTRUCTORS --- \n\n";
	cout << "\t" << std::left << std::setw(8) << "Id" << std::setw(15) << "Name" << endl << endl;
	while ((row = mysql_fetch_row(res_set)) != NULL)
	{
		cout << "\t" << std::left << std::setw(8) << row[1] << std::setw(15) << row[0] << endl;
		resultsList.push_back(std::stoi(row[1]));
		nameList.push_back(row[0]);
	}
	cout << endl;
}

void updateData(const int& instructorId, const int& skiLearnerId, const std::string& day, const int& hourIdx, const int& hoursNum, const int& price)
{
	int salary = 0;
	int workedHours = 0;
	int lessons = 0;

	// UPDATING INSTRUCTOR TABLE
	// data extraction from SQL: workedHours, salary, percent from instructor table
	stmt.str("");
	stmt << "SELECT workedHours, salary, percent FROM instructor WHERE id = " << instructorId << ";";
	query = stmt.str();
	q = query.c_str();
	mysql_query(connection, q);
	res_set = mysql_store_result(connection);
	while ((row = mysql_fetch_row(res_set)) != NULL)
	{
		workedHours = std::stoi(row[0]) + hoursNum;							// workedHours = workedHours (from SQL) + number of hours
		salary = ceil(std::stoi(row[1]) + std::stod(row[2]) * price);		// salary = salary (from SQL) + percent (from SQL) * price for the lesson  (ceil to be an int)
	}
	// updating instructor table
	stmt.str("");
	stmt << "UPDATE instructor SET workedHours = " << workedHours << " , salary = " << salary << " WHERE id = " << instructorId << ";";
	query = stmt.str();
	q = query.c_str();
	sendQuery("Instructor's Salary Successfully Updated");

	// UPDATING AVAILABILITY TABLE
	query = "";
	int lastIdx = hourIdx + hoursNum - 1;
	for (int i = hourIdx; i <= lastIdx; i++)
	{
		stmt.str("");
		stmt << "UPDATE availability SET " << workingHours[i] << " = 2 WHERE instructor_id = " << instructorId << " AND day = '" << day << "';";
		query = query + stmt.str() + "\n";
	}
	q = query.c_str();

	sendMultiQuery("New Lesson Successfully Added To Instructor's Availability");

	// UPDATING SKI_LEARNER TABLE
	// data extraction from SQL: lessons from ski_learner table
	stmt.str("");
	stmt << "SELECT lessons FROM ski_learner WHERE id = " << skiLearnerId << ";";
	query = stmt.str();
	q = query.c_str();
	mysql_query(connection, q);
	res_set = mysql_store_result(connection);
	while ((row = mysql_fetch_row(res_set)) != NULL)
	{
		lessons = std::stoi(row[0]) + hoursNum;							// lessons = lessons (from SQL) + number of hours
	}
	// updating ski_learner table
	stmt.str("");
	stmt << "UPDATE ski_learner SET lessons = " << lessons << " WHERE id = " << skiLearnerId << "; ";
	query = stmt.str();
	q = query.c_str();
	mysql_query(connection, q);
	sendQuery("SkiLearner's Data Successfully Updated");
}

void lessonsSearchingMenu()
{
	system("CLS");
	cout << "\n- SEARCHING FOR A LESSONS - \n\n";
	cout << "Search lessons by:\n\n";
	cout << "1. Instructor\n";
	cout << "2. Ski learner\n";
	cout << "0. EXIT\n\n";
	cout << "Insert your choice: ";
}

void searchLessonByInst()
{
	system("CLS");
	int id;
	Instructor inst;
	isInstrKnown(&inst);
	cout << "\n\nInsert instructor id: ";
	cin >> id;
	if (checkifSkiInstructorExist(id))
	{
		stmt.str("");
		stmt << "SELECT l.id, l.day, l.hour, l.numOfHours, l.numOfLearners, sl.name, sl.surname, sl.phoneNumber, sl.level, sl.slope"
			" FROM lesson AS l INNER JOIN ski_learner AS sl ON l.skiLearnerId = sl.id"
			" WHERE l.instructorId = " << id << " ORDER BY l.day;";

		query = stmt.str();
		q = query.c_str();
		mysql_query(connection, q);
		res_set = mysql_store_result(connection);

		system("CLS");
		cout << "\n\t\t\t\t\t" << "--- Scheduled lessons --- \n\n";
		cout << std::left << std::setw(4) << "Id" << std::setw(8) << "Day" << std::setw(6) << "Hour" << std::setw(7) << "hours" << std::setw(9) << "people" << std::setw(15) << "Name" << std::setw(12) << "Surname" << std::setw(12) << "Phone Num" << std::setw(30) << "level" << std::setw(20) << "slope" << endl << endl;
		bool noItems = true;
		while ((row = mysql_fetch_row(res_set)) != NULL)
		{
			cout << std::left << std::setw(4) << row[0] << std::setw(8) << row[1] << std::setw(6) << row[2] << std::setw(7) << row[3] << std::setw(9) << row[4] << std::setw(15) << row[5] << std::setw(12) << row[6] << std::setw(12) << row[7] << std::setw(30) << row[8] << std::setw(20) << row[9];
			cout << endl;
			noItems = false;
		}
		if (noItems)
		{
			cout << "\n\t\t\t\t\tNo lessons scheduled\n\n";
		}
	}
	else
	{
		cout << "\n\Instructor with this id doesn't exist!\n\n";
	}
	pressToContinue();
}

void searchLessonByLearner()
{
	cinIgnore();
	char* phoneNum = new char[11];		// The input should be 10 characters long (9 digits + null character), but I want to verify that the user has entered the correct number of digits
	bool validInput = false;
	while (!validInput)
	{
		try
		{
			system("CLS");
			cout << "\nInsert learner's phone number (e.g. 123456789): ";
			cin.width(11);		
			cin >> phoneNum;
			if (phoneNum[3] == '-')
			{
				throw std::invalid_argument("Invalid phone number format. \nExpected format: 123456789");
			}
			if (strlen(phoneNum) != 9)
			{
				throw std::length_error("Invalid phone number. \nNumber should consist of 9 digits. \nExpected format: 123456789");
			}
			validInput = true;
			stmt.str("");
			stmt << "SELECT l.id, l.day, l.hour, l.numOfHours, l.numOfLearners, sl.name, sl.surname, i.displayedName, sl.level, sl.slope"
				" FROM lesson AS l INNER JOIN instructor as i ON l.instructorId = i.id INNER JOIN ski_learner AS sl ON l.skiLearnerId = sl.id"
				" WHERE sl.phoneNumber = '" << phoneNum << "' ;";
			query = stmt.str();
			q = query.c_str();
			mysql_query(connection, q);
			res_set = mysql_store_result(connection);

			cout << "\n\n\t\t\t\t\t" << "--- Scheduled lessons --- \n\n";
			cout << std::left << std::setw(4) << "Id" << std::setw(15) << "Name" << std::setw(12) << "Surname" << std::setw(8) << "Day" << std::setw(6) << "Hour" << std::setw(7) << "hours" << std::setw(9) << "people" << std::setw(12) << "Instructor" << std::setw(30) << "level" << std::setw(20) << "slope" << endl << endl;
			bool noItems = true;
			while ((row = mysql_fetch_row(res_set)) != NULL)
			{
				cout << std::left << std::setw(4) << row[0] << std::setw(15) << row[5] << std::setw(12) << row[6] << std::setw(8) << row[1] << std::setw(6) << row[2] << std::setw(7) << row[3] << std::setw(9) << row[4] << std::setw(12) << row[7] << std::setw(30) << row[8] << std::setw(20) << row[9];
				cout << endl;
				noItems = false;
			}
			if (noItems)
			{
				cout << "\n\t\t\t\t\tNo lessons scheduled \n\n";
			}
		}
		catch (const std::invalid_argument& e)
		{
			cout << endl << "ERROR: " << e.what() << endl;
			cin.clear();	// clear the error flags of the input stream
		}
		catch (const std::length_error& e)
		{
			cout << endl << "ERROR: " << e.what() << endl;
			cin.clear();	// clear the error flags of the input stream
		}
		pressToContinue();
	}
	delete[] phoneNum;
}
