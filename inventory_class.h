#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <any>

// import user-defined files :: header
#include "utils.h"
#include "file_setup.h"

#ifndef SHOPMASTER_INVENTORY_H
#define SHOPMASTER_INVENTORY_H

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
    double rate;
    std::string name;
    std::array<int, 6> added_date;
    std::array<int, 6> removed_date;
    std::array<int, 6> last_modified_date;
    PRODUCT_STATUS status;

public:
    // constructor
    Product()
    {
        id = 0;
        quantity = 0;
        rate = 0.0;
        name = "";
        added_date = {0, 0, 0, 0, 0, 0};
        removed_date = {0, 0, 0, 0, 0, 0};
        last_modified_date = {0, 0, 0, 0, 0, 0};
        status = PRODUCT_STATUS::UNKNOWN;
    }

    // setters
    void setId(int);
    void setName(std::string);
    void setRate(double);
    void setQuantity(int);
    void setAddedDate(std::array<int, 6>);
    void setRemovedDate(std::array<int, 6>);
    void setLastModifiedDate(std::array<int, 6>);
    void setStatus(PRODUCT_STATUS);

    // setters :: extra
    void setStatusByString(std::string);
    bool setByLineData(std::vector<std::any>);

    // getters
    int getId() const;
    int getQuantity() const;
    double getRate() const;
    std::string getName() const;
    std::array<int, 6> getAddedDate() const;
    std::array<int, 6> getRemovedDate() const;
    std::array<int, 6> getLastModifiedDate() const;
    PRODUCT_STATUS getStatus() const;
    std::string getStatusString() const;

    bool add();    // add product
    bool fetch();  // fetch product
    void view();   // view product details
    bool update(); // update product details
    bool remove(); // remove product

    // static members
    static std::vector<Product> LIST;
    static void fetchAll(); // fetch all products
};

// static :: product list
std::vector<Product> Product::LIST = {};

// setters
// setter :: id
void Product::setId(int id)
{
    this->id = id;
}

// setter :: name
void Product::setName(std::string name)
{
    utils::convertToWordCase(name);
    this->name = name;
}

// setter :: rate
void Product::setRate(double rate)
{
    this->rate = rate;
}

// setter :: quantity
void Product::setQuantity(int quantity)
{
    this->quantity = quantity;
}

// setter :: added date
void Product::setAddedDate(std::array<int, 6> added_date)
{
    this->added_date = added_date;
}

// setter :: removed date
void Product::setRemovedDate(std::array<int, 6> removed_date)
{
    this->removed_date = removed_date;
}

// setter :: last modified
void Product::setLastModifiedDate(std::array<int, 6> last_modified_date)
{
    this->last_modified_date = last_modified_date;
}

// setter :: status
void Product::setStatus(PRODUCT_STATUS status)
{
    this->status = status;
}

// setters :: extra
// setter :: status by string
void Product::setStatusByString(std::string str)
{
    utils::convertToLowerCase(str);

    if (str == "available")
        this->status = PRODUCT_STATUS::AVAILABLE;
    else if (str == "out of stock")
        this->status = PRODUCT_STATUS::OUT_OF_STOCK;
    else if (str == "removed")
        this->status = PRODUCT_STATUS::REMOVED;
    else
        this->status = PRODUCT_STATUS::UNKNOWN;
}

// setter :: set by line date
bool Product::setByLineData(std::vector<std::any> data)
{
    try
    {
        this->id = std::stoi(std::any_cast<std::string>(data[0]));
        this->name = std::any_cast<std::string>(data[1]);
        this->rate = std::stod(std::any_cast<std::string>(data[2]));
        this->quantity = std::stoi(std::any_cast<std::string>(data[3]));
        this->added_date = utils::getDateFromString(std::any_cast<std::string>(data[4]));
        this->removed_date = utils::getDateFromString(std::any_cast<std::string>(data[5]));
        this->last_modified_date = utils::getDateFromString(std::any_cast<std::string>(data[6]));
        this->setStatusByString(std::any_cast<std::string>(data[7]));
        return true;
    }
    catch (const std::invalid_argument &e)
    {
        return false;
    }
}

// getters
// getter :: id
int Product::getId() const
{
    return this->id;
}

// getter ::
int Product::getQuantity() const
{
    return this->quantity;
}

// getter ::
double Product::getRate() const
{
    return this->rate;
}

// getter ::
std::string Product::getName() const
{
    return this->name;
}

// getter ::
std::array<int, 6> Product::getAddedDate() const
{
    return this->added_date;
}

// getter ::
std::array<int, 6> Product::getRemovedDate() const
{
    return this->removed_date;
}

// getter ::
std::array<int, 6> Product::getLastModifiedDate() const
{
    return this->last_modified_date;
}

// getter ::
PRODUCT_STATUS Product::getStatus() const
{
    return this->status;
}

// getter :: status string
std::string Product::getStatusString() const
{
    if (this->status == PRODUCT_STATUS::AVAILABLE)
        return "Available";
    else if (this->status == PRODUCT_STATUS::OUT_OF_STOCK)
        return "Out of Stock";
    else if (this->status == PRODUCT_STATUS::REMOVED)
        return "Removed";
    else
        return "Unknown";
}

// static fucntions
// add product
bool Product::add()
{
    std::fstream file;
    std::string line, headline;

    Product temp_product;

    // open file and get headline
    file.open(app_files::filenames["product"], std::ios::in); // open file in append mode
    std::getline(file, headline);                             // get headline
    file.close();

    // add process
    file.open(app_files::filenames["product"], std::ios::app); // open file in append mode

    file
        << this->id << ","
        << this->name << ","
        << this->rate << ","
        << this->quantity << ","
        << utils::getDateString(this->added_date, true) << ","
        << utils::getDateString(this->removed_date, true) << ","
        << utils::getDateString(this->last_modified_date, true) << ","
        << this->getStatusString() << "\n";

    bool status = file.good();

    file.close();

    std::thread fetch_product_thread(Product::fetchAll);
    fetch_product_thread.detach();

    return status;
}

// fetch product
bool Product::fetch()
{
    bool found = false;

    for (Product temp : Product::LIST)
    {
        if (temp.getId() == this->getId())
        {
            found = true;
            *this = temp;
            break;
        }
    }

    return found;
}

// view product detail
void Product::view()
{
    std::cout << "ID             :: " << this->getId();
    std::cout << "\nName           :: " << this->getName();
    std::cout << "\nRate           :: " << this->getRate();
    std::cout << "\nQuantity       :: " << this->getQuantity();
    std::cout << "\nAdded On       :: " << utils::getDateString(this->getAddedDate(), false);
    std::cout << "\nRemoved On     :: " << utils::getDateString(this->getRemovedDate(), false);
    std::cout << "\nLast Modified  :: " << utils::getDateString(this->getLastModifiedDate(), false);
    std::cout << "\nStatus         :: " << this->getStatusString();
}

// update product details
bool Product::update()
{
    std::fstream file;
    std::string heading;

    // open file and get headline
    file.open(app_files::filenames["product"], std::ios::in);
    std::getline(file, heading);
    file.close();

    // open file and update line
    file.open("new_products.csv", std::ios::out);
    file << heading << "\n"; // write heading

    for (Product temp : Product::LIST)
    {
        if (temp.getId() == this->getId())
        {
            temp.setName(this->getName());
            temp.setRate(this->getRate());
            temp.setLastModifiedDate(this->getLastModifiedDate());
        }

        file
            << temp.getId() << ","
            << temp.getName() << ","
            << temp.getRate() << ","
            << temp.getQuantity() << ","
            << utils::getDateString(temp.getAddedDate(), true) << ","
            << utils::getDateString(temp.getRemovedDate(), true) << ","
            << utils::getDateString(temp.getLastModifiedDate(), true) << ","
            << temp.getStatusString() << "\n";
    }

    // background process :: fetch products
    std::thread fetch_products_thread(Product::fetchAll);
    fetch_products_thread.detach();

    file.close();

    return app_files::updateFile(app_files::filenames["product"], "new_products.csv");
}

// remove product
bool Product::remove()
{
    std::fstream file;
    std::string heading;

    // open file and get headline
    file.open(app_files::filenames["product"], std::ios::in);
    std::getline(file, heading);
    file.close();

    // open file and update line
    file.open("new_products.csv", std::ios::out);
    file << heading << "\n"; // write heading

    for (Product temp : Product::LIST)
    {
        if (temp.getId() == this->getId())
        {
            temp.setRemovedDate(utils::getCurrentDateTime());
            temp.setStatus(PRODUCT_STATUS::REMOVED);
        }

        file
            << temp.getId() << ","
            << temp.getName() << ","
            << temp.getRate() << ","
            << temp.getQuantity() << ","
            << utils::getDateString(temp.getAddedDate(), true) << ","
            << utils::getDateString(temp.getRemovedDate(), true) << ","
            << utils::getDateString(temp.getLastModifiedDate(), true) << ","
            << temp.getStatusString() << "\n";
    }

    file.close();

    // background process :: fetch products
    std::thread fetch_products_thread(Product::fetchAll);
    fetch_products_thread.detach();

    return app_files::updateFile(app_files::filenames["product"], "new_products.csv");
}

// static member :: fetch all products
void Product::fetchAll()
{
    Product product;
    std::string line;
    std::vector<Product> products = {};
    std::vector<std::any> line_data;

    std::ifstream fin(app_files::filenames["product"]);

    std::getline(fin, line); // headline

    while (std::getline(fin, line))
    {
        line_data = utils::getLineData(line);
        product.setByLineData(line_data);
        products.push_back(product);
    }

    Product::LIST = products;

    fin.close();
}

#endif