#pragma once

// include header file
#include "sales_manager.h"
#include "customer_manager.h"
#include "employee_manager.h"
#include "product_manager.h"

namespace sales_interface
{
    void menu();                                             // menu
    void searchInvoice();                                    // search sales report by id
    void searchSalesReportByCustomerName();                  // search sales report by customer name
    void viewAllSalesReports();                              // view all sales reports
    void viewTodaysSalesReport();                            // view today's sales reports
    void searchDailySalesReport();                           // view daily sales reports
    void searchMonthlySalesReport();                         // view month sales reports
    void searchAnnualSalesReport();                          // view annual sales reports
    void viewFormattedSalesReport(std::vector<Sales>);       // view formatted sales report
    void showInvoice(Sales, std::vector<Product>, Customer); // generate invoice
    bool saveInvoice(Sales, std::vector<Product>, Customer); // save invoice
};
