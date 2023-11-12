#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <conio.h>
#include <cstdlib>

#include "Instructor.h";
#include "mysqlConnection.h"
#include "SkiLearner.h"
#include "additionalFunctions.h"	
#include "Lesson.h";

using std::cout;
using std::cin;
using std::endl;

// Connection with MySQL - definition

MYSQL* connection;			
MYSQL_RES* res_set;
MYSQL_ROW row;

std::stringstream stmt;
const char* q;
std::string query;


/*
----------------------------------
MENU 
----------------------------------
*/

void instructorMenu(Instructor& instr);
void learnerMenu(SkiLearner& skiLearner);
void lessonMenu(Lesson& lesson);

// MENU 

void displayMainMenu()
{
	system("CLS");
	cout << "\n--- MAIN MENU ---\n\n";
	cout << "1. Lessons\n";
	cout << "2. Instructors\n";
	cout << "3. Ski learners\n";
	cout << "0. EXIT\n\n";
	cout << "Choose option: ";
}

void peopleMenu()
{
	char choice;
	displayMainMenu();

	while (cin >> choice && choice != '0')
	{
		cin.get();
		switch (choice)
		{
		case '0':
			cout << "\n\nGoodbye!\n\n";
			exit(0);
			break;
		case '1':
		{
			Lesson l;
			lessonMenu(l);
			break;
		}
		case '2':
		{
			Instructor i;
			instructorMenu(i);
			break;
		}
		case '3':
		{
			SkiLearner sl;
			learnerMenu(sl);
			break;
		}
		default:
			cout << "\nIncorrect choice.\nPlease select number from 0 to 5.\n\n";
			break;
		}

		displayMainMenu();
	}
}


// MENU - Lesson

void displayMenuLesson()
{
	system("CLS");
	cout << "\n--- LESSONS MENU ---\n\n";
	cout << "1. Add new lesson\n";
	cout << "2. Find lesson\n";
	cout << "3. Display all lessons\n";
	cout << "0. EXIT\n\n";
	cout << "Choose option: ";
}

void lessonMenu(Lesson& lesson)
{
	char choice;
	displayMenuLesson();

	while (cin >> choice && choice != '0')
	{
		cin.get();
		switch (choice)
		{
		case '0':
			break;
		case '1':
			lesson.addLesson();
			break;
		case '2':
			//lesson.findLesson();
			break;
		case '3':
			//lesson.displayAllLessons();
			break;
		default:
			cout << "\nIncorrect choice.\nPlease select number from 0 to 3: \n\n";
			break;
		}
		displayMenuLesson();
	}
}

// MENU - Instructor

void displayMenuInst()
{
	system("CLS");
	cout << "\n--- INSTRUCTORS MENU ---\n\n";
	cout << "1. Add new instructor\n";
	cout << "2. Display all instructors\n";
	cout << "3. Find instructor\n";
	cout << "4. Modify instructor's data\n";
	cout << "5. Delete instructor\n";
	cout << "6. Check instructor's availability\n";
	cout << "7. Change availability\n";
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
		case '6':
			instr.checkAvailability();
			break;
		case '7':
			instr.changeAvailability();
			break;
		default:
			cout << "\nIncorrect choice.\nPlease select number from 0 to 5.\n\n";
			pressToContinue();
			break;
		}
	
		displayMenuInst();
	}
}


// MENU - Ski Learner

void displayMenuSL()
{
	system("CLS");
	cout << "\n--- SKI LEARNERS MENU ---\n\n";
	cout << "1. Add new learner\n";
	cout << "2. Display all learners\n";
	cout << "3. Find learner\n";
	cout << "4. Modify learner's data\n";
	cout << "5. Delete learner\n";
	cout << "0. EXIT\n\n";
	cout << "Choose option: ";
}

void learnerMenu(SkiLearner& skiLearner)
{
	char choice;
	displayMenuSL();

	while (cin >> choice && choice != '0')
	{
		cin.get();
		switch (choice)
		{
		case '0':
			break;
		case '1':
			skiLearner.addSkiLearner();
			break;
		case '2':
			skiLearner.displayAll();
			break;
		case '3':
			skiLearner.findSkiLearner();
			break;
		case '4':
			skiLearner.modifyData();
			break;
		case '5':
			skiLearner.deleteSkiLerner();
			break;
		default:
			cout << "\nIncorrect choice.\nPlease select number from 0 to 5: \n\n";
			break;
		}

		displayMenuSL();
	}
}


int main()
{
	// connection initialization
	connection = mysql_init(0);
	connection = mysql_real_connect(connection, HOST, USER, PASS, DATABASE, PORT, NULL, 0);
	mysql_set_server_option(connection, MYSQL_OPTION_MULTI_STATEMENTS_ON);		// enables sending more than one statemet to SQL 

	/*
	if (connection) {
		cout << "Successful connection to database!" << endl;
	}
	else {
		cout << "Connection to database failed: " << mysql_error(connection) << endl;
	}
	*/

	peopleMenu();
	//Instructor i;
	//instructorMenu(i);
	//i.addInstructor();
	//i.displayAll();
	//i.deleteInstructor();
	//i.findInstructor();
	//i.modifyData();
	//SkiLearner s;
	//learnerMenu(s);

	//Lesson l;
	//l.addLesson();
}

