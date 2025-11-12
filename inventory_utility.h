// import header files
#include <iostream>
#include <vector>

// import user-defined files :: header
#include "inventory_class.h"
#include "utils.h"

#ifndef SHOPMASTER_INVENTORY_UTILITY_H
#define SHOPMASTER_INVENTORY_UTILITY_H

// utility
namespace inventory_utility
{
    bool restock(int, int);                         // restock
    bool searchById(int, Product &);                // search by id
    bool validProductName(std::string);             // check if the product name is already taken
    int getValidId();                               // get valid id
    std::vector<Product> searchByName(std::string); // search by name
    std::vector<Product> fetchAvailableProducts();  // fetch available product
    std::vector<Product> fetchOutOfStockProducts(); // fetch out of stock product
}

// restock
bool inventory_utility::restock(int id, int qty)
{
    if (id <= 0)
        return false;

    bool status = false;

    std::string headline;
    std::string temporary_file = "products_temp.csv";
    std::fstream file;

    // get headline
    file.open(app_files::filenames["product"], std::ios::in);
    std::getline(file, headline);
    file.close();

    file.open(temporary_file, std::ios::out);
    file << headline << "\n";
    
    for (Product &product : Product::fetchAllProducts())
    {
        if (product.getId() == id)
        {
            product.setQuantity(product.getQuantity() + qty); // update quantity
            if (product.getStatus() == PRODUCT_STATUS::OUT_OF_STOCK)
                product.setStatus(PRODUCT_STATUS::AVAILABLE); // update product status
            status = true;
        }
        file
            << product.getId() << ","
            << product.getName() << ","
            << product.getRate() << ","
            << product.getQuantity() << ","
            << utils::getDateString(product.getAddedDate(), true) << ","
            << utils::getDateString(product.getRemovedDate(), true) << ","
            << utils::getDateString(product.getLastModifiedDate(), true) << ","
            << product.getStatusString() << "\n";
    }
    file.close();

    if (status)
        status = app_files::updateFile(app_files::filenames["product"], temporary_file);

    return status;
}

// search by id
bool inventory_utility::searchById(int target_id, Product &product)
{
    bool found = false;

    for (Product temp : Product::fetchAllProducts())
    {
        if (temp.getId() == target_id)
        {
            product = temp;
            found = true;
            break;
        }
    }

    return found;
}

// check if the product name is already taken
bool inventory_utility::validProductName(std::string str)
{
    std::vector<Product> products = Product::fetchAllProducts(); // fetch all products

    if (products.empty())
        return true;

    for (Product product : products)
        if (product.getName() == str)
            return false;

    return true;
}

// get valid id :: get greatest id + 1
int inventory_utility::getValidId()
{
    int id = 1;

    std::vector<Product> products = Product::fetchAllProducts(); // fetch all products

    if (!products.empty())
    {
        for (Product product : products)
            if (product.getId() > id)
                id = product.getId();
        id++;
    }

    return id;
}

// search by name
std::vector<Product> inventory_utility::searchByName(std::string target_name)
{
    std::string name;
    
    std::vector<Product> products = Product::fetchAllProducts(); // fetch all products

    utils::convertToLowerCase(target_name); // convert target name into lowercase

    for (Product temp : products)
    {
        name = temp.getName();
        utils::convertToLowerCase(name); // convert name into lowercase

        if (name.find(target_name) != std::string::npos)
            products.push_back(temp);
    }

    return products;
}

// fetch available product
std::vector<Product> inventory_utility::fetchAvailableProducts()
{
    std::vector<Product> available_products = {};

    for (Product product : Product::fetchAllProducts())
        if (product.getStatus() == PRODUCT_STATUS::AVAILABLE)
            available_products.push_back(product);

    return available_products;
}

// fetch out of stock products
std::vector<Product> inventory_utility::fetchOutOfStockProducts()
{
    std::vector<Product> out_of_stock_products = {};

    for (Product product : Product::fetchAllProducts())
        if (product.getStatus() == PRODUCT_STATUS::OUT_OF_STOCK || product.getQuantity() == 0)
            out_of_stock_products.push_back(product);

    return out_of_stock_products;
}

#endif
