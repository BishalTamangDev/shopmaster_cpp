// include header file
#include "../include/sales.h"

// setters
// setter :: id
void Sales::setSalesId(int id)
{
    this->sales_id = id;
}

// setter :: employee id
void Sales::setEmployeeId(int employee_id)
{
    this->employee_id = employee_id;
}

// setter :: net amount
void Sales::setNetAmount(double net_amount)
{
    this->net_amount = net_amount;
}

// setter :: discount
void Sales::setDiscount(double discount)
{
    this->discount = discount;
}

// setter :: gross amount
void Sales::setGrossAmount(double gross_amount)
{
    this->gross_amount = gross_amount;
}

// setter :: tender
void Sales::setTender(double tender)
{
    this->tender = tender;
}

// setter :: change
void Sales::setChange(double change)
{
    this->change = change;
}

// setter :: date
void Sales::setDate(std::array<int, 3> date)
{
    this->date = date;
}

// setter :: time
void Sales::setTime(std::array<int, 3> time)
{
    this->time = time;
}

// setter :: using line data
bool Sales::setByLineData(std::vector<std::any> data)
{
    try
    {
        sales_id = std::stoi(std::any_cast<std::string>(data[0]));
        employee_id = std::stoi(std::any_cast<std::string>(data[1]));
        net_amount = std::stod(std::any_cast<std::string>(data[2]));
        discount = std::stod(std::any_cast<std::string>(data[3]));
        gross_amount = std::stod(std::any_cast<std::string>(data[4]));
        tender = std::stod(std::any_cast<std::string>(data[5]));
        change = std::stod(std::any_cast<std::string>(data[6]));
        date = utility::getDateFromString(std::any_cast<std::string>(data[7]));
        time = utility::getTimeFromString(std::any_cast<std::string>(data[8]));
        return true;
    }
    catch (const std::invalid_argument &e)
    {
        return false;
    }
}

// getters
// getter :: sales id
int Sales::getSalesId() const
{
    return this->sales_id;
}

// getter :: employee id
int Sales::getEmployeeId() const
{
    return this->employee_id;
}

// getter :: net amount
double Sales::getNetAmount() const
{
    return this->net_amount;
}

// getter :: discount
double Sales::getDiscount() const
{
    return this->discount;
}

// getter :: gross amount
double Sales::getGrossAmount() const
{
    return this->gross_amount;
}

// getter :: tender
double Sales::getTender() const
{
    return this->tender;
}

// getter :: change
double Sales::getChange() const
{
    return this->change;
}

// getter :: date
std::array<int, 3> Sales::getDate() const
{
    return this->date;
}

// getter :: time
std::array<int, 3> Sales::getTime() const
{
    return this->time;
}