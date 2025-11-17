// include header file
#include "../include/sales_interface.h"

// sales menu
void sales_interface::menu()
{
    std::string choice;

    std::map<int, std::string> options = {
        {1, "View Today's Sales Reports"},
        {2, "View All Sales Reports"},
        {3, "Search Annual Sales Report"},
        {4, "Search Monthly Sales Report"},
        {5, "Search Daily Sales Report"},
        {6, "Search Sales Report By ID"},
        {7, "Search Sales Report By Customer Name"},
        {8, "Go Back"},
    };

    while (true)
    {
        utility::header("SALES MENU");

        for (const auto &option : options)
            utility::showOption(option.first, option.second);

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
            sales_interface::viewTodaysSalesReport();
        else if (choice == "2")
            sales_interface::viewAllSalesReports();
        else if (choice == "3")
            sales_interface::searchAnnualSalesReport();
        else if (choice == "4")
            sales_interface::searchMonthlySalesReport();
        else if (choice == "5")
            sales_interface::searchDailySalesReport();
        else if (choice == "6")
            sales_interface::searchSalesReportById();
        else if (choice == "7")
            sales_interface::searchSalesReportByCustomerName();
        else if (choice == "8")
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

        valid_id = true;

        std::cout << "Enter sales ID to search :: ";
        std::getline(std::cin, buffer);

        try
        {
            id = std::stoi(buffer);
        }
        catch (const std::invalid_argument &e)
        {
            valid_id = false;
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid input!\n");
        }

        if (valid_id)
        {
            Sales sales;
            bool found = SalesManager::fetchSalesReportById(id, sales);

            std::cout << "\n";

            if (!found)
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "No sales report found!\n");
            else
            {
                std::cout << "Customer Name     :: " << CustomerManager::getCustomerName(sales.getSalesId()) << "\n";
                std::cout << "Employee ID       :: " << sales.getEmployeeId() << "\n";
                std::cout << "Employee Name     :: " << EmployeeManager::getEmployeeName(sales.getSalesId()) << "\n";
                std::cout << "Date              :: " << utility::getDateString(sales.getDate(), false) << "\n";
                std::cout << "Net Amount        :: " << sales.getNetAmount() << "\n";
                std::cout << "Discount          :: " << sales.getDiscount() << "%" << "\n";
                std::cout << "Gross Amount      :: " << sales.getGrossAmount() << "\n";
                std::cout << "Tender            :: " << sales.getTender() << "\n";
                std::cout << "Change            :: " << sales.getChange() << "\n";
            }
        }

        std::cout << "\nDo you want to search another sales report [y/n]? ";
        std::getline(std::cin, buffer);

        if (buffer != "Y" && buffer != "y")
            break;
    }
}

// search sales report by customer name
void sales_interface::searchSalesReportByCustomerName()
{
    std::vector<Sales> sales;
    std::string choice, name;

    while (true)
    {
        utility::header("SEARCH SALES REPORT BY CUSTOMER NAME");

        std::cout << "Enter customer name to search :: ";
        std::getline(std::cin, name);

        sales = SalesManager::fetchSalesReportsByCustomerName(name);

        std::cout << "\n";

        if (sales.empty())
            utility::showMessage(utility::MESSAGE_TYPE::INFO, "No sales report found!\n");
        else
            sales_interface::viewFormattedSalesReport(sales);

        std::cout << "\nDo you want to search another sales report [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "Y" && choice != "y")
            break;
    }
}

// view all sales reports
void sales_interface::viewAllSalesReports()
{
    std::vector<Sales> sales = SalesManager::fetchSalesReports(0, 0, 0);

    utility::header("ALL SALES REPORTS");

    if (sales.empty())
        utility::showMessage(utility::MESSAGE_TYPE::INFO, "No sales report found!\n");
    else
        sales_interface::viewFormattedSalesReport(sales);

    std::cout << "\nPress any key to continue...";

    utility::pauseScreen();
}

// view today's sales reports
void sales_interface::viewTodaysSalesReport()
{
    utility::header("TODAY'S SALES REPORT");

    std::array<int, 6> current_date_time = utility::getCurrentDateTime();

    std::vector<Sales> sales = SalesManager::fetchSalesReports(current_date_time[0], current_date_time[1], current_date_time[2]);

    if (sales.empty())
        utility::showMessage(utility::MESSAGE_TYPE::INFO, "No sales report found!\n");
    else
        sales_interface::viewFormattedSalesReport(sales);

    std::cout << "\nPress any key to continue...";

    utility::pauseScreen();
}

// view daily sales report
void sales_interface::searchDailySalesReport()
{
    int year, month, day;

    bool valid_date;

    std::string choice, buffer;

    while (true)
    {
        utility::header("DAILY SALES REPORT");

        valid_date = true;

        // get year
        std::cout << "Year      :: ";
        std::getline(std::cin, buffer);

        try
        {
            year = std::stoi(buffer);
        }
        catch (const std::invalid_argument &e)
        {
            valid_date = false;
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid input!\n");
        }

        if (valid_date)
        {
            // get month
            std::cout << "\nMonth     :: ";
            std::getline(std::cin, buffer);

            try
            {
                month = std::stoi(buffer);
            }
            catch (const std::invalid_argument &e)
            {
                valid_date = false;
                utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid input!\n");
            }

            if (valid_date)
            {
                // get day
                std::cout << "\nDay       :: ";
                std::getline(std::cin, buffer);

                try
                {
                    day = std::stoi(buffer);
                }
                catch (const std::invalid_argument &e)
                {
                    valid_date = false;
                    utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid input!\n");
                }

                if (valid_date)
                {
                    // get sales report
                    std::vector<Sales> sales = SalesManager::fetchSalesReports(year, month, day);

                    if (sales.empty())
                        utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nNo sales report found!\n");
                    else
                    {
                        utility::header("DAILY SALES REPORT");

                        std::cout << "Date :: " << year << "-" << month << "-" << day << "\n\n";

                        sales_interface::viewFormattedSalesReport(sales);
                    }
                }
            }
        }

        std::cout << "\nDo you want to search another saily sales report [y/n]? :: ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "Y")
            break;
    }
}

// view monthly sales report
void sales_interface::searchMonthlySalesReport()
{
    int year, month;
    bool valid_date;
    std::string choice, buffer;

    while (true)
    {
        utility::header("MONTHLY SALES REPORT");

        valid_date = true;

        // get year
        std::cout << "Year      :: ";
        std::getline(std::cin, buffer);

        try
        {
            year = std::stoi(buffer);
        }
        catch (const std::exception &e)
        {
            valid_date = false;
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid input!\n");
        }

        if (valid_date)
        {
            // get month
            std::cout << "\nMonth     :: ";
            std::getline(std::cin, buffer);

            try
            {
                month = std::stoi(buffer);
            }
            catch (const std::invalid_argument &e)
            {
                valid_date = false;
                utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid input!\n");
            }
        }

        if (valid_date)
        {
            std::vector<Sales> sales = SalesManager::fetchSalesReports(year, month, 0);

            if (sales.empty())
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nNo sales report found!\n");
            else
            {
                std::cout << "\n";
                sales_interface::viewFormattedSalesReport(sales);
            }
        }

        std::cout << "\nDo you want to search another saily sales report [y/n]? :: ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "Y")
            break;
    }
}

// search annual sales report
void sales_interface::searchAnnualSalesReport()
{
    int year;
    bool valid_date;
    std::string choice, buffer;

    std::vector<Sales> sales = {};

    while (true)
    {
        utility::header("ANNUAL SALES REPORT");

        // get year
        std::cout << "Year      :: ";
        std::getline(std::cin, buffer);

        try
        {
            year = std::stoi(buffer);
            valid_date = true;
        }
        catch (const std::exception &e)
        {
            valid_date = false;
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid input!\n");
        }

        if (valid_date)
        {
            sales = SalesManager::fetchSalesReports(year, 0, 0);

            if (sales.empty())
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nNo sales report found!\n");
            else
            {
                std::cout << "\n";
                sales_interface::viewFormattedSalesReport(sales);
            }
        }

        std::cout << "\nDo you want to search another sales report [y/n]? :: ";
        std::getline(std::cin, buffer);

        if (buffer != "y" && buffer != "Y")
            break;
    }
}

// view formatted sales report
void sales_interface::viewFormattedSalesReport(std::vector<Sales> sales)
{
    std::vector<int> spaces = {10, 20, 13, 12, 10, 14, 10, 10, 10};

    utility::showLine(spaces, {"Sales ID", "Customer Name", "Employee ID", "Net Amount", "Discount", "Gross Amount", "Tender", "Change", "Date"});

    for (Sales &sale : sales)
    {
        utility::showLine(spaces,
                          {
                              std::to_string(sale.getSalesId()),
                              CustomerManager::getCustomerName(sale.getSalesId()),
                              std::to_string(sale.getEmployeeId()),
                              utility::getFormattedDouble(sale.getNetAmount()),
                              utility::getFormattedDouble(sale.getDiscount()),
                              utility::getFormattedDouble(sale.getGrossAmount()),
                              utility::getFormattedDouble(sale.getTender()),
                              utility::getFormattedDouble(sale.getChange()),
                              utility::getDateString(sale.getDate(), false),
                          });
    }
}
