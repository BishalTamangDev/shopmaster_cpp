#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>

// importing user-defined files
#include "utils.h"
#include "file_setup.h"
#include "admin.h"

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

    Admin admin;

    // check if admain has been registered yet
    if (!admin.isRegistered())
    {
        if (admin.registerAdmin())
        {
            utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nAdmin been registered successfully. Press any key to login.");
            utils::pauseScreen();
        }
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nAdmin registration failed!");
            utils::pauseScreen();
            exit(1);
        }
    }

    // login
    int chance = 3;

    while (true)
    {
        utils::clearScreen();

        if (admin.loginAdmin())
        {
            utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nLogin successful!");
            utils::showMessage(MESSAGE_TYPE::INFO, "\n\nRedirecting to main menu...");
            std::this_thread::sleep_for(std::chrono::seconds(1));
            menu();
        }
        else
        {
            chance--;

            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid username or password!");

            if (chance > 0)
            {
                std::string choice;

                std::cout << "\n\nDo you want to try again [y/n]? :: ";
                std::getline(std::cin, choice);

                if (choice != "Y" && choice != "y")
                {
                    utils::showMessage(MESSAGE_TYPE::INFO, "\nExiting program...\n");
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    break;
                }
            }
            else
            {
                utils::showMessage(MESSAGE_TYPE::INFO, "\n\nYou entered your credentials 3 times incorrectly!");
                utils::showMessage(MESSAGE_TYPE::INFO, "\n\nExiting program...\n");
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
            }
        }
    }

    return 0;
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
        {
            utils::showMessage(MESSAGE_TYPE::INFO, "\nExiting program...\n");
            std::this_thread::sleep_for(std::chrono::seconds(1));
            exit(0);
        }
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