
# Campus Lost-and-Found Management System

## 1. Project Overview

The Campus Lost-and-Found Management System is a C++ application
designed to help students and staff report lost belongings and
register items found on campus.

The system provides a centralized way to record, search, display,
and update lost-and-found item information.

## 2. Problem Statement

Traditional methods of reporting lost belongings, such as
notice boards and verbal communication, can make it difficult
to maintain and search records.

This project proposes a simple computerized system to organize
item records and make the recovery process more efficient.

## 3. Objectives

- Register lost items.
- Register found items.
- Store item names, categories, locations, and dates.
- Search records by item name.
- Display all registered items.
- Update the status of an item.
- Save records using file handling.
- Demonstrate OOP concepts in C++.

## 4. Features

- Lost item registration
- Found item registration
- Automatic item IDs
- Item search
- Display of all records
- Status updates: Lost, Found, Returned
- Persistent local file storage

## 5. Technologies Used

- Programming Language: C++
- Compiler: GCC or Clang
- Code Editor: Visual Studio Code
- C++ Standard: C++17
- Storage: Text file

## 6. OOP Concepts Used

### Classes and Objects
The Item class represents an item, while LostAndFound manages
the application's operations.

### Encapsulation
Item data members are private and accessed through public
member functions.

### Constructors
Constructors initialize item objects with their details.

### Vectors
A vector stores multiple item records.

### File Handling
The items.txt file stores records between program sessions.

### Abstraction
The user interacts with simple menu options without needing
to know how records are stored internally.

## 7. How to Compile and Run

### macOS or Linux

Compile:

clang++ -std=c++17 main.cpp -o lost_found

Run:

./lost_found

### Windows with GCC

Compile:

g++ -std=c++17 main.cpp -o lost_found.exe

Run:

lost_found.exe

## 8. Data Storage

The program creates items.txt to store item records.
The file is generated automatically when records are saved.

Keep this file in the program's working directory to retain
records between sessions.

## 9. Limitations

- Console-based interface.
- No online database or user accounts.
- No automatic notifications.
- No automatic verification of item ownership.
- Search is based on item names and is case-sensitive.

## 10. Future Enhancements

- User authentication
- Administrator dashboard
- Email or app notifications
- Advanced search by location and date
- Graphical user interface
- Database integration

## 11. Conclusion

The Campus Lost-and-Found Management System demonstrates how
C++ and OOP can help organize lost-and-found records.

It applies classes, objects, encapsulation, constructors,
vectors, and file handling to a practical campus problem.

## 12. Project Type

OOP in C++ Case Study and Demonstration Project
