#pragma once

// include header file
#include "sales.h"

class SalesManager
{
public:
    bool add(); // add new sales

    static int generateId();                                                // generate sales id
    static bool fetchSalesReportById(int, Sales &);                         // fetch sales by sales id
    static std::vector<Sales> fetchSalesReportsByCustomerName(std::string); // fetch sales by customer name
    static std::vector<Sales> fetchSalesReports(int, int, int);             // fetch sales report
};