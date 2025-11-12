#include <iostream>
#include <chrono>
#include <thread>

// import user-defined header files
#include "inventory_utility.h"

#ifndef SHOPMASTER_INVENTORY_VIEW_H
#define SHOPMASTER_INVENTORY_VIEW_H

namespace inventory_view
{
    void adminMenu();              // menu
    void addNewProduct();          // add new product
    void viewProductMenu();        // view product menu
    void viewProducts();           // view all product
    void viewAvailableProducts();  // view available products
    void viewOutOfStockProducts(); // view out of stock products
    void searchProductMenu();      // search product menu
    void searchById();             // search product by id
    void searchByName();           // search product by name
    void updateProductDetails();   // update product details
    void restock();                // restock product
    void remove();                 // remove product

    void sell(); // sell
}

// view products
void inventory_view::viewProducts()
{
    utils::header("ALL PRODUCTS");

    const std::vector<int> spaces = {6, 25, 12, 7, 12, 12, 15, 13};

    utils::showLine(spaces, {"ID", "Name", "Rate", "Qty", "Added On", "Removed On", "Last Modified", "Status"});

    if (Product::LIST.empty())
        utils::showMessage(MESSAGE_TYPE::INFO, "\nNo product has been been added yet!\n");
    else
        for (Product product : Product::LIST)
            utils::showLine(spaces, {std::to_string(product.getId()), product.getName(), std::to_string(product.getRate()), std::to_string(product.getQuantity()), utils::getDateString(product.getAddedDate(), false), utils::getDateString(product.getRemovedDate(), false), utils::getDateString(product.getLastModifiedDate(), false), product.getStatusString()});

    std::cout << "\nPress any key to continue...";

    utils::pauseScreen();
}

// inventory view :: menu
void inventory_view::adminMenu()
{
    std::string choice;

    const std::map<int, std::string> options = {
        {1, "View Products"},
        {2, "Search Product"},
        {3, "Add New Product"},
        {4, "Update Product Details"},
        {5, "Restock Product"},
        {6, "Remove Product"},
        {7, "Go Back"},
    };

    while (true)
    {
        utils::header("INVENTORY MENU");

        for (const auto &option : options)
            utils::showOption(option.first, option.second);

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
            inventory_view::viewProductMenu();
        else if (choice == "2")
            inventory_view::searchProductMenu();
        else if (choice == "3")
            inventory_view::addNewProduct();
        else if (choice == "4")
            inventory_view::updateProductDetails();
        else if (choice == "5")
            inventory_view::restock();
        else if (choice == "6")
            inventory_view::remove();
        else if (choice == "7")
            return;
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            utils::pauseScreen();
        }
    }

    utils::pauseScreen();
}

// inventory view :: view product menu
void inventory_view::addNewProduct()
{
    Product product;

    int qty;
    double rate;
    bool valid_name, valid_rate, valid_qty, product_added;
    std::string name, rate_str, qty_str, choice;

    while (true)
    {
        valid_rate = false;
        valid_qty = false;

        utils::header("ADD NEW PRODUCT");

        // name
        std::cout << "Name        :: ";
        std::getline(std::cin, name);

        valid_name = inventory_utility::validProductName(name);

        if (!valid_name)
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nThis product is already added!");
        else
        {
            product.setName(name);

            // set rate
            while (!valid_rate)
            {
                std::cout << "\nRate        :: ";
                std::getline(std::cin, rate_str);

                try
                {
                    rate = std::stof(rate_str);

                    if (rate > 0)
                    {
                        valid_rate = true;
                        product.setRate(rate);
                    }
                    else
                        utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid rate!\n");
                }
                catch (const std::invalid_argument &e)
                {
                    utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid input!\n");
                }
            }

            // set qty
            while (!valid_qty)
            {
                std::cout << "\nQuantity    :: ";
                std::getline(std::cin, qty_str);

                try
                {
                    qty = std::stof(qty_str);

                    if (qty > 0)
                    {
                        valid_qty = true;
                        product.setQuantity(qty);
                    }
                    else
                        utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid quantity!\n");
                }
                catch (const std::invalid_argument &e)
                {
                    utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid input!\n");
                }
            }

            product.setAddedDate(utils::getCurrentDateTime());
            product.setStatus(PRODUCT_STATUS::AVAILABLE);

            int id = inventory_utility::getValidId();

            product.setId(id);

            // preview product details
            utils::header("ADD NEW PRODUCT :: PRODUCT DETAILS");
            product.view();

            std::cout << "\n\nAre you sure you want to add this product [y/n]? ";
            std::getline(std::cin, choice);

            if (choice != "y" && choice != "Y")
                utils::showMessage(MESSAGE_TYPE::INFO, "\nProduct addition cancelled!");
            else
            {
                product_added = product.add();

                if (!product_added)
                    utils::showMessage(MESSAGE_TYPE::FAILURE, "\nProduct addition failed!");
                else
                {
                    utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nProduct added successfully!");
                    std::thread fetch_product_thread(Product::fetchAll);
                    fetch_product_thread.detach();
                }
            }
        }

        std::cout << "\n\nDo you want to add another product [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "Y")
            break;
    }
}

// view available products
void inventory_view::viewAvailableProducts()
{
    utils::header("VIEW AVAILABLE PRODUCTS");

    const std::vector<int> spaces = {6, 25, 12, 7, 12, 12, 15, 13};

    std::vector<Product> available_products = inventory_utility::fetchAvailableProducts();

    utils::showLine(spaces, {"ID", "Name", "Rate", "Qty", "Added On", "Removed On", "Last Modified", "Status"});

    if (available_products.empty())
        utils::showMessage(MESSAGE_TYPE::INFO, "\nNo product available!\n");
    else
        for (Product product : available_products)
            utils::showLine(spaces, {std::to_string(product.getId()), product.getName(), std::to_string(product.getRate()), std::to_string(product.getQuantity()), utils::getDateString(product.getAddedDate(), false), utils::getDateString(product.getRemovedDate(), false), utils::getDateString(product.getLastModifiedDate(), false), product.getStatusString()});

    std::cout << "\nPress any key to continue...";

    utils::pauseScreen();
}

// search product by id
void inventory_view::viewOutOfStockProducts()
{
    utils::header("VIEW OUT OF STOCK PRODUCTS");

    const std::vector<int> spaces = {6, 25, 12, 7, 12, 12, 15, 13};

    std::vector<Product> out_of_stock_products = inventory_utility::fetchOutOfStockProducts();

    utils::showLine(spaces, {"ID", "Name", "Rate", "Qty", "Added On", "Removed On", "Last Modified", "Status"});

    if (out_of_stock_products.empty())
        utils::showMessage(MESSAGE_TYPE::INFO, "\nNo product out of stock!\n");
    else
        for (Product product : out_of_stock_products)
            utils::showLine(spaces, {std::to_string(product.getId()), product.getName(), std::to_string(product.getRate()), std::to_string(product.getQuantity()), utils::getDateString(product.getAddedDate(), false), utils::getDateString(product.getRemovedDate(), false), utils::getDateString(product.getLastModifiedDate(), false), product.getStatusString()});

    std::cout << "\nPress any key to continue...";

    utils::pauseScreen();
}

// search product menu
void inventory_view::searchProductMenu()
{
    std::string choice;

    const std::map<int, std::string> options = {
        {1, "Search Product by ID"},
        {2, "Search Product by Name"},
        {3, "Go Back"},
    };

    while (true)
    {
        utils::header("SEARCH PRODUCT MENU");

        for (const auto &option : options)
            utils::showOption(option.first, option.second);

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
            inventory_view::searchById();
        else if (choice == "2")
            inventory_view::searchByName();
        else if (choice == "3")
            return;
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            utils::pauseScreen();
        }
    }
}

// search product by id
void inventory_view::searchById()
{
    int id;
    bool product_found;
    std::string id_str, choice;

    Product product;

    while (true)
    {
        product_found = false;

        utils::header("SEARCH BY PRODUCT BY ID");

        std::cout << "Enter product ID to search :: ";
        std::getline(std::cin, id_str);

        try
        {
            id = std::stoi(id_str);

            product_found = inventory_utility::searchById(id, product);

            if (product_found)
            {
                std::cout << "\n";
                product.view();
            }
            else
                utils::showMessage(MESSAGE_TYPE::INFO, "\nNo product found with this ID!");
        }
        catch (const std::invalid_argument &e)
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid input!");
        }

        std::cout << "\n\nDo you want to search another product [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "y")
            break;
    }
}

// search product by name
void inventory_view::searchByName()
{
    bool found;
    std::string name, target_name, choice;
    const std::vector<int> spaces = {6, 25, 12, 7, 12, 12, 15, 13};

    while (true)
    {
        found = false;
        utils::header("SEARCH BY PRODUCT BY NAMES");

        std::cout << "Enter product name to search :: ";
        std::getline(std::cin, target_name);

        utils::convertToLowerCase(target_name);
        std::cout << "\n";
        utils::showLine(spaces, {"ID", "Name", "Rate", "Qty", "Added On", "Removed On", "Last Modified", "Status"});

        for (Product product : Product::LIST)
        {
            name = product.getName();
            utils::convertToLowerCase(name);

            if (name.find(target_name) != std::string::npos)
            {
                found = true;
                utils::showLine(spaces, {std::to_string(product.getId()), product.getName(), std::to_string(product.getRate()), std::to_string(product.getQuantity()), utils::getDateString(product.getAddedDate(), false), utils::getDateString(product.getRemovedDate(), false), utils::getDateString(product.getLastModifiedDate(), false), product.getStatusString()});
            }
        }

        if (!found)
            utils::showMessage(MESSAGE_TYPE::INFO, "\nNo product found with this name!\n");

        std::cout << "\nDo you want to search another product [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "y")
            break;
    }
}

// inventory view :: view product menu
void inventory_view::viewProductMenu()
{
    std::string choice;

    const std::map<int, std::string> options = {
        {1, "View All Product"},
        {2, "View Available Products"},
        {3, "View Out of Stock Products"},
        {4, "Go Back"},
    };

    while (true)
    {
        utils::header("VIEW PRODUCT MENU");

        for (const auto &option : options)
            utils::showOption(option.first, option.second);

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
            inventory_view::viewProducts();
        else if (choice == "2")
            inventory_view::viewAvailableProducts();
        else if (choice == "3")
            inventory_view::viewOutOfStockProducts();
        else if (choice == "4")
            return;
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            utils::pauseScreen();
        }
    }
}

// inventory view :: update details
void inventory_view::updateProductDetails()
{
    utils::header("UPDATE PRODUCT DETAILS");
    utils::pauseScreen();
}

// inventory view :: add to stock
void inventory_view::restock()
{
    int id, qty;
    bool valid_id, valid_qty;
    std::string id_str, qty_str, choice;
    Product product;

    while (true)
    {
        utils::header("RESTOCK");

        // get product id
        std::cout << "Enter product ID to  :: ";
        std::getline(std::cin, id_str);

        try
        {
            id = std::stoi(id_str);
            product.setId(id);
            valid_id = true;
        }
        catch (const std::invalid_argument &e)
        {
            valid_id = false;
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid input!");
        }

        if (valid_id)
        {
            if (!product.fetch())
                utils::showMessage(MESSAGE_TYPE::INFO, "\nProduct not found!");
            else
            {
                // preview product details
                std::cout << "\n";
                product.view();
                std::cout << "\n";

                // check if the product is removed
                if (product.getStatus() == PRODUCT_STATUS::REMOVED)
                    utils::showMessage(MESSAGE_TYPE::INFO, "\nThis product is already removed!");
                else
                {
                    // proceed
                    std::cout << "\nEnter the quantity to add :: ";
                    std::getline(std::cin, qty_str);

                    try
                    {
                        qty = std::stoi(qty_str);

                        if (qty == 0)
                            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid quantity!");
                        else
                            valid_qty = true;
                    }
                    catch (const std::invalid_argument &e)
                    {
                        valid_qty = false;
                        utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid input!");
                    }

                    if (valid_qty)
                    {
                        bool response = inventory_utility::restock(id, qty);

                        if (response)
                            utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nStock updated successfully!");
                        else
                            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nCouldn't update stock!");
                    }
                }
            }
        }

        std::cout << "\n\nDo you want to restock another product [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "y")
            break;
    }
}

// inventory view :: remove
void inventory_view::remove()
{
    int id;
    Product product;
    std::string id_str, choice;

    while (true)
    {
        utils::header("REMOVE PRODUCT");

        // get product id
        std::cout << "Enter product ID to remove :: ";
        std::getline(std::cin, id_str);

        // convert string id into integer id
        try
        {
            id = std::stoi(id_str);
            product.setId(id);
        }
        catch (const std::invalid_argument &e)
        {
            id = 0;
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid input!");
        }

        if (id != 0)
        {
            // fetch product detail
            bool present = product.fetch();

            if (!present)
            {
                utils::showMessage(MESSAGE_TYPE::INFO, "\nNo product found with this ID!");
            }
            else
            {
                std::cout << "\n";
                product.view(); // preview product details
                std::cout << "\n";

                // check if the product is already removed
                if (product.getStatus() == PRODUCT_STATUS::REMOVED)
                    utils::showMessage(MESSAGE_TYPE::FAILURE, "\nThis product is already removed!");
                else
                {
                    std::cout << "\nAre you sure you want to remove this product [y/n]? ";
                    // ask user for removal confirmation
                    std::getline(std::cin, choice);

                    if (choice == "y" || choice == "Y")
                    {
                        if (product.remove())
                        {
                            utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nProduct removed successfully!");
                            Product::fetchAll(); // update product list
                        }
                        else
                            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nProduct removal failed!");
                    }
                }
            }
        }

        std::cout << "\n\nDo you want to remove another product [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "Y")
            break;
    }
}

// sell
void inventory_view::sell()
{
    utils::header("SELL PRODUCT");
    utils::pauseScreen();
}

#endif