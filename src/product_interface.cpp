// include header file
#include "../include/product_interface.h"

// menu
void product_interface::menu()
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
        utility::header("PRODUCT MANAGEMENT MENU");

        for (const auto &option : options)
        {
            utility::showOption(option.first, option.second);
        }

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
        {
            product_interface::viewMenu();
        }
        else if (choice == "2")
        {
            product_interface::searchMenu();
        }
        else if (choice == "3")
        {
            product_interface::add();
        }
        else if (choice == "4")
        {
            product_interface::update();
        }
        else if (choice == "5")
        {
            product_interface::restock();
        }
        else if (choice == "6")
        {
            product_interface::remove();
        }
        else if (choice == "7")
        {
            return;
        }
        else
        {
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            utility::pauseScreen();
        }
    }
}

// add new product
void product_interface::add()
{
    Product product;
    ProductManager productManager;

    int qty;
    double rate;
    bool valid_rate, valid_qty, product_added;

    std::string name, rate_str, qty_str, choice;

    while (true)
    {
        valid_rate = false;
        valid_qty = false;

        utility::header("ADD NEW PRODUCT");

        // name
        std::cout << "Name        :: ";
        std::getline(std::cin, name);

        if (!productManager.isValidProductName(name))
        {
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nThis product is already added!");
        }
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
                    {
                        utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid rate!\n");
                    }
                }
                catch (const std::invalid_argument &e)
                {
                    utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid input!\n");
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
                    {
                        utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid quantity!\n");
                    }
                }
                catch (const std::invalid_argument &e)
                {
                    utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid input!\n");
                }
            }

            product.setAddedDate(utility::getCurrentDateTime());
            product.setStatus(PRODUCT_STATUS::AVAILABLE);

            int id = productManager.getValidId();

            product.setId(id);

            // preview product details
            utility::header("ADD NEW PRODUCT :: PRODUCT DETAILS");
            product.view();

            std::cout << "\n\nAre you sure you want to add this product [y/n]? ";
            std::getline(std::cin, choice);

            if (choice != "y" && choice != "Y")
            {
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nProduct addition cancelled!");
            }
            else
            {
                product_added = productManager.add(product);

                if (!product_added)
                {
                    utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nProduct addition failed!");
                }
                else
                {
                    utility::showMessage(utility::MESSAGE_TYPE::SUCCESS, "\nProduct added successfully!");
                }
            }
        }

        std::cout << "\n\nDo you want to add another product [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "Y")
        {
            break;
        }
    }
}

// update
void product_interface::update()
{
    int id;
    double rate;
    bool valid_id, detail_updated;

    std::string buffer;

    Product product, updated_product;
    ProductManager productManager;

    while (true)
    {
        detail_updated = false;

        utility::header("UPDATE PRODUCT DETAILS");

        // get product id
        std::cout << "Enter product ID to update :: ";
        std::getline(std::cin, buffer);

        try
        {
            id = std::stoi(buffer);
            product.setId(id);
            valid_id = true;
        }
        catch (const std::invalid_argument &e)
        {
            valid_id = false;
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid input!\n");
        }

        if (valid_id)
        {
            if (!productManager.fetch(id, product))
            {
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nProduct not found!\n");
            }
            else
            {
                if (product.getStatus() == PRODUCT_STATUS::REMOVED)
                {
                    utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nYou cannot update the details of already removed products!\n");
                }
                else
                {
                    // preview product details
                    std::cout << "\n";
                    product.view();

                    // check for correct product
                    std::cout << "\n\nAre you sure you want to update this product [y/n]? ";
                    std::getline(std::cin, buffer);

                    if (buffer == "y" || buffer == "Y")
                    {
                        // get new details
                        std::cout << "\nGETTING NEW DETAILS\n";

                        updated_product = product;

                        // name
                        std::cout << "\nName        :: ";
                        std::getline(std::cin, buffer);

                        if (!buffer.empty())
                        {
                            // check if the name is already taken
                            utility::convertToWordCase(buffer);

                            if (buffer != product.getName())
                            {
                                detail_updated = true;
                                updated_product.setName(buffer);
                            }
                        }

                        // rate
                        while (true)
                        {
                            std::cout << "\nRate        :: ";
                            std::getline(std::cin, buffer);

                            if (buffer.empty())
                            {
                                break;
                            }
                            else
                            {
                                try
                                {
                                    rate = std::stod(buffer);

                                    if (rate > 0.0)
                                    {
                                        if (rate != product.getRate())
                                        {
                                            detail_updated = true;
                                            updated_product.setRate(rate);
                                        }
                                        break;
                                    }
                                    else
                                    {
                                        utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nInvalid rate!\n");
                                    }
                                }
                                catch (const std::invalid_argument &e)
                                {
                                    utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nInvalid input!\n");
                                }
                            }
                        }

                        if (!detail_updated)
                        {
                            utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nNo details to be updated updated!\n");
                        }
                        else
                        {
                            updated_product.setLastModifiedDate(utility::getCurrentDateTime()); // get latest date

                            std::cout << "\nUPDATED PRODUCT DETAILS\n\n";
                            updated_product.view();

                            std::cout << "\n\nAre you sure you want to update this product [y/n]? ";
                            std::getline(std::cin, buffer);

                            if (buffer != "y" && buffer != "Y")
                            {
                                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nProduct update cancelled!\n");
                            }
                            else
                            {
                                if (productManager.update(id, updated_product))
                                {
                                    utility::showMessage(utility::MESSAGE_TYPE::SUCCESS, "\nProduct updated successfully!\n");
                                }
                                else
                                {
                                    utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nProduct update failed!\n");
                                }
                            }
                        }
                    }
                }
            }
        }

        std::cout << "\nDo you want to update another product [y/n]? ";
        std::getline(std::cin, buffer);

        if (buffer != "y" && buffer != "y")
        {
            break;
        }
    }
}

// restock
void product_interface::restock()
{
    int id, qty;
    bool valid_id, valid_qty;
    std::string id_str, qty_str, choice;

    Product product;
    ProductManager productManager;

    while (true)
    {
        utility::header("RESTOCK");

        // get product id
        std::cout << "Enter product ID to restock :: ";
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
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid input!\n");
        }

        if (valid_id)
        {
            if (!productManager.fetch(id, product))
            {
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nProduct not found!\n");
            }
            else
            {
                // preview product details
                std::cout << "\n";
                product.view();
                std::cout << "\n";

                // check if the product is removed
                if (product.getStatus() == PRODUCT_STATUS::REMOVED)
                {
                    utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nThis product is already removed!");
                }
                else
                {
                    // proceed
                    std::cout << "\nEnter the quantity to add :: ";
                    std::getline(std::cin, qty_str);

                    try
                    {
                        qty = std::stoi(qty_str);

                        if (qty == 0)
                        {
                            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid quantity!");
                        }
                        else
                        {
                            valid_qty = true;
                        }
                    }
                    catch (const std::invalid_argument &e)
                    {
                        valid_qty = false;
                        utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid input!");
                    }

                    if (valid_qty)
                    {
                        bool response = productManager.restock(id, qty);

                        if (response)
                        {
                            utility::showMessage(utility::MESSAGE_TYPE::SUCCESS, "\nStock updated successfully!");
                        }
                        else
                        {
                            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nCouldn't update stock!");
                        }
                    }
                }
            }
        }

        std::cout << "\n\nDo you want to restock another product [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "y")
        {
            break;
        }
    }
}

// remove
void product_interface::remove()
{
    int id;
    std::string id_str, choice;

    Product product;
    ProductManager productManager;

    while (true)
    {
        utility::header("REMOVE PRODUCT");

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
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid input!");
        }

        if (id != 0)
        {
            // fetch product detail
            bool present = productManager.fetch(id, product);

            if (!present)
            {
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nNo product found with this ID!");
            }
            else
            {
                std::cout << "\n";
                product.view(); // preview product details
                std::cout << "\n";

                // check if the product is already removed
                if (product.getStatus() == PRODUCT_STATUS::REMOVED)
                {
                    utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nThis product is already removed!");
                }
                else
                {
                    std::cout << "\nAre you sure you want to remove this product [y/n]? ";
                    std::getline(std::cin, choice);

                    if (choice == "y" || choice == "Y")
                    {
                        if (productManager.remove(id))
                        {
                            utility::showMessage(utility::MESSAGE_TYPE::SUCCESS, "\nProduct removed successfully!");
                        }
                        else
                        {
                            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nProduct removal failed!");
                        }
                    }
                }
            }
        }

        std::cout << "\n\nDo you want to remove another product [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "Y")
        {
            break;
        }
    }
}

// search menu
void product_interface::searchMenu()
{
    std::string choice;

    const std::map<int, std::string> options = {
        {1, "Search Product by ID"},
        {2, "Search Product by Name"},
        {3, "Go Back"},
    };

    while (true)
    {
        utility::header("SEARCH PRODUCT MENU");

        for (const auto &option : options)
        {
            utility::showOption(option.first, option.second);
        }

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
        {
            product_interface::searchById();
        }
        else if (choice == "2")
        {
            product_interface::searchByName();
        }
        else if (choice == "3")
        {
            return;
        }
        else
        {
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            utility::pauseScreen();
        }
    }
}

// search by id
void product_interface::searchById()
{
    int id;
    bool product_found;
    std::string id_str, choice;

    Product product;
    ProductManager productManager;

    while (true)
    {
        product_found = false;

        utility::header("SEARCH BY PRODUCT BY ID");

        std::cout << "Enter product ID to search :: ";
        std::getline(std::cin, id_str);

        std::cout << "\n";

        try
        {
            id = std::stoi(id_str);

            product_found = productManager.searchById(id, product);

            if (product_found)
            {
                product.view();
            }
            else
            {
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "No product found with this ID!");
            }
        }
        catch (const std::invalid_argument &e)
        {
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "Invalid input!");
        }

        std::cout << "\n\nDo you want to search another product [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "y")
        {
            break;
        }
    }
}

// search by name
void product_interface::searchByName()
{
    bool found;
    std::string name, target_name, choice;
    const std::vector<int> spaces = {6, 25, 12, 7, 12, 12, 15, 13};

    while (true)
    {
        found = false;
        utility::header("SEARCH BY PRODUCT BY NAMES");

        std::cout << "Enter product name to search :: ";
        std::getline(std::cin, target_name);

        utility::convertToLowerCase(target_name);

        std::cout << "\n";

        std::cout << std::left << std::setw(6) << "ID"
                  << std::setw(25) << "Name"
                  << std::setw(10) << std::right << "Rate" << "  "
                  << std::setw(5) << "Qty" << "  "
                  << std::setw(12) << std::left << "Added On"
                  << std::setw(12) << "Removed On"
                  << std::setw(15) << "Last Modified"
                  << std::setw(11) << "Status" << "\n";

        for (Product product : ProductManager::fetchAllProducts())
        {
            name = product.getName();
            utility::convertToLowerCase(name);

            if (name.find(target_name) != std::string::npos)
            {
                found = true;

                std::cout << std::left << std::setw(6) << product.getId()
                          << std::setw(25) << product.getName()
                          << std::setw(10) << std::right << product.getRate() << "  "
                          << std::setw(5) << product.getQuantity() << "  "
                          << std::setw(12) << std::left << utility::getDateString(product.getAddedDate(), false)
                          << std::setw(12) << utility::getDateString(product.getRemovedDate(), false)
                          << std::setw(15) << utility::getDateString(product.getLastModifiedDate(), false)
                          << std::setw(11) << product.getStatusString() << "\n";
            }
        }

        if (!found)
        {
            utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nNo product found with this name!\n");
        }

        std::cout << "\nDo you want to search another product [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "y")
        {
            break;
        }
    }
}

// view menu
void product_interface::viewMenu()
{
    std::string choice;

    const std::map<int, std::string> options = {
        {1, "View All Product"},
        {2, "View Available Products"},
        {3, "View Out of Stock Products"},
        {4, "View Removed Products"},
        {5, "View Sold Products"},
        {6, "Go Back"},
    };

    while (true)
    {
        utility::header("VIEW PRODUCT MENU");

        for (const auto &option : options)
        {
            utility::showOption(option.first, option.second);
        }

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
        {
            product_interface::viewAllProducts();
        }
        else if (choice == "2")
        {
            product_interface::viewAvailableProducts();
        }
        else if (choice == "3")
        {
            product_interface::viewOutOfStockProducts();
        }
        else if (choice == "4")
        {
            product_interface::viewRemovedProducts();
        }
        else if (choice == "5")
        {
            product_interface::viewSoldProducts();
        }
        else if (choice == "6")
        {
            return;
        }
        else
        {
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            utility::pauseScreen();
        }
    }
}

// view all products
void product_interface::viewAllProducts()
{
    utility::header("ALL PRODUCTS");

    std::vector<Product> products = ProductManager::fetchAllProducts();

    product_interface::viewFormattedProducts(products);

    if (products.empty())
    {
        utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nNo product has been been added yet!\n");
    }

    std::cout << "\nPress any key to continue...";

    utility::pauseScreen();
}

// view available products
void product_interface::viewAvailableProducts()
{
    utility::header("VIEW AVAILABLE PRODUCTS");

    std::vector<Product> available_products = ProductManager::fetchProductsByStatus(PRODUCT_STATUS::AVAILABLE);

    product_interface::viewFormattedProducts(available_products);

    if (available_products.empty())
    {
        utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nNo product available!\n");
    }

    std::cout << "\nPress any key to continue...";

    utility::pauseScreen();
}

// view out of stock products
void product_interface::viewOutOfStockProducts()
{
    utility::header("VIEW OUT OF STOCK PRODUCTS");

    std::vector<Product> out_of_stock_products = ProductManager::fetchProductsByStatus(PRODUCT_STATUS::OUT_OF_STOCK);

    product_interface::viewFormattedProducts(out_of_stock_products);

    if (out_of_stock_products.empty())
    {
        utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nNo product out of stock!\n");
    }

    std::cout << "\nPress any key to continue...";

    utility::pauseScreen();
}

// view removed products
void product_interface::viewRemovedProducts()
{
    utility::header("VIEW OUT OF STOCK PRODUCTS");

    std::vector<Product> out_of_stock_products = ProductManager::fetchProductsByStatus(PRODUCT_STATUS::REMOVED);

    product_interface::viewFormattedProducts(out_of_stock_products);

    if (out_of_stock_products.empty())
    {
        utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nNo removed product found!\n");
    }

    std::cout << "\nPress any key to continue...";

    utility::pauseScreen();
}

// view sold products
void product_interface::viewSoldProducts()
{
    utility::header("SOLD PRODUCTS");

    std::vector<Product> sold_products = ProductManager::fetchAllSoldProducts(); // fetch all sold products

    if (sold_products.empty())
    {
        utility::showMessage(utility::MESSAGE_TYPE::INFO, "No product sold yet!\n");
    }
    else
    {
        std::cout << std::left << std::setw(6) << "ID"
                  << std::setw(10) << "Sales ID"
                  << std::setw(25) << "Name"
                  << std::setw(10) << std::right << "Rate" << "  "
                  << std::setw(5) << "Qty" << "\n";

        for (Product product : sold_products)
        {
            std::cout << std::left << std::setw(6) << product.getId()
                      << std::setw(10) << product.getSalesId()
                      << std::setw(25) << product.getName()
                      << std::setw(10) << std::right << product.getRate() << "  "
                      << std::setw(5) << product.getQuantity() << "\n";
        }
    }

    std::cout << "\nPress any key to continue...";

    utility::pauseScreen();
}

// view formatted product
void product_interface::viewFormattedProducts(std::vector<Product> products)
{
    int total_qty = 0;
    double total_net_price = 0.0;

    std::cout << std::left << std::setw(6) << "ID"
              << std::setw(25) << "Name"
              << std::setw(10) << std::right << "Rate" << "  "
              << std::setw(5) << "Qty" << "  "
              << std::setw(12) << std::left << "Added On"
              << std::setw(12) << "Removed On"
              << std::setw(15) << "Last Modified"
              << std::setw(11) << "Status" << "\n";

    for (Product &product : products)
    {
        total_net_price += product.getRate() * product.getQuantity();
        total_qty += product.getQuantity();

        std::cout << std::left << std::setw(6) << product.getId()
                  << std::setw(25) << product.getName()
                  << std::setw(10) << std::right << product.getRate() << "  "
                  << std::setw(5) << product.getQuantity() << "  "
                  << std::setw(12) << std::left << utility::getDateString(product.getAddedDate(), false)
                  << std::setw(12) << utility::getDateString(product.getRemovedDate(), false)
                  << std::setw(15) << utility::getDateString(product.getLastModifiedDate(), false)
                  << std::setw(11) << product.getStatusString() << "\n";
    }

    if (total_qty > 0)
    {
        std::cout << "\nTotal quantity  :: " << total_qty << "\n";
        std::cout << "Total net price :: " << total_net_price << "\n";
    }
}
