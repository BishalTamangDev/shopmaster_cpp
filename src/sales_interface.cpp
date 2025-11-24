// include header file
#include "../include/sales_interface.h"

// sales menu
void sales_interface::menu()
{
    std::string choice;

    std::map<int, std::string> options = {
        {1, "View Today's Sales Reports"},
        {2, "Search Invoice"},
        {3, "Search Sales Report By Customer Name"},
        {4, "View All Sales Reports"},
        {5, "Search Annual Sales Report"},
        {6, "Search Monthly Sales Report"},
        {7, "Search Daily Sales Report"},
        {8, "Go Back"},
    };

    while (true)
    {
        utility::header("SALES MENU");

        for (const auto &option : options)
        {
            utility::showOption(option.first, option.second);
        }

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
        {
            sales_interface::viewTodaysSalesReport();
        }
        else if (choice == "2")
        {
            sales_interface::searchInvoice();
        }
        else if (choice == "3")
        {
            sales_interface::searchSalesReportByCustomerName();
        }
        else if (choice == "4")
        {
            sales_interface::viewAllSalesReports();
        }
        else if (choice == "5")
        {
            sales_interface::searchAnnualSalesReport();
        }
        else if (choice == "6")
        {
            sales_interface::searchMonthlySalesReport();
        }
        else if (choice == "7")
        {
            sales_interface::searchDailySalesReport();
        }
        else if (choice == "8")
        {
            return;
        }
        else
        {
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            std::cout << "\n\nPress any key to try again...";
            utility::pauseScreen();
        }
    }
}

// view sales report by id
void sales_interface::searchInvoice()
{
    int id;
    bool valid_id;

    std::string buffer;

    while (true)
    {
        utility::header("SEARCH INVOICE");

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
            {
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "No invoice found!\n");
            }
            else
            {
                Customer customer;

                CustomerManager customerManager;

                bool response = customerManager.fetchCustomerBySalesId(sales.getSalesId(), customer); // fetch customer by sales id

                if (!response)
                {
                    customer.setName("Unknown");
                }

                ProductManager productManager;

                std::vector<Product> cart = productManager.fetchSoldProductsBySalesId(sales.getSalesId());

                sales_interface::showInvoice(sales, cart, customer); // generate invoice
            }
        }

        std::cout << "\nDo you want to search another invoice [y/n]? ";
        std::getline(std::cin, buffer);

        if (buffer != "Y" && buffer != "y")
        {
            break;
        }
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
        {
            utility::showMessage(utility::MESSAGE_TYPE::INFO, "No sales report found!\n");
        }
        else
        {
            sales_interface::viewFormattedSalesReport(sales);
        }

        std::cout << "\nDo you want to search another sales report [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "Y" && choice != "y")
        {
            break;
        }
    }
}

// view all sales reports
void sales_interface::viewAllSalesReports()
{
    std::vector<Sales> sales = SalesManager::fetchSalesReports(0, 0, 0);

    utility::header("ALL SALES REPORTS");

    if (sales.empty())
    {
        utility::showMessage(utility::MESSAGE_TYPE::INFO, "No sales report found!\n");
    }
    else
    {
        sales_interface::viewFormattedSalesReport(sales);
    }

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
    {
        utility::showMessage(utility::MESSAGE_TYPE::INFO, "No sales report found!\n");
    }
    else
    {
        sales_interface::viewFormattedSalesReport(sales);
    }

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
                    {
                        utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nNo sales report found!\n");
                    }
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
        {
            break;
        }
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
            {
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nNo sales report found!\n");
            }
            else
            {
                std::cout << "\n";
                sales_interface::viewFormattedSalesReport(sales);
            }
        }

        std::cout << "\nDo you want to search another saily sales report [y/n]? :: ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "Y")
        {
            break;
        }
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
            {
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nNo sales report found!\n");
            }
            else
            {
                std::cout << "\n";
                sales_interface::viewFormattedSalesReport(sales);
            }
        }

        std::cout << "\nDo you want to search another sales report [y/n]? :: ";
        std::getline(std::cin, buffer);

        if (buffer != "y" && buffer != "Y")
        {
            break;
        }
    }
}

// view formatted sales report
void sales_interface::viewFormattedSalesReport(std::vector<Sales> sales)
{
    double total_net_amount = 0.0;
    double total_gross_amount = 0.0;

    std::cout << std::left << std::setw(10) << "Sales ID"
              << std::setw(25) << "Customer Name"
              << std::setw(8) << "Emp ID"
              << std::setw(10) << std::right << "Net Amount" << "  "
              << std::setw(10) << "Discount (%)" << "  "
              << std::setw(12) << "Gross Amount" << "  "
              << std::setw(8) << "Tender" << "  "
              << std::setw(8) << "Change" << "  "
              << std::left << "Date" << "\n";

    for (Sales &sale : sales)
    {
        total_net_amount += sale.getNetAmount();
        total_gross_amount += sale.getGrossAmount();

        std::cout << std::left << std::setw(10) << sale.getSalesId()
                  << std::setw(25) << CustomerManager::getCustomerName(sale.getSalesId())
                  << std::setw(8) << sale.getEmployeeId()
                  << std::setw(10) << std::right << sale.getNetAmount() << "  "
                  << std::setw(12) << sale.getDiscount() << "  "
                  << std::setw(12) << sale.getGrossAmount() << "  "
                  << std::setw(8) << sale.getTender() << "  "
                  << std::setw(8) << sale.getChange() << "  "
                  << std::left << utility::getDateString(sale.getDate(), false) << "\n";
    }

    std::cout << "\nTotal net amount     :: " << total_net_amount;
    std::cout << "\nTotal gross amount   :: " << total_gross_amount << "\n";
}

// show invoice
void sales_interface::showInvoice(Sales sales, std::vector<Product> cart, Customer customer)
{

    utility::header("INVOICE");

    // show shop details
    Shop shop;
    ShopManager shopManager;

    bool response = shopManager.fetch(shop);

    if (!response)
    {
        utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "Shop details not found!");
        std::cout << "\nPress any key to continue...";
        utility::pauseScreen();
        return;
    }

    std::cout << shop.getName() << "\n";
    std::cout << shop.getAddress() << "\n";
    std::cout << "Contact No. " << shop.getContactNumber() << "\n";
    std::cout << "PAN " << shop.getPan() << "\n\n";

    // show customer details
    std::cout << "Customer name :: " << customer.getName() << "\n\n";

    std::cout << std::left << std::setw(6) << "ID"
              << std::setw(25) << "Name"
              << std::setw(10) << std::right << "Rate" << "  "
              << std::setw(7) << "Qty" << "  "
              << std::setw(10) << "Total" << "\n";

    for (Product product : cart)
    {
        double total = product.getRate() * product.getQuantity();

        std::cout << std::left << std::setw(6) << product.getId()
                  << std::setw(25) << product.getName()
                  << std::setw(10) << std::right << product.getRate() << "  "
                  << std::setw(7) << product.getQuantity() << "  "
                  << std::setw(10) << total << "\n";
    }

    std::cout << "\nNet amount        :: " << sales.getNetAmount();
    std::cout << "\nDiscount          :: " << sales.getDiscount() << "%";
    std::cout << "\nGross amount      :: " << sales.getGrossAmount();
    std::cout << "\nTender            :: " << sales.getTender();
    std::cout << "\nChange            :: " << sales.getChange() << "\n";
}

// save invoice
bool sales_interface::saveInvoice(Sales sales, std::vector<Product> cart, Customer customer)
{
    // customer
    CustomerManager customerManager;
    bool customer_response = customerManager.add(customer);

    // sales
    SalesManager salesManager;
    bool sales_response = salesManager.add(sales);

    // sold products
    ProductManager productManager;
    bool sold_product_response = productManager.sellProduct(cart);

    return customer_response && sales_response && sold_product_response;
}
