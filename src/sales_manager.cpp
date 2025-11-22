// include header file
#include "../include/sales_manager.h"
#include "../include/product_manager.h"
#include "../include/customer_manager.h"

// add new sales
bool SalesManager::add(Sales sales)
{
    std::ofstream fout(project_setup::filenames["sales"], std::ios::app);

    fout << sales.getSalesId() << ","
         << sales.getEmployeeId() << ","
         << sales.getNetAmount() << ","
         << sales.getDiscount() << ","
         << sales.getGrossAmount() << ","
         << sales.getTender() << ","
         << sales.getChange() << ","
         << utility::getDateString(sales.getDate(), true) << "\n";

    bool status = fout.good();

    fout.close();

    return status;
}

// generate sales id
int SalesManager::generateId()
{
    int id = 1;

    std::vector<Sales> all_sales = SalesManager::fetchSalesReports(0, 0, 0);

    for (Sales sales : all_sales)
        if (sales.getSalesId() >= id)
            id = sales.getSalesId() + 1;

    return id;
}

// get sales by sales id
bool SalesManager::fetchSalesReportById(int sales_id, Sales &sales)
{
    bool found = false;

    std::vector<Sales> all_sales = SalesManager::fetchSalesReports(0, 0, 0);

    for (Sales temp : all_sales)
    {
        if (temp.getSalesId() == sales_id)
        {
            sales = temp;
            found = true;
            break;
        }
    }

    return found;
}

// fetch sales by customer name
std::vector<Sales> SalesManager::fetchSalesReportsByCustomerName(std::string target_name)
{
    std::string name;

    std::vector<Sales> list;
    std::vector<Sales> all_sales = SalesManager::fetchSalesReports(0, 0, 0);

    std::vector<Customer> all_customers = CustomerManager::fetchAllCustomers();

    utility::convertToLowerCase(target_name); // convert targeted customer name into lowercase

    for (Sales sales : all_sales)
    {
        for (Customer customer : all_customers)
        {
            if (customer.getSalesId() == sales.getSalesId())
            {
                name = customer.getName();
                utility::convertToLowerCase(name); // convert customer name into lowercase

                if (name.find(target_name) != std::string::npos)
                {
                    list.push_back(sales);
                    break;
                }
            }
        }
    }

    return list;
}

// get all sales report
std::vector<Sales> SalesManager::fetchSalesReports(int year, int month, int day)
{
    Sales sale;

    bool status;

    std::string line, sales_type;
    std::vector<std::any> data;

    std::vector<Sales> sales = {};

    std::ifstream fin(project_setup::filenames["sales"]);

    std::getline(fin, line); // heading

    while (std::getline(fin, line))
    {
        data = utility::getLineData(line);

        status = sale.setByLineData(data);

        if (status)
        {
            if (year != 0 && month == 0 && day == 0)
            {
                if (sale.getDate()[0] == year)
                    sales.push_back(sale);
            }
            else if (year != 0 && month != 0 && day == 0)
            {
                if (sale.getDate()[0] == year && sale.getDate()[1] == month)
                    sales.push_back(sale);
            }
            else if (year != 0 && month != 0 && day != 0)
            {
                if (sale.getDate()[0] == year && sale.getDate()[1] == month && sale.getDate()[2] == day)
                sales.push_back(sale);
            }
            else if (year == 0 && month == 0 && day == 0)
            {
                sales.push_back(sale);
            }
        }
    }

    fin.close();

    return sales;
}
