// include header file
#include "../include/customer_manager.h"

// add customer
bool CustomerManager::add(Customer customer)
{
    // get headline
    std::ofstream fout(project_setup::filenames["customer"], std::ios::app);

    if (!fout)
    {
        return false;
    }

    fout << customer.getSalesId() << "," << customer.getName() << "\n";

    bool status = fout.good();

    return status;
}

// fetch customer by sales id
bool CustomerManager::fetchCustomerBySalesId(int sales_id, Customer &customer)
{
    std::ifstream fin(project_setup::filenames["customer"]);

    if (!fin)
    {
        return false;
    }

    bool status = false;

    std::string line;

    std::getline(fin, line); // skip heading

    while (std::getline(fin, line))
    {
        Customer temp_customer;

        if (temp_customer.setByLineData(utility::getLineData(line)))
        {
            if(temp_customer.getSalesId() == sales_id)
            {
                customer = temp_customer;
                status = true;
                break;
            }
        }
    }

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
    std::ifstream fin(project_setup::filenames["customer"]);

    if (!fin)
    {
        return {};
    }

    std::string line;
    std::vector<Customer> customers;

    std::getline(fin, line); // skip heading

    while (std::getline(fin, line))
    {
        Customer customer;

        if (customer.setByLineData(utility::getLineData(line)))
        {
            customers.push_back(customer);
        }
    }

    return customers;
}