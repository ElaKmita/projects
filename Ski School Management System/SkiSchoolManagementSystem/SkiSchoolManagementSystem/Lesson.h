#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

#include "mysqlConnection.h"
#include "additionalFunctions.h"
#include "SkiLearner.h"
#include "Instructor.h"

class Lesson
{
private:
	int id;
	int skiLearnerId;		// only one learner's data is needed to book a lesson (even if it's a group lesson)
	int learnersNum;		// number of learners
	int hoursNum;			// number of hours
	int instructorId;
	int price;				// price is returned by getPrice() function
	int getPrice(int learners, int hours);		// returns price for hour for one person - price depends on number of learners and number of hours		
	std::string day;
	std::string hour;

public:
	void addLesson();
	void findLesson();				// find the lesson by phone number or surname
	void displayAllLessons();		// display all lessons on a specific day
};

// functions' declarations
int chooseDay();
int chooseHour(int hoursNum);
int checkifSkiLearnerExist(const int& skiLearnerId);
void findAvailableInst(const std::string& day, const int& hourIndex, const int& hoursNum, std::vector<int>& resultsList, std::vector<std::string>& nameList);
void updateData(const int& instructorId, const int& skiLearnerId, const std::string& day, const int& hourIdx, const int& hoursNum, const int& price);
void lessonsSearchingMenu();
void searchLessonByInst();
void searchLessonByLearner();