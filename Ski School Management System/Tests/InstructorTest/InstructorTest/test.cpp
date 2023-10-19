# include "pch.h"
#include <gtest/gtest.h>
#include "../../../SkiSchoolManagementSystem/SkiSchoolManagementSystem/Instructor.h"
#include "../../../SkiSchoolManagementSystem/SkiSchoolManagementSystem/Instructor.cpp"

TEST(InstructorTest, DefaultConstructor)
{
    Instructor instr;

    EXPECT_EQ("", instr.getName());
    EXPECT_EQ("", instr.getSurname());
    EXPECT_EQ("", instr.getDisplayedName());
    EXPECT_EQ("", instr.getTitle());
    EXPECT_EQ(0.0, instr.getPertcent());
    EXPECT_EQ(0, instr.getWorkedHours());
    EXPECT_EQ(0, instr.getSalary());
    EXPECT_EQ(0, Instructor::getInstAmount());
    EXPECT_EQ(0, Instructor::getPZNInstAmount());
}

TEST(InstructorTest, ParametrizedConstructor)
{
    std::string name = "John";
    std::string surname = "Doe";
    std::string displayedName = "John Doe";
    std::string title = "I PZN";

    Instructor instr(name, surname, displayedName, title);

    EXPECT_EQ(name, instr.getName());
    EXPECT_EQ(surname, instr.getSurname());
    EXPECT_EQ(displayedName, instr.getDisplayedName());
    EXPECT_EQ(title, instr.getTitle());
    EXPECT_EQ(0.6, instr.getPertcent());
    EXPECT_EQ(0, instr.getWorkedHours());
    EXPECT_EQ(0, instr.getSalary());
    EXPECT_EQ(1, Instructor::getInstAmount());
    EXPECT_EQ(1, Instructor::getPZNInstAmount());
}


TEST(InstructorTest, Constructors)
{
    std::string name = "John";
    std::string surname = "Doe";
    std::string displayedName = "John Doe";
    std::string title = "AI SITN";
    std::string title1 = "AI PZN";
    std::string title2 = "I PZN";

    Instructor instr(name, surname, displayedName, title);
    Instructor instr1(name, surname, displayedName, title1);
    Instructor instr2(name, surname, displayedName, title2);
    //Instructor inst;        // instructor with empty data is not included into instructors amount

    EXPECT_EQ(3, Instructor::getInstAmount());
    EXPECT_EQ(2, Instructor::getPZNInstAmount());
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
