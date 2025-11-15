#pragma once

// include header file
#include "employee.h"

class EmployeeManager
{
public:
    bool add(Employee);                               // add new employee;
    bool update(Employee);                            // update
    bool remove(int);                                 // remove employees
    bool fetch(int, Employee &);                      // fetch employee
    bool login(std::string, std::string, int &);      // login
    static std::vector<Employee> fetchAllEmployees(); // fetch all employees
};