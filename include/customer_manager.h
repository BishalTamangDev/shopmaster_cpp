#pragma once

// include header file
#include "customer.h"

class CustomerManager
{
public:
    bool add(Customer);                               // add customer
    bool fetchCustomerBySalesId(int, Customer &);     // fetch customer by sales id
    static std::string getCustomerName(int);          // get customer name
    static std::vector<Customer> fetchAllCustomers(); // fetch all customers
};