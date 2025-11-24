// include header files
#include "../include/project_setup.h"
#include "../include/admin_interface.h"
#include "../include/shop_interface.h"
#include "../include/employee_interface.h"
#include "../include/customer_interface.h"
#include "../include/product_interface.h"
#include "../include/inventory_interface.h"
#include "../include/sales_interface.h"

// global variable
int current_emp_id = 0;

// function declarations
void mainMenu(); // main menu

void adminMain(); // admin main
void adminMenu(); // admin main menu

void employeeMenu(); // employee main main

// main function
int main()
{
    std::filesystem::path folder = "data";

    // Create directory if it doesn't exist
    if (!std::filesystem::exists(folder))
    {
        std::filesystem::create_directory(folder);
    }

    // Change working directory into the folder
    std::filesystem::current_path(folder);

    // background process :: file setup
    std::thread project_setup_thread(project_setup::fileSetup); // file setup thread
    project_setup_thread.detach();

    mainMenu(); // main menu

    return 0;
}

// main menu
void mainMenu()
{
    bool login_status;
    std::string choice;

    const std::map<int, std::string> options = {
        {1, "Admin"},
        {2, "Employee"},
        {3, "Exit"},
    };

    while (true)
    {
        utility::header("LOGIN AS");

        for (const auto &option : options)
        {
            utility::showOption(option.first, option.second);
        }

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
        {
            adminMain();
        }
        else if (choice == "2")
        {
            login_status = employee_interface::login(current_emp_id);

            if (login_status)
            {
                employeeMenu();
            }
        }
        else if (choice == "3")
        {
            exit(0);
        }
        else
        {
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            std::cout << "\n\nPress any key to try again...";
            utility::pauseScreen();
        }
    };
}

// admin main menu
void adminMain()
{
    AdminManager adminManager;

    // check if admain has been registered yet
    if (!adminManager.registrationStatus())
    {
        if (admin_interface::registration())
        {
            utility::showMessage(utility::MESSAGE_TYPE::SUCCESS, "\nAdmin registered successfully. Press any key to login.");
            utility::pauseScreen();
        }
        else
        {
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nAdmin registration failed!");
            utility::pauseScreen();
            exit(1);
        }
    }

    // login
    int chance = 3;
    bool login_success = false;

    while (true)
    {
        utility::clearScreen();

        if (admin_interface::login())
        {
            utility::showMessage(utility::MESSAGE_TYPE::SUCCESS, "\nLogin successful!");
            login_success = true;
            break;
        }
        else
        {
            chance--;

            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid username or password!");

            if (chance > 0)
            {
                std::string choice;

                std::cout << "\n\nDo you want to try again [y/n]? :: ";
                std::getline(std::cin, choice);

                if (choice != "Y" && choice != "y")
                {
                    return;
                }
            }
            else
            {
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\n\nYou entered your credentials 3 times incorrectly!");
                std::cout << "\n\nExiting program...\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                exit(0);
            }
        }
    }

    if (login_success)
    {
        ShopManager shopManager;

        if (!shopManager.registrationStatus())
        {
            if (!shop_interface::registration())
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                exit(1);
            }
        }

        std::cout << "\n\nRedirecting to main menu...";

        std::this_thread::sleep_for(std::chrono::seconds(1));

        adminMenu();
    }
}

// admin menu
void adminMenu()
{
    std::string choice;

    std::map<int, std::string> options = {
        {1, "Product Management"},
        {2, "Sales Management"},
        {3, "Employee Management"},
        {4, "Customer Management"},
        {5, "My Profile"},
        {6, "My Shop"},
        {7, "Log Out"},
        {8, "Exit"},
    };

    while (true)
    {
        utility::clearScreen();

        utility::header("ADMIN MENU");

        for (const auto &option : options)
        {
            utility::showOption(option.first, option.second);
        }

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
        {
            product_interface::menu();
        }
        else if (choice == "2")
        {
            sales_interface::menu();
        }
        else if (choice == "3")
        {
            employee_interface::adminMenu();
        }
        else if (choice == "4")
        {
            customer_interface::adminMenu();
        }
        else if (choice == "5")
        {
            admin_interface::profileMenu();
        }
        else if (choice == "6")
        {
            shop_interface::menu();
        }
        else if (choice == "7")
        {
            std::cout << "\nAre you sure you want to log out [y/n]? ";
            std::getline(std::cin, choice);

            if (choice == "y" || choice == "Y")
            {
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nLogging out...");
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return;
            }
            else
            {
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nLogging out aborted");
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }
        }
        else if (choice == "8")
        {
            std::cout << "\nExiting the program...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            exit(0);
        }
        else
        {
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid choice! Press any key to try again.");
            utility::pauseScreen();
        }
    }
}

// employee menu
void employeeMenu()
{
    std::string choice;

    const std::map<int, std::string> options = {
        {1, "Sell Product"},
        {2, "Search Invoice"},
        {3, "View Today's Sales"},
        {4, "View All Products"},
        {5, "Search Product By ID"},
        {6, "Search Product By Name"},
        {7, "My Account Details"},
        {8, "Log Out"},
        {9, "Exit"},
    };

    while (true)
    {
        utility::header("EMPLOYEE MENU");

        for (const auto &option : options)
        {
            utility::showOption(option.first, option.second);
        }

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
        {
            inventory_interface::sell(current_emp_id);
        }
        else if (choice == "2")
        {
            sales_interface::searchInvoice();
        }
        else if (choice == "3")
        {
            sales_interface::viewTodaysSalesReport();
        }
        else if (choice == "4")
        {
            product_interface::viewAllProducts();
        }
        else if (choice == "5")
        {
            product_interface::searchById();
        }
        else if (choice == "6")
        {
            product_interface::searchByName();
        }
        else if (choice == "7")
        {
            employee_interface::showDetails(current_emp_id);
        }
        else if (choice == "8") // log out
        {
            std::cout << "\nAre you sure you want to logout [y/n]? ";
            std::getline(std::cin, choice);

            if (choice == "y" || choice == "Y")
            {
                current_emp_id = 0;
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nLogging out...");
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return;
            }
            else
            {
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nLogging out aborted!");
                std::cout << "\n\nPress any key to continue...";
                utility::pauseScreen();
            }
        }
        else if (choice == "8")
        {
            std::cout << "\nExiting the program...";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            exit(0);
        }
        else
        {
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            utility::pauseScreen();
        }
    }
}
