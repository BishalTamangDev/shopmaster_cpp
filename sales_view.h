#include <iostream>

// import user-defined header files
#include "utils.h"

#ifndef SHOPMASTER_SALES_VIEW_H
#define SHOPMASTER_SALES_VIEW_H

// namespace sales_view
namespace sales_view
{
    void viewTodaysSalesReport(); // view today's sales report
}

// view today's sales report
void sales_view::viewTodaysSalesReport()
{
    utils::header("TODAY'S SALES REPORT");
    utils::pauseScreen();
}

#endif