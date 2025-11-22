#pragma once

// include header file
#include "sales_manager.h"
#include "product_manager.h"
#include "customer_manager.h"
#include "employee_manager.h"

namespace inventory_interface
{
    void sell(int);                                          // sell product
    void showInvoice(Sales, std::vector<Product>, Customer); // generate invoice
    bool saveInvoice(Sales, std::vector<Product>, Customer); // save invoice
}