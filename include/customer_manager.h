#pragma once

// include header file
#include "customer.h"

class CustomerManager
{
public:
    bool addCustomer(Customer);                       // add customer
    static std::string getCustomerName(int);          // get customer name
    static std::vector<Customer> fetchAllCustomers(); // fetch all customers
};