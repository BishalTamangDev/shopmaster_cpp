// include header file
#include "../include/product.h"

// setters
// setter :: id
void Product::setId(int id)
{
    this->id = id;
}

// setter :: name
void Product::setName(std::string name)
{
    utility::convertToWordCase(name);
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

// setter :: sales id
void Product::setSalesId(int id)
{
    this->sales_id = id;
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

// setter :: status by string
void Product::setStatusByString(std::string str)
{
    utility::convertToLowerCase(str);

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
        this->added_date = utility::getDateFromString(std::any_cast<std::string>(data[4]));
        this->removed_date = utility::getDateFromString(std::any_cast<std::string>(data[5]));
        this->last_modified_date = utility::getDateFromString(std::any_cast<std::string>(data[6]));
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

// getter :: quantity
int Product::getQuantity() const
{
    return this->quantity;
}

// getter :: sales id
int Product::getSalesId() const
{
    return this->sales_id;
}

// getter :: rate
double Product::getRate() const
{
    return this->rate;
}

// getter :: name
std::string Product::getName() const
{
    return this->name;
}

// getter :: added date
std::array<int, 6> Product::getAddedDate() const
{
    return this->added_date;
}

// getter :: removed date
std::array<int, 6> Product::getRemovedDate() const
{
    return this->removed_date;
}

// getter :: last modified date
std::array<int, 6> Product::getLastModifiedDate() const
{
    return this->last_modified_date;
}

// getter :: status
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

// view product details
void Product::view()
{
    std::cout << "ID             :: " << this->getId();
    std::cout << "\nName           :: " << this->getName();
    std::cout << "\nRate           :: " << ShopManager::getCurrency() << utility::getFormattedDouble(this->getRate());
    std::cout << "\nQuantity       :: " << this->getQuantity();
    std::cout << "\nAdded On       :: " << utility::getDateString(this->getAddedDate(), false);
    std::cout << "\nRemoved On     :: " << utility::getDateString(this->getRemovedDate(), false);
    std::cout << "\nLast Modified  :: " << utility::getDateString(this->getLastModifiedDate(), false);
    std::cout << "\nStatus         :: " << this->getStatusString();
}