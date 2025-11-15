#pragma once

// include header file
#include "project_setup.h"

class Customer
{
private:
    int sales_id;
    std::string name;

public:
    // constructor
    Customer()
    {
        this->sales_id = 0;
        this->name = "";
    }

    // parameterized constructor
    Customer(int sales_id, std::string name)
    {
        this->sales_id = sales_id;
        this->name = name;
    }

    // setters
    void setSalesId(int id);
    void setName(std::string name);
    bool setByLineData(std::vector<std::any>);

    // getters
    int getSalesId() const;
    std::string getName() const;
};