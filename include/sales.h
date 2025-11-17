#pragma once

// include header file
#include "project_setup.h"

class Sales
{
private:
    int sales_id, employee_id;
    double net_amount, discount, gross_amount, tender, change;
    std::array<int, 6> date;

public:
    // constructor
    Sales()
    {
        sales_id = 0;
        employee_id = 0;
        net_amount = 0.0;
        discount = 0.0;
        gross_amount = 0.0;
        tender = 0.0;
        change = 0.0;
        date = {0, 0, 0, 0, 0, 0};
    }

    // setters
    void setSalesId(int);
    void setEmployeeId(int);
    void setNetAmount(double);
    void setDiscount(double);
    void setGrossAmount(double);
    void setTender(double);
    void setChange(double);
    void setDate(std::array<int, 6>);
    bool setByLineData(std::vector<std::any>);

    // getters
    int getSalesId() const;
    int getEmployeeId() const;
    double getNetAmount() const;
    double getDiscount() const;
    double getGrossAmount() const;
    double getTender() const;
    double getChange() const;
    std::array<int, 6> getDate() const;
};