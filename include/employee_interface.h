#pragma once

// include header file
#include "employee_manager.h"

namespace employee_interface
{
    void adminMenu();        // menu
    void add();              // add new employee
    void showDetails(int);   // my details
    void update();           // update employee details
    void remove();           // remove employee
    bool login(int &);       // login
    void viewAll();          // view all employees
    void searchById();       // search employee by id
    void searchByUsername(); // search employee by username
};