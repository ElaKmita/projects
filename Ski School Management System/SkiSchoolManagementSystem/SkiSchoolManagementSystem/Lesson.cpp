#include "Lesson.h"

int getPrice(int learners, int hours)		// returns price for hour for one person
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

