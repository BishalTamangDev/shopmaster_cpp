#include <iostream>
#include <thread>
#include <map>
#include <string>

// import user-defined files
#include "utils.h"
#include "file_setup.h"
#include "employee_view.h"
#include "inventory_view.h"
#include "sales_view.h"

// global variables
int current_emp_id = 0;

// function declarations
bool mainMenu();

// main
int main()
{
    // background process :: file setup
    std::thread file_setup(app_files::setup); // file setup thread
    file_setup.detach();                      // run file setup task in the background independently

    do
    {
        if (employee_view::login(current_emp_id))
        {
            utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nLogin successful!");
            utils::showMessage(MESSAGE_TYPE::INFO, "\n\nRedirecting to main menu...");
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\n\nLogin failed!");
            std::cout << "\n\nExiting the program...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
        }
    } while (mainMenu());

    mainMenu(); // main menu

    return 0;
}

// employee menu
bool mainMenu()
{
    std::string choice;

    const std::map<int, std::string> options = {
        {1, "Sell Product"},
        {2, "Search Product By ID"},
        {3, "Search Product By Name"},
        {4, "View Products"},
        {5, "View Today's Sales"},
        {6, "My Account Details"},
        {7, "Log Out"},
        {8, "Exit"},
    };

    while (true)
    {
        utils::header("EMPLOYEE MENU");

        for (const auto &option : options)
            utils::showOption(option.first, option.second);

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
            inventory_view::sell();
        else if (choice == "2")
            inventory_view::searchById();
        else if (choice == "3")
            inventory_view::searchByName();
        else if (choice == "4")
            inventory_view::viewProducts();
        else if (choice == "5")
            sales_view::viewTodaysSalesReport();
        else if (choice == "6")
            employee_view::showDetails(current_emp_id);
        else if (choice == "7") // log out
        {
            std::cout << "\nAre you sure you want to logout [y/n]? ";
            std::getline(std::cin, choice);

            if (choice == "y" || choice == "Y")
            {
                current_emp_id = 0;
                return true;
            }
            else
            {
                utils::showMessage(MESSAGE_TYPE::INFO, "\nLogging out aborted!");
                std::cout << "\n\nPress any key to continue...";
                utils::pauseScreen();
            }
        }
        else if (choice == "7")
            exit(0);
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            utils::pauseScreen();
        }
    }
    return false;
}