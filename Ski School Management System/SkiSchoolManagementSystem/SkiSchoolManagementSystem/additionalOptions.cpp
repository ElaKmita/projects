#include "additionalOptions.h"

using std::cout;
using std::cin;
using std::endl;

void payAll();
void singlePay();

void resetWeek()
{
	char ans;
	system("CLS");
	cout << "\n - RESETING WEEK -\n\n";
	cout << "Are you sure you want to reset the previous week and prepare for another one? (y/n) ";
	cin >> ans;
	if (ans == 'y' || ans == 'Y')
	{
		query = "";
		for (std::string h : workingHours)
		{
			stmt.str("");
			stmt << "UPDATE availability SET " << h << " = 1 ;";
			query = query + stmt.str() + "\n";
		}
		q = query.c_str();

		sendMultiQuery("Instructor's Availability Reset Successfully");

		stmt.str("");
		stmt << "TRUNCATE lesson;";
		query = stmt.str();
		q = query.c_str();

		sendQuery("Lessons Reset Successfuly");
	}
	else
	{
		cout << endl << endl << "Data Not Reset\n\n";
	}
	pressToContinue();
}

void paymentMenu()
{
	system("CLS");
	query = "SELECT id, name, surname, salary FROM instructor;";
	q = query.c_str();
	mysql_query(connection, q);
	res_set = mysql_store_result(connection);

	cout << "\n" << "--- SALARY --- \n\n";
	cout << std::left << std::setw(8) << "Id" << std::setw(20) << "Name" << std::setw(20) << "Surname" << std::setw(8) << "Salary [PLN]" << endl << endl;
	while ((row = mysql_fetch_row(res_set)) != NULL)
	{
		cout << std::left << std::setw(8) << row[0] << std::setw(20) << row[1] << std::setw(20) << row[2] << std::setw(8) << row[3];
		cout << endl;
	}

	cout << "\n\n - PAYMENT -\n\n";
	cout << "1. Make all payment\n";
	cout << "2. Pay one instructor\n";
	cout << "0. EXIT\n\n";
	cout << "Insert your choice: ";
}

void payment()
{
	char ans;
	paymentMenu();
	while (cin >> ans && ans != '0')
	{
		switch (ans)
		{
		case '0':
			break;
		case '1':
		{
			payAll();
			break;
		}
		case '2':
		{
			singlePay();
			break;
		}	
		default:
			cout << "\nIncorrect input. Select number from 0 to 2: ";
		}
		paymentMenu();
	}	
}

void payAll()
{
	char ans;
	cout << endl << endl << "Would you like to confirm the withdrawal? (y/n) ";
	cin >> ans;
	if (ans == 'y' || ans == 'Y')
	{
		query = "UPDATE instructor SET salary = 0 ;";
		q = query.c_str();
		sendQuery("Withdrawal Confirmed - Salary Updated Successfully");
	}
	else
	{
		cout << endl << endl << "Salary Not Changed\n\n";
	}
	pressToContinue();
}

void singlePay()
{
	int id;
	char ans;
	cout << endl << endl << "Enter instructor id: ";
	cin >> id;
	// check if instructor exist
	cout << endl << endl << "Would you like to confirm the withdrawal? (y/n) ";
	cin >> ans;
	if (ans == 'y' || ans == 'Y')
	{
		stmt.str("");
		stmt << "UPDATE instructor SET salary = 0 WHERE id = " << id << " ;";
		query = stmt.str();
		q = query.c_str();
		sendQuery("Withdrawal Confirmed - Salary Updated Successfully");
	}
	else
	{
		cout << endl << endl << "Salary Not Changed\n\n";
	}
	pressToContinue();
}