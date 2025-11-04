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

void myProfileMenu();       // my profile menu
void updateUsername(Admin); // update username
void updatePassword(Admin); // update password
void updateName(Admin);     // update admin name

void myShopMenu(); // my shop menu

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
void myProfileMenu()
{
    Admin admin;

    while (true)
    {
        admin.fetchDetails(); // fetch admin details

        utils::clearScreen();

        utils::header("MY PROFILE");

        // show details
        std::cout << "Username :: " << admin.getUsername() << "\n";
        std::cout << "Name     :: " << admin.getFullName() << "\n\n";

        // options
        std::map<int, std::string> options = {
            {1, "Update Username"},
            {2, "Update Password"},
            {3, "Update Name"},
            {4, "Go Back"},
        };

        for (const auto &option : options)
            utils::showOption(option.first, option.second);

        std::string choice;

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
            updateUsername(admin);
        else if (choice == "2")
            updatePassword(admin);
        else if (choice == "3")
            updateName(admin);
        else if (choice == "4")
            break;
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\n\nInvalid choice!");
            utils::pauseScreen();
        }
    }
}

// update username
void updateUsername(Admin admin)
{
    std::string choice;
    std::string new_username;

    while (true)
    {
        utils::clearScreen();

        utils::header("UPDATE USERNAME");

        std::cout << "Old username       :: " << admin.getUsername() << "\n\n";

        std::cout << "Enter new username :: ";
        std::getline(std::cin, new_username);

        if (new_username == admin.getUsername())
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nYou entered old username!");

            std::cout << "\n\nDo you want to try again [y/n]? ";
            std::getline(std::cin, choice);

            if (choice != "Y" && choice != "y")
                break;
            else
                continue;
        }

        std::cout << "\nNew username       :: " << new_username;

        admin.setUsername(new_username); // set new username

        // proceed update
        if (admin.update())
            utils::showMessage(MESSAGE_TYPE::SUCCESS, "\n\nUsername updated successfully!");
        else
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\n\nUsername updation failed!");

        utils::showMessage(MESSAGE_TYPE::INFO, "\n\nPress any key to continue...");

        utils::pauseScreen();

        break;
    }
}

// update password
void updatePassword(Admin admin)
{
    std::string choice;
    std::string old_password, new_password, new_password_confirmation;

    while (true)
    {
        utils::clearScreen();

        utils::header("UPDATE PASSWORD");

        // get old password
        std::cout << "Enter old password :: ";
        std::getline(std::cin, old_password);

        if (old_password != admin.getPassword())
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid password!");

            std::cout << "\n\nDo you want to try again [y/n]? ";
            std::getline(std::cin, choice);

            if (choice != "Y" && choice != "y")
                break;
            else
                continue;
        }

        std::cout << "\nEnter new password :: ";
        std::getline(std::cin, new_password);

        if (new_password == admin.getPassword())
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nYou entered old password!");
            std::cout << "\n\nPress any key to go back...";
            utils::pauseScreen();
            break;
        }

        std::cout << "\nEnter again for confirmation :: ";
        std::getline(std::cin, new_password_confirmation);

        if (new_password != new_password_confirmation)
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nPassword confirmation failed!");
            std::cout << "\n\nPress any key to go back...";
            utils::pauseScreen();
            break;
        }

        admin.setPassword(new_password); // set new password

        // proceed update
        if (admin.update())
            utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nPassword updated successfully!");
        else
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nPassword updation failed!");

        utils::showMessage(MESSAGE_TYPE::INFO, "\n\nPress any key to continue...");

        utils::pauseScreen();

        break;
    }
}

// update name
void updateName(Admin admin)
{
    utils::clearScreen();
    utils::header("UPDATE NAME");
    std::string first_name, middle_name, last_name;

    std::cout << "Old name :: " << admin.getFullName();

    std::cout << "\n\nFirst name :: ";
    std::getline(std::cin, first_name);
    admin.setFirstName(first_name);

    std::cout << "\nMiddle name [Press enter if you don't have a middle name] :: ";
    std::getline(std::cin, middle_name);
    admin.setMiddleName(middle_name);

    std::cout << "\nLast name :: ";
    std::getline(std::cin, last_name);
    admin.setLastName(last_name);

    std::cout << "\nNew name :: " << admin.getFullName();

    if (admin.update())
        utils::showMessage(MESSAGE_TYPE::SUCCESS, "\n\nName updated successfully!");
    else
        utils::showMessage(MESSAGE_TYPE::FAILURE, "\n\nName updation failed!");

    utils::showMessage(MESSAGE_TYPE::INFO, "\n\nPress any key to continue...");

    utils::pauseScreen();
}

// my shop menu
void myShopMenu() {}