#include "Availability.h"
#include "mysqlConnection.h"

using std::cout;
using std::cin;
using std::endl;

/*
void Availability::resetWeekAvailability()
{
	system("CLS");
	cout << "\n- Reseting Instructors' availability for whole week -\n\n";
	stmt.str("");
	std::string query = "SELECT id FROM instructor;";
	q = query.c_str();
	mysql_query(connection, q);
	res_set = mysql_store_result(connection);

	while ((row = mysql_fetch_row(res_set)) != NULL)
	{
		for (std::string d : daysOfWeek)
		{

		}
	}

}
*/