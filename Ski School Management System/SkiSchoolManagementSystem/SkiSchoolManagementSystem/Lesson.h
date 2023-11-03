#pragma once

#include <iostream>

class Lesson
{
private:
	int id;
	int skiLearnerId;		// only one learner's data is needed to book a lesson (even if it's a group lesson)
	int learnersNum;		// number of learners
	int hoursNum;
	int instructorId;
	int price;				
	int getPrice(int learners, int hours);		// returns price for hour for one person - price depends on number of learners and number of hours		
	std::string day;
	int hour;
public:
	//addLesson();
};



/*
SELECT * FROM skischool.instructor
LEFT JOIN skischool.availability ON instructor.id = availability.instructor_id;
*/