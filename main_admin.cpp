#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>

// importing user-defined files
#include "utils.h"
#include "file_setup.h"
#include "admin_view.h"
#include "shop_view.h"
#include "employee_view.h"
#include "inventory_view.h"
#include "customer_view.h"

// function declarations
void mainMenu(); // main menu

// main function
int main()
{
    // background process :: file setup
    std::thread file_setup(app_files::setup); // file setup thread
    file_setup.detach();

    // check if admain has been registered yet
    if (!admin_utility::adminRegistered())
    {
        if (admin_view::registration())
        {
            utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nAdmin registered successfully. Press any key to login.");
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
    bool login_success = false;
    int chance = 3;

    while (true)
    {
        utils::clearScreen();

        if (admin_view::login())
        {
            utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nLogin successful!");
            login_success = true;
            break;
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

    if (login_success)
    {
        if (!shop_utility::isRegistered())
        {
            if (!shop_view::registration())
            {
                std::this_thread::sleep_for(std::chrono::seconds(2));
                exit(1);
            }
        }

        utils::showMessage(MESSAGE_TYPE::INFO, "\n\nRedirecting to main menu...");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        mainMenu();
    }

    return 0;
}

// main menu
void mainMenu()
{
    std::string choice;

    std::map<int, std::string> options = {
        {1, "Inventory view"},
        {2, "Employee view"},
        {3, "Customer view"},
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
            inventory_view::adminMenu();
        else if (choice == "2")
            employee_view::adminMenu();
        else if (choice == "3")
            customer_view::adminMenu();
        else if (choice == "4")
            admin_view::profileMenu();
        else if (choice == "5")
            shop_view::menu();
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