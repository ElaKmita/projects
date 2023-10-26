#pragma once

#include <iostream>
#include <array>
#include <cstring>
#include <sstream>
#include <iomanip>

class SkiLearner
{
private:
	int id;
	std::string name;
	std::string surname;
	char phoneNumber[9];
	std::string level;
	std::string slope;
	int lessons;

	std::array<std::string, 6> levels = { "Never skied before", "Snowplow turns and braking", "Stem turns", "Parallel glide turns", "Beginning to ski on edges", "Advanced" };
	std::array<std::string, 2> slopes = { "For beginners", "Normal slope" };
	void setLevel();
	void setSlope();

public:
	void addSkiLearner();			// adds new learner to the database
	void displayAll();				// displays all ski learners
	void findSkiLearner();			// finds learner in the database
	void modifyData();				// modifies learner's data
	void deleteSkiLerner();			// deletes learner from database
};

