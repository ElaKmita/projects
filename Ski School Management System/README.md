# Table of Contents

- [Ski School Management System](#ski-school-management-system)
    - [General Info](#general-info)
    - [Technologies](#technologies)
    - [Project](#project)
        - [Database_MySQL folder](#database_mysql-folder) 
        - [SkiSchoolManagementSystem folder](#skischoolmanagementsystem-folder)

<br><br>

# Ski School Management System

## General Info
The aim of this project is to create console application, that simulates functioning of the Ski School Management System.

The example program fragments are shown below: <br> <br>
<img src=".\SkiSchoolManagementSystem\Graphics\mainMenu.png" width=400/>
<img src=".\SkiSchoolManagementSystem\Graphics\dispInstructors.png" width=400/>

<br><br>

## Technologies
- C++ 14
- mysql.h library
- SQL 
- MySQL 8.0
<br><br>

## Project
### Database_MySQL folder
Database_MySQL folder contains a database named 'skischool' exported from MySQL Workbench. <br>
It allows to create a schema on the connected server by importing the generated structure and data. <br>

### SkiSchoolManagementSystem folder
This folder includes the main program.
Created solution consists of header files and .cpp files. <br>
Main function is placed in `SkiSchoolManagementSystem.cpp` file. <br>
Before running the code, it is obligatory to: <br>
* create MySQL database (arbitrary name) basing on [Database_MySQL folder](#database_mysql-folder)
* set the connection with MySQL in `mysqlConnection.h` file int the part that is shown below

```
#define HOST "127.0.0.1"
#define USER "root"
#define PASS                    /*put the password of MySQL in here between ""*/
#define DATABASE "skischool"	/*put the name of database in here between ""*/
#define PORT 3306
```

After that, build the solution and run the project.