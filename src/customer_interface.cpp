// include header file
#include "../include/customer_interface.h"

// admin menu
void customer_interface::adminMenu()
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
        utility::header("CUSTOMER MANAGEMENT MENU");

        for (const auto &option : options)
            utility::showOption(option.first, option.second);

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
            customer_interface::viewAll();
        else if (choice == "2")
            customer_interface::searchBySalesId();
        else if (choice == "3")
            customer_interface::searchByName();
        else if (choice == "4")
            return;
        else
        {
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            utility::pauseScreen();
        }
    }
}

// view all customer
void customer_interface::viewAll()
{
    utility::header("ALL CUSTOMERS");

    std::vector<Customer> customers = CustomerManager::fetchAllCustomers();

    if (customers.size() == 0)
        utility::showMessage(utility::MESSAGE_TYPE::INFO, "No customers found!\n");
    else
    {
        utility::showLine({11, 25}, {"Sales ID", "Name"});
        for (Customer customer : customers)
            utility::showLine({11, 25}, {std::to_string(customer.getSalesId()), customer.getName()});
    }

    std::cout << "\nPress any key to continue...";
    utility::pauseScreen();
}

// search customer by sales id
void customer_interface::searchBySalesId()
{
    int sales_id;
    bool found, valid_id;
    std::string sales_id_str, choice;

    std::vector<Customer> customers = CustomerManager::fetchAllCustomers();

    while (true)
    {
        found = false;
        valid_id = true;

        utility::header("SEARCH CUSTOMER BY SALES ID");

        if (customers.size() == 0)
        {
            utility::showMessage(utility::MESSAGE_TYPE::INFO, "No customers found!");
            std::cout << "\n\nPress any key to continue...";
            utility::pauseScreen();
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
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid input");
        }

        if (valid_id) // search
        {
            for (Customer customer : customers)
            {
                if (customer.getSalesId() == sales_id)
                {
                    found = true;
                    utility::showMessage(utility::MESSAGE_TYPE::SUCCESS, "\nCustomer found!");
                    std::cout << "\n\nSales ID     :: " << sales_id;
                    std::cout << "\n\nName         :: " << customer.getName();
                    break;
                }
            }

            if (!found)
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nCustomer not found!");
        }

        std::cout << "\n\nDo you want to search another customer [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "Y")
            break;
    }
}

// search customer by name
void customer_interface::searchByName()
{
    bool found;
    std::string name, target_name, choice;

    std::vector<Customer> customers = CustomerManager::fetchAllCustomers();

    while (true)
    {
        found = false;

        utility::header("SEARCH CUSTOMER BY NAME");

        if (customers.size() == 0)
        {
            utility::showMessage(utility::MESSAGE_TYPE::INFO, "No customers found!");
            std::cout << "\n\nPress any key to continue...";
            utility::pauseScreen();
            break;
        }

        std::cout << "Enter customer name to search :: ";
        std::getline(std::cin, target_name);

        std::cout << "\n";
        utility::showLine({11, 25}, {"Sales ID", "Name"});

        for (Customer &customer : customers)
        {
            name = customer.getName();
            utility::convertToLowerCase(name);
            utility::convertToLowerCase(target_name);

            if (name.find(target_name) != std::string::npos)
            {
                found = true;
                utility::showLine({11, 25}, {std::to_string(customer.getSalesId()), customer.getName()});
            }
        }

        if (!found)
            utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nCustomer not found!\n");

        std::cout << "\nDo you want to search another customer [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "Y")
            break;
    }
}