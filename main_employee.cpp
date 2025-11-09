#include <iostream>
#include <thread>
#include <map>
#include <string>

// import user-defined files
#include "utils.h"
#include "file_setup.h"
#include "employee.h"

// global variables
int current_emp_id = 0;

// function declarations
namespace ns_employee
{
    bool menu();        // menu
    bool login();       // login
    void showDetails(); // my details
}

// namespace :: inventory
namespace ns_inventory
{
    void sellProduct();    // sell product
    void searchProduct();  // search product
    void viewProducts();   // view products
    void viewTodaySales(); // view today's sales
}

// main
int main()
{
    std::thread file_setup(app_files::setup); // file setup thread
    file_setup.detach();                      // run file setup task in the background independently

    do
    {
        if (ns_employee::login())
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
    } while (ns_employee::menu());

    return 0;
}

// employee section
// employee :: login
bool ns_employee::login()
{
    int chance = 3;
    bool status = false;
    std::string username, password;
    Employee employee;

    while (true)
    {
        chance--;

        utils::header("EMPLOYEE LOGIN");

        std::cout << "Username :: ";
        std::getline(std::cin, username);

        std::cout << "\nPassword :: ";
        std::getline(std::cin, password);

        if (employee.login(username, password, current_emp_id))
        {
            status = true;
            break;
        }

        utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid username or password!");

        if (chance == 0)
        {
            utils::showMessage(MESSAGE_TYPE::INFO, "\n\nYou entered your credentials 3 times incorrectly!");
            break;
        }

        std::cout << "\n\nPress any key to try again...";
        utils::pauseScreen();
    }

    return status;
}

// employee :: menu
bool ns_employee::menu()
{
    std::string choice;

    const std::map<int, std::string> options = {
        {1, "Sell Product"},
        {2, "Search Product"},
        {3, "View Products"},
        {4, "View Today's Sales"},
        {5, "My Account Details"},
        {6, "Log Out"},
        {7, "Exit"},
    };

    while (true)
    {
        utils::header("EMPLOYEE MENU");

        for (const auto &option : options)
            utils::showOption(option.first, option.second);

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
            ns_inventory::sellProduct();
        else if (choice == "2")
            ns_inventory::searchProduct();
        else if (choice == "3")
            ns_inventory::viewProducts();
        else if (choice == "4")
            ns_inventory::viewTodaySales();
        else if (choice == "5")
            ns_employee::showDetails();
        else if (choice == "6")
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

// employee :: show details
void ns_employee::showDetails()
{
    utils::header("MY ACCOUNT DETAILS");
    utils::pauseScreen();
}

// inventory section
// inventory :: sell product
void ns_inventory::sellProduct()
{
    utils::header("SELL PRODUCT");
    utils::pauseScreen();
}

// inventory :: search product
void ns_inventory::searchProduct()
{
    utils::header("SEARCH PRODUCT");
    utils::pauseScreen();
}

// inventory :: view products
void ns_inventory::viewProducts()
{
    utils::header("ALL PRODUCTS");
    utils::pauseScreen();
}

// inventory :: view today's sales
void ns_inventory::viewTodaySales()
{
    utils::header("TODAY'S SALES");
    utils::pauseScreen();
}