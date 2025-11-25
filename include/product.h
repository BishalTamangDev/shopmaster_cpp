#pragma once

// include header file
#include "project_setup.h"
#include "shop_manager.h"

// product status
enum class PRODUCT_STATUS
{
    AVAILABLE,
    OUT_OF_STOCK,
    REMOVED,
    UNKNOWN,
};

// class :: product
class Product
{
private:
    int id;
    int quantity;
    int sales_id;
    double rate;
    std::string name;
    std::array<int, 3> added_date;
    std::array<int, 3> removed_date;
    std::array<int, 3> last_modified_date;
    PRODUCT_STATUS status;

public:
    // constructor
    Product()
    {
        id = 0;
        quantity = 0;
        sales_id = 0;
        rate = 0.0;
        name = "";
        added_date = {0, 0, 0};
        removed_date = {0, 0, 0};
        last_modified_date = {0, 0, 0};
        status = PRODUCT_STATUS::UNKNOWN;
    }

    // pameterized constructor
    Product(int id, std::string name, double rate, int quantity, std::array<int, 3> added_date, std::array<int, 3> removed_date, std::array<int, 3> last_modified_date, PRODUCT_STATUS status)
    {
        this->id = id;
        this->name = name;
        this->rate = rate;
        this->quantity = quantity;
        this->added_date = added_date;
        this->removed_date = removed_date;
        this->last_modified_date = last_modified_date;
        this->status = status;
    }

    // setters
    void setId(int);
    void setName(std::string);
    void setRate(double);
    void setQuantity(int);
    void setSalesId(int);
    void setAddedDate(std::array<int, 3>);
    void setRemovedDate(std::array<int, 3>);
    void setLastModifiedDate(std::array<int, 3>);
    void setStatus(PRODUCT_STATUS);
    void setStatusByString(std::string);
    bool setByLineData(std::vector<std::any>);

    // getters
    int getId() const;
    int getQuantity() const;
    int getSalesId() const;
    double getRate() const;
    std::string getName() const;
    std::array<int, 3> getAddedDate() const;
    std::array<int, 3> getRemovedDate() const;
    std::array<int, 3> getLastModifiedDate() const;
    PRODUCT_STATUS getStatus() const;
    std::string getStatusString() const;

    void view(); // view product details
};