#include <iostream>

// import user-defined header file
#include "customer_class.h"

#ifndef SHOPMASTER_CUSTOMER_VIEW_H
#define SHOPMASTER_CUSTOMER_VIEW_H

// namespace :: customer
namespace customer_view
{
    void adminMenu();       // menu
    void viewAll();         // view all customer
    void searchBySalesId(); // search by sales id
    void searchByName();    // search by name
};

// section :: customer
// customer :: menu
void customer_view::adminMenu()
{
    std::string choice;

    const std::map<int, std::string> options = {
        {1, "View Customer"},
        {2, "Search Customer by Sales ID"},
        {3, "Search Customer by Name"},
        {4, "Go Back"},
    };

    while (true)
    {
        utils::header("CUSTOMER view MENU");

        for (const auto &option : options)
            utils::showOption(option.first, option.second);

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
            customer_view::viewAll();
        else if (choice == "2")
            customer_view::searchBySalesId();
        else if (choice == "3")
            customer_view::searchByName();
        else if (choice == "4")
            return;
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            utils::pauseScreen();
        }
    }
}

// view all customer
void customer_view::viewAll()
{
    utils::header("ALL CUSTOMERS");

    std::vector<Customer> customers = Customer::fetchAllCustomers();

    if (customers.size() == 0)
        utils::showMessage(MESSAGE_TYPE::INFO, "No customers found!\n");
    else
    {
        utils::showLine({11, 25}, {"Sales ID", "Name"});
        for (Customer customer : customers)
            utils::showLine({11, 25}, {std::to_string(customer.getSalesId()), customer.getName()});
    }

    std::cout << "\nPress any key to continue...";
    utils::pauseScreen();
}

// search by sales id
void customer_view::searchBySalesId()
{
    int sales_id;
    bool found, valid_id;
    std::string sales_id_str, choice;

    std::vector<Customer> customers = Customer::fetchAllCustomers();

    while (true)
    {
        found = false;
        valid_id = true;

        utils::header("SEARCH CUSTOMER BY SALES ID");

        if (customers.size() == 0)
        {
            utils::showMessage(MESSAGE_TYPE::INFO, "No customers found!");
            std::cout << "\n\nPress any key to continue...";
            utils::pauseScreen();
            break;
        }

        std::cout << "Enter sales ID to search :: ";
        std::getline(std::cin, sales_id_str);

        try
        {
            sales_id = std::stoi(sales_id_str);
        }
        catch (const std::invalid_argument &e)
        {
            valid_id = false;
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid input");
        }

        if (valid_id) // search
        {
            for (Customer customer : customers)
            {
                if (customer.getSalesId() == sales_id)
                {
                    found = true;
                    utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nCustomer found!");
                    std::cout << "\n\nSales ID     :: " << sales_id;
                    std::cout << "\n\nName         :: " << customer.getName();
                    break;
                }
            }

            if (!found)
                utils::showMessage(MESSAGE_TYPE::INFO, "\nCustomer not found!");
        }

        std::cout << "\n\nDo you want to search another customer [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "Y")
            break;
    }
}

// search by name
void customer_view::searchByName()
{
    bool found;
    std::string name, target_name, choice;

    std::vector<Customer> customers = Customer::fetchAllCustomers();

    while (true)
    {
        found = false;

        utils::header("SEARCH CUSTOMER BY NAME");

        if (customers.size() == 0)
        {
            utils::showMessage(MESSAGE_TYPE::INFO, "No customers found!\n");
            std::cout << "\n\nPress any key to continue...";
            break;
        }

        std::cout << "Enter customer name to search :: ";
        std::getline(std::cin, target_name);

        std::cout << "\n";
        utils::showLine({11, 25}, {"Sales ID", "Name"});

        for (Customer &customer : customers)
        {
            name = customer.getName();
            utils::convertToLowerCase(name);
            utils::convertToLowerCase(target_name);

            if (name.find(target_name) != std::string::npos)
            {
                found = true;
                utils::showLine({11, 25}, {std::to_string(customer.getSalesId()), customer.getName()});
            }
        }

        if (!found)
            utils::showMessage(MESSAGE_TYPE::INFO, "\nCustomer not found!\n");

        std::cout << "\nDo you want to search another customer [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "Y")
            break;
    }
}

#endif