// include header file
#include "../include/customer_manager.h"

// add customer
bool CustomerManager::add(Customer customer)
{
    // get headline
    std::ofstream file(project_setup::filenames["customer"], std::ios::app);

    file << customer.getSalesId() << "," << customer.getName() << "\n";

    bool status = file.good();

    file.close();

    return status;
}

// static :: get customer name
std::string CustomerManager::getCustomerName(int sales_id)
{
    std::string name = "Unknown";

    std::vector<Customer> customers = CustomerManager::fetchAllCustomers();

    for (Customer customer : customers)
    {
        if (customer.getSalesId() == sales_id)
        {
            name = customer.getName();
            break;
        }
    }

    return name;
}

// static :: fetch all customers
std::vector<Customer> CustomerManager::fetchAllCustomers()
{
    Customer customer;

    std::string line;
    std::vector<Customer> customers;

    std::ifstream fin(project_setup::filenames["customer"]);

    std::getline(fin, line);

    while (std::getline(fin, line))
    {
        bool status = customer.setByLineData(utility::getLineData(line));

        if (status)
            customers.push_back(customer);
    }

    fin.close();

    return customers;
}