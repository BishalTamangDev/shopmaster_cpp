// include header file
#include "../include/sales_interface.h"

// sales menu
void sales_interface::menu()
{
    std::string choice;

    std::map<int, std::string> options = {
        {1, "View Daily Sales Report"},
        {2, "View Monthly Sales Report"},
        {3, "View Annual Sales Report"},
        {4, "Search Sales Report"},
        {5, "Go Back"},
    };

    while (true)
    {
        utility::header("SALES MENU");

        for (const auto &option : options)
            utility::showOption(option.first, option.second);

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
            sales_interface::viewDailySalesReport();
        else if (choice == "2")
            sales_interface::viewMonthlySalesReport();
        else if (choice == "3")
            sales_interface::viewAnnualSalesReport();
        else if (choice == "4")
            sales_interface::searchSalesReportById();
        else if (choice == "5")
            return;
        else
        {
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            std::cout << "\n\nPress any key to try again...";
            utility::pauseScreen();
        }
    }
}

// view sales report by id
void sales_interface::searchSalesReportById()
{
    int id;
    bool valid_id;
    std::string buffer;

    while (true)
    {
        utility::header("SEARCH SALES REPORT");

        std::cout << "Enter sales ID to search :: ";
        std::getline(std::cin, buffer);

        try
        {
            id = std::stoi(buffer);
            valid_id = true;
        }
        catch (const std::invalid_argument &e)
        {
            valid_id = false;
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid input!");
        }

        if (valid_id)
        {
            // main logic
            std::cout << "SALES ID :: " << id << "\n";
        }

        std::cout << "\nDo you want to search another sales report [y/n]? ";
        std::getline(std::cin, buffer);

        if (buffer != "Y" && buffer != "y")
            break;
    }
}

// view daily sales report
void sales_interface::viewDailySalesReport()
{
    utility::header("DAILY SALES REPORT");

    std::array<int, 6> current_date_time = utility::getCurrentDateTime();

    std::cout << utility::getDateString(current_date_time, true);

    utility::pauseScreen();
}

// view daily sales report
void sales_interface::viewMonthlySalesReport()
{
    utility::header("MONTHLY SALES REPORT");

    std::array<int, 6> current_date_time = utility::getCurrentDateTime();

    std::cout << utility::getDateString(current_date_time, true);

    utility::pauseScreen();
}

// view daily sales report
void sales_interface::viewAnnualSalesReport()
{
    utility::header("ANNUAL SALES REPORT");

    std::array<int, 6> current_date_time = utility::getCurrentDateTime();

    std::cout << utility::getDateString(current_date_time, true);

    utility::pauseScreen();
}