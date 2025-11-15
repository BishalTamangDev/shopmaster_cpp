// include header file
#include "../include/customer.h"

// setter :: sales id
void Customer::setSalesId(int sales_id)
{
    this->sales_id = sales_id;
}

// setter :: sales name
void Customer::setName(std::string name)
{
    utility::convertToWordCase(name);
    this->name = name;
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

// getter :: sales id
int Customer::getSalesId() const
{
    return this->sales_id;
}

// getter :: name
std::string Customer::getName() const
{
    return this->name;
}