#pragma once

#include "Instructor.h";
#include "mysqlConnection.h"
#include "SkiLearner.h"
#include "additionalFunctions.h"	
#include "Lesson.h";
#include "additionalOptions.h"

void mainMenu();
void instructorMenu(Instructor& instr);
void learnerMenu(SkiLearner& skiLearner);
void lessonMenu(Lesson& lesson);
void AdditionalOptionsMenu();

