#pragma once

// include header file
#include "sales.h"

class SalesManager
{
    bool add();              // add new sales
    int generateId();        // generate sales id
    Sales getSalesById(int); // get sales by sales id

    std::vector<Sales> getSalesByCustomerName(std::string); // get sales by customer name
    std::vector<Sales> getDailySalesReport(int, int, int);  // get daily sales report
    std::vector<Sales> getMonthlySalesReport(int, int);     // get monthly sales report
    std::vector<Sales> getAnnuallySalesReport(int);         // get annually sales report

    static std::vector<Sales> getAllSales(); // get all sales report
};