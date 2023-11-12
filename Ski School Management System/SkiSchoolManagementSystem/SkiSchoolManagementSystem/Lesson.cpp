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
	cin >> skiLearnerId;
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
				stmt << "INSERT INTO lesson(skiLearnerId, instructorId, day, hour, numOflearners, numOfHours, price) VALUES(" << skiLearnerId << " , " << instructorId << ",'" << day << "','" << hour << "', " << learnersNum << " , " << hoursNum << " , " << price <<  ");";
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
	cin.get();
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
	cout << endl << endl;
	// funkcja z array i obsluga blednie wprowadzonych danych
	int ans;
	cout << "Choose your option: ";
	// OBSŁUGA BŁĘDNIE WPROWADZONYCH DANYCH
	while (!(cin >> ans) || ans < 1 || ans > lastAvailableHour)
	{
		cout << "\nIncorrect data \n";
		cout << "Choose your option: ";
	}
	return ans;
}

int chooseDay()					// returns value from the menu (counting from 1) 
{
	system("CLS");
	cout << "Choose the day:\n\n";
	int i = 1;
	for (std::string d : daysOfWeek)
	{
		cout << i << ". " << d << endl;
		i++;
	}
	cout << endl << endl;
	// funkcja z array i obsluga blednie wprowadzonych danych
	int ans;
	cout << "Choose your option: ";
	// OBSŁUGA BŁĘDNIE WPROWADZONYCH DANYCH
	while (!(cin >> ans) || ans < 1 || ans > daysOfWeek.size())
	{
		cout << "\nIncorrect data \n";
		cout << "Choose your option: ";
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