#include <iostream>
#include <thread>
#include <vector>
#include <string>

// importing user-defined files
#include "utils.h"
#include "file_setup.h"

// function declarations
void menu();                    // menu
void inventoryManagementMenu(); // inventory management menu
void employeeManagementMenu();  // employee management menu
void customerManagementMenu();  // customer management menu
void myProfileMenu();           // my profile menu
void myShopMenu();              // my shop menu

// main
int main()
{
    std::thread file_setup(app_files::setup); // file setup thread
    file_setup.detach();                      // run file setup task in the background independently
    menu();                                   // menu
}

// menu
void menu()
{
    std::string choice;

    std::map<int, std::string> options = {
        {1, "Inventory Management"},
        {2, "Employee Management"},
        {3, "Customer Management"},
        {4, "My Profile"},
        {5, "My Shop"},
        {6, "Exit"},
    };

    while (true)
    {
        utils::clearScreen();

        utils::header("ADMIN MENU");

        for (const auto &option : options)
            utils::showOption(option.first, option.second);

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
            inventoryManagementMenu();
        else if (choice == "2")
            employeeManagementMenu();
        else if (choice == "3")
            customerManagementMenu();
        else if (choice == "4")
            myProfileMenu();
        else if (choice == "5")
            myShopMenu();
        else if (choice == "6")
            exit(0);
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid choice! Press any key to try again.");
            utils::pauseScreen();
        }
    }
}

// inventory management menu
void inventoryManagementMenu() {}

// employee management menu
void employeeManagementMenu() {}

// customer management menu
void customerManagementMenu() {}

// my profile menu
void myProfileMenu() {}

// my shop menu
void myShopMenu() {}