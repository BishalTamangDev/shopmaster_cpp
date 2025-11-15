#pragma once

// include header file
#include "sales_manager.h"

namespace sales_interface
{
    void menu();                   // menu
    void searchSalesReportById();  // search sales report by id
    void viewDailySalesReport();   // view daily sales report
    void viewMonthlySalesReport(); // view month sales report
    void viewAnnualSalesReport();  // view annual sales report
};