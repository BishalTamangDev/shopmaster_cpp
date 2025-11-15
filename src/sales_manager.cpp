// include header file
#include "../include/sales_manager.h"
#include "../include/product_manager.h"
#include "../include/customer_manager.h"

// add new sales
bool SalesManager::add()
{
    return true;
}

// generate sales id
int SalesManager::generateId()
{
    int id = 1;

    return id;
}

// get sales by sales id
Sales SalesManager::getSalesById(int sales_id)
{
    Sales sales;

    std::cout << "Sales ID :: " << sales_id << "\n";

    return sales;
}

// get sales by customer name
std::vector<Sales> SalesManager::getSalesByCustomerName(std::string)
{
    return std::vector<Sales>();
}

// get daily sales report
std::vector<Sales> SalesManager::getDailySalesReport(int, int, int)
{
    return std::vector<Sales>();
}

// get monthly sales report
std::vector<Sales> SalesManager::getMonthlySalesReport(int, int)
{
    return std::vector<Sales>();
}

// get annually sales report
std::vector<Sales> SalesManager::getAnnuallySalesReport(int)
{
    return std::vector<Sales>();
}

// get all sales report
std::vector<Sales> SalesManager::getAllSales()
{
    Sales sale;
    std::vector<Sales> sales = {};

    std::string line;
    std::vector<std::any> data;

    std::ifstream fin(project_setup::filenames["sales"]);

    std::getline(fin, line); // heading

    while (std::getline(fin, line))
    {
        data = utility::getLineData(line);
        sale.setByLineData(data);
        sales.push_back(sale);
    }

    fin.close();

    return sales;
}
