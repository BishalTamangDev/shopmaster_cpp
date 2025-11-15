#pragma once

// include header file
#include "customer.h"

class CustomerManager
{
public:
    bool addCustomer(Customer);
    static std::vector<Customer> fetchAllCustomers(); // fetch all customers
};