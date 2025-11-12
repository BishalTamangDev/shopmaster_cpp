#include <iostream>
#include <string>
#include <vector>
#include <any>
#include <fstream>
#include <filesystem>

// import user-defined header files
#include "utils.h"
#include "file_setup.h"

#ifndef SHOPMASTER_CUSTOMER_H
#define SHOPMASTER_CUSTOMER_H

class Customer
{
private:
    int sales_id;
    std::string name;

public:
    Customer()
    {
        this->sales_id = 0;
        this->name = "";
    }

    // setters
    void setSalesId(int id);
    void setName(std::string name);

    // getters
    int getSalesId() const;
    std::string getName();

    bool add();
    bool setByLineData(std::vector<std::any>);

    // static functions
    static std::vector<Customer> fetchAllCustomers(); // fetch all customers
};

// setters
// setter :: sales id
void Customer::setSalesId(int sales_id)
{
    this->sales_id = sales_id;
}

// setter :: sales name
void Customer::setName(std::string name)
{
    utils::convertToWordCase(name);
    this->name = name;
}

// getters
// getter :: sales id
int Customer::getSalesId() const
{
    return this->sales_id;
}

// getter :: name
std::string Customer::getName()
{
    utils::convertToWordCase(this->name);
    return this->name;
}

// add customer
bool Customer::add()
{
    // get headline
    std::ofstream file(app_files::filenames["customer"], std::ios::app);

    file << this->getSalesId() << "," << this->getName() << "\n";

    bool status = file.good();

    file.close();

    return status;
}

// set customer by line data
bool Customer::setByLineData(std::vector<std::any> data)
{
    try
    {
        this->setSalesId(std::stoi(std::any_cast<std::string>(data[0])));
        this->setName(std::any_cast<std::string>((data[1])));
        return true;
    }
    catch (std::invalid_argument &e)
    {
        return false;
    }
}

// static members :: fetch all customers
std::vector<Customer> Customer::fetchAllCustomers()
{
    std::string line;
    Customer customer;
    std::vector<Customer> customers;

    std::ifstream fin(app_files::filenames["customer"]);

    std::getline(fin, line);

    while (std::getline(fin, line))
    {
        customer.setByLineData(utils::getLineData(line));
        customers.push_back(customer);
    }

    fin.close();

    return customers;
}

#endif