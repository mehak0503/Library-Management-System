# INTRODUCTION

A user driven library management system with three entities involved i.e. Students, Library Staff and Supplier. Each entity has a provision to perform only defined set of functions.

## Technologies Used
- C++
- make
- SQLite
- batch scripting

## BUILD INSTRUCTIONS
- Using g++
> g++ main.cpp db.cpp Menu.cpp -lsqlite3
> ./a.out

- Using IDE
simply run main.cpp with adding sqlite3 path to linker


## RUN SYSTEM 
- Enter "admin" as password
- Choose 1/2/3 for staff/user/supplier and 4 for exit.
- Choose suitable option based on the operation required as presented in the menu.
- Enter valid input wherever prompted.


## TEST CASES 
- Input for test cases is provided in testcases folder.
- Makefile executes all the defined testcases.
- Run "make" command to execute testcases.
