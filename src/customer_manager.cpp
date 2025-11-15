// include header file
#include "../include/customer_manager.h"

// add customer
bool CustomerManager::addCustomer(Customer customer)
{
    // get headline
    std::ofstream file(project_setup::filenames["customer"], std::ios::app);

    file << customer.getSalesId() << "," << customer.getName() << "\n";

    bool status = file.good();

    file.close();

    return status;
}

// fetch all customers
std::vector<Customer> CustomerManager::fetchAllCustomers()
{
    Customer customer;
    
    std::string line;
    std::vector<Customer> customers;

    std::ifstream fin(project_setup::filenames["customer"]);

    std::getline(fin, line);

    while (std::getline(fin, line))
    {
        customer.setByLineData(utility::getLineData(line));
        customers.push_back(customer);
    }

    fin.close();

    return customers;
}