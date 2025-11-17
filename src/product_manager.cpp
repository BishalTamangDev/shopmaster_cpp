// include header file
#include "../include/product_manager.h"

// add new product
bool ProductManager::add(Product product)
{
    std::fstream file;
    std::string line, headline;

    Product temp_product;

    // open file and get headline
    file.open(project_setup::filenames["product"], std::ios::in); // open file in append mode
    std::getline(file, headline);                                 // get headline
    file.close();

    // add process
    file.open(project_setup::filenames["product"], std::ios::app); // open file in append mode

    file
        << product.getId() << ","
        << product.getName() << ","
        << product.getRate() << ","
        << product.getQuantity() << ","
        << utility::getDateString(product.getAddedDate(), true) << ","
        << utility::getDateString(product.getRemovedDate(), true) << ","
        << utility::getDateString(product.getLastModifiedDate(), true) << ","
        << product.getStatusString() << "\n";

    bool status = file.good();

    file.close();

    return status;
}

// fetch product
bool ProductManager::fetch(int id, Product &product)
{
    bool found = false;

    for (Product temp : ProductManager::fetchAllProducts())
    {
        if (temp.getId() == id)
        {
            found = true;
            product = temp;
            break;
        }
    }

    return found;
}

// update product details
bool ProductManager::update(int target_id, Product product)
{
    std::fstream file;
    std::string heading;

    // open file and get headline
    file.open(project_setup::filenames["product"], std::ios::in);
    std::getline(file, heading);
    file.close();

    // open file and update line
    file.open("new_products.csv", std::ios::out);
    file << heading << "\n"; // write heading

    for (Product temp : ProductManager::fetchAllProducts())
    {
        if (temp.getId() == target_id)
        {
            temp.setName(product.getName());
            temp.setRate(product.getRate());
            temp.setLastModifiedDate(product.getLastModifiedDate());
        }

        file
            << temp.getId() << ","
            << temp.getName() << ","
            << temp.getRate() << ","
            << temp.getQuantity() << ","
            << utility::getDateString(temp.getAddedDate(), true) << ","
            << utility::getDateString(temp.getRemovedDate(), true) << ","
            << utility::getDateString(temp.getLastModifiedDate(), true) << ","
            << temp.getStatusString() << "\n";
    }

    file.close();

    return project_setup::updateFile(project_setup::filenames["product"], "new_products.csv");
}

// remove product
bool ProductManager::remove(int target_id)
{
    std::fstream file;
    std::string heading;

    // open file and get headline
    file.open(project_setup::filenames["product"], std::ios::in);
    std::getline(file, heading);
    file.close();

    // open file and update line
    file.open("new_products.csv", std::ios::out);
    file << heading << "\n"; // write heading

    for (Product temp : ProductManager::fetchAllProducts())
    {
        if (temp.getId() == target_id)
        {
            temp.setRemovedDate(utility::getCurrentDateTime());
            temp.setStatus(PRODUCT_STATUS::REMOVED);
        }

        file
            << temp.getId() << ","
            << temp.getName() << ","
            << temp.getRate() << ","
            << temp.getQuantity() << ","
            << utility::getDateString(temp.getAddedDate(), true) << ","
            << utility::getDateString(temp.getRemovedDate(), true) << ","
            << utility::getDateString(temp.getLastModifiedDate(), true) << ","
            << temp.getStatusString() << "\n";
    }

    file.close();

    return project_setup::updateFile(project_setup::filenames["product"], "new_products.csv");
}

// fetch all products
std::vector<Product> ProductManager::fetchAllProducts()
{
    Product product;
    std::string line;
    std::vector<Product> products = {};
    std::vector<std::any> line_data;

    std::ifstream fin(project_setup::filenames["product"]);

    std::getline(fin, line); // headline

    while (std::getline(fin, line))
    {
        line_data = utility::getLineData(line);
        product.setByLineData(line_data);
        products.push_back(product);
    }

    fin.close();

    return products;
}

// restock
bool ProductManager::restock(int id, int qty)
{
    if (id <= 0)
        return false;

    bool status = false;

    std::string headline;
    std::string temporary_file = "products_temp.csv";
    std::fstream file;

    // get headline
    file.open(project_setup::filenames["product"], std::ios::in);
    std::getline(file, headline);
    file.close();

    file.open(temporary_file, std::ios::out);
    file << headline << "\n";

    for (Product &product : ProductManager::fetchAllProducts())
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
            << utility::getDateString(product.getAddedDate(), true) << ","
            << utility::getDateString(product.getRemovedDate(), true) << ","
            << utility::getDateString(product.getLastModifiedDate(), true) << ","
            << product.getStatusString() << "\n";
    }
    file.close();

    if (status)
        status = project_setup::updateFile(project_setup::filenames["product"], temporary_file);

    return status;
}

// search by id
bool ProductManager::searchById(int target_id, Product &product)
{
    bool found = false;

    for (Product temp : ProductManager::fetchAllProducts())
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
bool ProductManager::isValidProductName(std::string str)
{
    std::vector<Product> products = ProductManager::fetchAllProducts(); // fetch all products

    if (products.empty())
        return true;

    for (Product product : products)
        if (product.getName() == str)
            return false;

    return true;
}

// get valid id :: get greatest id + 1
int ProductManager::getValidId()
{
    int id = 1;

    std::vector<Product> products = ProductManager::fetchAllProducts(); // fetch all products

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
std::vector<Product> ProductManager::searchByName(std::string target_name)
{
    std::string name;

    std::vector<Product> products = ProductManager::fetchAllProducts(); // fetch all products

    utility::convertToLowerCase(target_name); // convert target name into lowercase

    for (Product temp : products)
    {
        name = temp.getName();
        utility::convertToLowerCase(name); // convert name into lowercase

        if (name.find(target_name) != std::string::npos)
            products.push_back(temp);
    }

    return products;
}

// fetch products by status
std::vector<Product> ProductManager::fetchProductsByStatus(PRODUCT_STATUS status)
{
    std::vector<Product> products;

    for (Product temp : ProductManager::fetchAllProducts())
        if (temp.getStatus() == status)
            products.push_back(temp);

    return products;
}

// fetch sold products by sales id
std::vector<Product> fetchSoldProductsBySalesId(int)
{
    Product product;
    std::vector<Product> sold_products;

    std::string line;
    std::vector<std::any> data;

    std::ifstream fin(project_setup::filenames["sold_products"]);

    std::getline(fin, line);

    while (std::getline(fin, line))
    {
        data = utility::getLineData(line);
        product.setByLineData(data);
        sold_products.push_back(product);
    }

    fin.close();

    return sold_products;
}
