#include <iostream>

// include user-defined files
#include "utils.h"
#include "main_admin.cpp"
#include "main_employee.cpp"

// function declarations
void menu();

// main function
int main()
{
    menu();
    return 0;
}

// void menu
void menu()
{
    std::string choice;

    while (true)
    {
        Utils::clearScreen();

        Utils::header("LOGIN AS");

        Utils::showOption(1, "Admin");
        Utils::showOption(2, "Employee");
        Utils::showOption(3, "Exit");

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
        {
            main_admin();
        }
        else if (choice == "2")
        {
            main_employee();
        }
        else if (choice == "3")
        {
            exit(0);
        }
        else
        {
            Utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid choice. Press any key to try again!");
            Utils::pauseScreen();
        }
    }
}