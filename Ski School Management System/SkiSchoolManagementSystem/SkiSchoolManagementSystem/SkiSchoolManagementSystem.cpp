// SkiSchoolManagementSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cstdlib>

#include "Instructor.h";

using std::cout;
using std::cin;
using std::endl;

int main()
{
    int option;

    cout << " *** INSTRUCTORS ***" << endl << endl;
    cout << "1. Add new instructor" << endl;
    cout << "2. Delete instructor" << endl;
    cout << "3. Modify instructor's data" << endl;
    cout << "4. EXIT" << endl << endl;

    cout << "Choose option: ";
    cin >> option;

    switch (option)
    {
    case 1:
        addInstructor();
        break;
    case 2:
        deleteInstructor();
        break;
    case 3:
        modifyInstructor();
        break;
    case 4:
        // display previous MENU
        exit(0);
    default:
        cout << "This option not exists.\nPlease select number from 1 to 4.\n";
        break;
    }
    /*
    std::string name, surname, displayedName, title;
    std::cout << "podaj imie: ";
    std::getline(std::cin, name);
    std::cout << "podaj nazwisko: ";
    std::getline(std::cin, surname);
    std::cout << "podaj wyswietlana nazwe: ";
    std::getline(std::cin, displayedName);
    std::cout << "podaj tytul: ";
    std::getline(std::cin, title);
    */

    std::string name = "John";
    std::string surname = "Doe";
    std::string displayedName = "John Doe";
    std::string title = "AI SITN";
    std::string title1 = "AI PZN";
    std::string title2 = "I PZN";

    Instructor instr(name, surname, displayedName, title);
    Instructor instr1(name, surname, displayedName, title1);
    Instructor instr2(name, surname, displayedName, title2);
    Instructor i;
    //instr.displayData();
    std::cout << Instructor::getInstAmount() << std::endl;
    std::cout << Instructor::getPZNInstAmount() << std::endl;
}

