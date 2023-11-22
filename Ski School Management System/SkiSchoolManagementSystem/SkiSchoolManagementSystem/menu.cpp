#include "menu.h"

using std::cout;
using std::cin;
using std::endl;


// MENU 

void displayMainMenu()
{
	system("CLS");
	cout << "\n--- MAIN MENU ---\n\n";
	cout << "1. Lessons\n";
	cout << "2. Instructors\n";
	cout << "3. Ski learners\n";
	cout << "4. Additional options\n";
	cout << "0. EXIT\n\n";
	cout << "Choose option: ";
}

void mainMenu()
{
	int choice = -1;
	while (true)
	{
		try
		{
			while (choice != 0)
			{
				displayMainMenu();
				cin >> choice;
				if (cin.fail())
				{
					throw std::invalid_argument("Incorrect input. \nPlease select number from 0 to 4.");
				}
				switch (choice)
				{
				case 0:
					cout << "\n\nGoodbye!\n\n";
					exit(0);
					break;
				case 1:
				{
					Lesson l;
					lessonMenu(l);
					break;
				}
				case 2:
				{
					Instructor i;
					instructorMenu(i);
					break;
				}
				case 3:
				{
					SkiLearner sl;
					learnerMenu(sl);
					break;
				}
				case 4:
				{
					AdditionalOptionsMenu();
					break;
				}
				default:
					cout << "\nIncorrect choice.\nPlease select number from 0 to 4.\n\n";
					pressToContinue();
					break;
				}
			}
		}
		catch (const std::invalid_argument& e)
		{
			cout << endl << "ERROR: " << e.what() << endl << endl;
			cin.clear();
			pressToContinue();
			choice = -1;
		}
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
	int choice = -1;
	bool validInput = false;
	while (!validInput)
	{
		try
		{
			while (choice != 0)
			{
				displayMenuLesson();
				cin >> choice;
				if (cin.fail())
				{
					throw std::invalid_argument("Incorrect input. \nPlease select number from 0 to 3.");
				}
				switch (choice)
				{
				case 0:
					break;
				case 1:
					lesson.addLesson();
					break;
				case 2:
					lesson.findLesson();
					break;
				case 3:
					lesson.displayAllLessons();
					break;
				default:
					cout << "\nIncorrect choice.\nPlease select number from 0 to 3: \n\n";
					pressToContinue();
					break;
				}
				validInput = (choice == 0 ? true : false);
			}
		}
		catch (const std::invalid_argument& e)
		{
			cout << endl << "ERROR: " << e.what() << endl << endl;
			cin.clear();
			pressToContinue();
			choice = -1;
		}
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
	int choice = -1;
	bool validInput = false;
	while (!validInput)
	{
		try
		{
			while (choice != 0)
			{
				displayMenuInst();
				cin >> choice;
				if (cin.fail())
				{
					throw std::invalid_argument("Incorrect input. \nPlease select number from 0 to 7.");
				}
				switch (choice)
				{
				case 0:
					break;
				case 1:
					instr.addInstructor();
					break;
				case 2:
					instr.displayAll();
					break;
				case 3:
					instr.findInstructor();
					break;
				case 4:
					instr.modifyData();
					break;
				case 5:
					instr.deleteInstructor();
					break;
				case 6:
					instr.checkAvailability();
					break;
				case 7:
					instr.changeAvailability();
					break;
				default:
					cout << "\nIncorrect choice.\nPlease select number from 0 to 7.\n\n";
					pressToContinue();
					break;
				}
				validInput = (choice == 0 ? true : false);
			}
		}
		catch (const std::invalid_argument& e)
		{
			cout << endl << "ERROR: " << e.what() << endl << endl;
			cin.clear();
			pressToContinue();
			choice = -1;
		}
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
	cout << "4. Change learner's level\n";
	cout << "5. Modify learner's data\n";
	cout << "6. Delete learner\n";
	cout << "0. EXIT\n\n";
	cout << "Choose option: ";
}

void learnerMenu(SkiLearner& skiLearner)
{
	int choice = -1;
	bool validInput = false;
	while (!validInput)
	{
		try
		{
			while (choice != 0)
			{
				displayMenuSL();
				cin >> choice;
				if (cin.fail())
				{
					throw std::invalid_argument("Incorrect input. \nPlease select number from 0 to 6.");
				}
				switch (choice)
				{
				case 0:
					break;
				case 1:
					skiLearner.addSkiLearner();
					break;
				case 2:
					skiLearner.displayAll();
					break;
				case 3:
					skiLearner.findSkiLearner();
					break;
				case 4:
					skiLearner.changeLevel();
					break;
				case 5:
					skiLearner.modifyData();
					break;
				case 6:
					skiLearner.deleteSkiLerner();
					break;
				default:
					cout << "\nIncorrect choice.\nPlease select number from 0 to 6. \n\n";
					pressToContinue();
					break;
				}
				validInput = (choice == 0 ? true : false);
			}
		}
		catch (const std::invalid_argument& e)
		{
			cout << endl << "ERROR: " << e.what() << endl << endl;
			cin.clear();
			pressToContinue();
			choice = -1;
		}
	}
}

// MENU - Additional Options

void displayMenuAO()		// displays menu of additional options
{
	system("CLS");
	cout << "\n--- ADDITIONAL OPTIONS MENU ---\n\n";
	cout << "1. Reset week\n";
	cout << "2. Instructor's payment\n";
	cout << "0. EXIT\n\n";
	cout << "Choose option: ";
}

void AdditionalOptionsMenu()
{
	int choice = -1;
	bool validInput = false;
	while (!validInput)
	{
		try
		{
			while (choice != 0)
			{
				displayMenuAO();
				cin >> choice;
				if (cin.fail())
				{
					throw std::invalid_argument("Incorrect input. \nPlease select number from 0 to 2.");
				}
				switch (choice)
				{
				case 0:
					break;
				case 1:
					resetWeek();			// reset all lessons and set instructor's availability to presence for the whole week
					break;
				case 2:
					payment();
					break;
				default:
					cout << "\nIncorrect choice.\nPlease select number from 0 to 2. \n\n";
					pressToContinue();
					break;
				}
				validInput = (choice == 0 ? true : false);
			}
		}
		catch (const std::invalid_argument& e)
		{
			cout << endl << "ERROR: " << e.what() << endl << endl;
			cin.clear();
			pressToContinue();
			choice = -1;
		}
	}
}