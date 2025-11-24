// include header file
#include "../include/product_manager.h"

// add new product
bool ProductManager::add(Product &product)
{
    std::fstream file;

    file.open(project_setup::filenames["product"], std::ios::in); // open file in append mode

    if (!file)
    {
        return false;
    }

    std::string line, headline;
    std::getline(file, headline); // get headline

    file.close();

    Product temp_product;

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

    return status;
}

// fetch product
bool ProductManager::fetch(int target_id, Product &product) const
{
    std::ifstream fin(project_setup::filenames["product"]);

    if (!fin)
    {
        return false;
    }

    bool found = false;

    std::string line;
    std::vector<Product> products;

    std::getline(fin, line); // skip header

    while (std::getline(fin, line))
    {
        Product temp_product;
        std::vector<std::any> line_data = utility::getLineData(line);

        if (temp_product.setByLineData(line_data))
        {
            if (temp_product.getId() == target_id)
            {
                found = true;
                product = temp_product;
                break;
            }
        }
    }

    return found;
}

// update product details
bool ProductManager::update(int target_id, Product &product)
{
    std::fstream file;

    file.open(project_setup::filenames["product"], std::ios::in);

    if (!file)
    {
        return false;
    }

    std::string heading;
    std::getline(file, heading); // get header
    file.close();

    std::string new_filename = "new_products.csv";

    file.open(new_filename, std::ios::out);
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

    return project_setup::updateFile(project_setup::filenames["product"], new_filename);
}

// remove product
bool ProductManager::remove(int target_id)
{
    std::fstream file;

    file.open(project_setup::filenames["product"], std::ios::in);

    if (!file)
    {
        return false;
    }

    std::string heading, new_filename = "new_products.csv";
    std::getline(file, heading); // get header
    file.close();

    // open file and update line
    file.open(new_filename, std::ios::out);
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

    return project_setup::updateFile(project_setup::filenames["product"], new_filename);
}

// fetch all products
std::vector<Product> ProductManager::fetchAllProducts()
{
    std::ifstream fin(project_setup::filenames["product"]);

    if (!fin)
    {
        return {};
    }

    std::string line;
    std::getline(fin, line); // skip header
    std::vector<Product> products;

    while (std::getline(fin, line))
    {
        Product product;
        std::vector<std::any> line_data = utility::getLineData(line);

        if (product.setByLineData(line_data))
        {
            products.push_back(std::move(product));
        }
    }

    return products;
}

// restock
bool ProductManager::restock(int id, int qty)
{
    if (id <= 0)
    {
        return false;
    }

    std::string headline;

    std::fstream file;

    file.open(project_setup::filenames["product"], std::ios::in);

    if (!file)
    {
        return false;
    }

    std::getline(file, headline); // get headline
    file.close();

    bool status = false;
    std::string temporary_file = "products_temp.csv";

    file.open(temporary_file, std::ios::out);
    file << headline << "\n";

    for (Product &product : ProductManager::fetchAllProducts())
    {
        if (product.getId() == id)
        {
            product.setQuantity(product.getQuantity() + qty); // update quantity

            if (product.getStatus() == PRODUCT_STATUS::OUT_OF_STOCK)
            {
                product.setStatus(PRODUCT_STATUS::AVAILABLE); // update product status
            }

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

    if (status)
    {
        status = project_setup::updateFile(project_setup::filenames["product"], temporary_file);
    }

    return status;
}

// search by id
bool ProductManager::searchById(int target_id, Product &product) const
{
    std::ifstream fin(project_setup::filenames["product"]);

    if (!fin)
    {
        return false;
    }

    bool found = false;

    std::string line;

    std::getline(fin, line); // skip header

    while (std::getline(fin, line))
    {
        Product temp_product;
        std::vector<std::any> line_data = utility::getLineData(line);

        if (temp_product.setByLineData(line_data))
        {
            if (temp_product.getId() == target_id)
            {
                product = temp_product;
                found = true;
                break;
            }
        }
    }

    return found;
}

// check if the product name is already taken
bool ProductManager::isValidProductName(std::string &new_name) const
{
    std::ifstream fin(project_setup::filenames["product"]);

    if (!fin)
    {
        return false;
    }

    bool valid_name = true;

    std::string line;

    std::getline(fin, line); // skip header

    while (std::getline(fin, line))
    {
        Product temp_product;
        std::vector<std::any> line_data = utility::getLineData(line);

        if (temp_product.setByLineData(line_data))
        {
            std::string old_name = temp_product.getName();

            utility::convertToLowerCase(old_name);
            utility::convertToLowerCase(new_name);

            if (temp_product.getName() == new_name)
            {
                valid_name = false;
                break;
            }
        }
    }

    return valid_name;
}

// get valid id :: get greatest id + 1
int ProductManager::getValidId() const
{
    std::ifstream fin(project_setup::filenames["sold_products"]);

    if (!fin)
    {
        return 1;
    }

    int new_id = 1;

    std::string buffer;
    std::vector<Product> products;

    std::getline(fin, buffer); // skip header

    while (std::getline(fin, buffer))
    {
        Product temp_product;

        if (temp_product.setByLineData(utility::getLineData(buffer)))
        {
            if (temp_product.getId() >= new_id)
            {
                new_id = temp_product.getId() + 1;
            }
        }
    }

    return new_id;
}

// sell product
bool ProductManager::sellProduct(std::vector<Product> cart)
{
    bool status = true;

    std::ofstream fout;

    std::vector<Product> all_products = ProductManager::fetchAllProducts(); // fetch all products

    // update stock & product status
    std::string new_filename = "products_temp.csv";

    fout.open(new_filename);

    fout << "ID,Name,Rate,Quantity,Added On,Removed On,Last Modified,Status\n";

    for (Product all_product : all_products)
    {
        for (Product cart_product : cart)
        {
            if (all_product.getId() == cart_product.getId())
            {
                all_product.setQuantity(all_product.getQuantity() - cart_product.getQuantity());

                if (all_product.getQuantity() <= 0)
                {
                    all_product.setStatus(PRODUCT_STATUS::OUT_OF_STOCK);
                }

                break;
            }
        }

        fout << all_product.getId() << ","
             << all_product.getName() << ","
             << all_product.getRate() << ","
             << all_product.getQuantity() << ","
             << utility::getDateString(all_product.getAddedDate(), true) << ","
             << utility::getDateString(all_product.getRemovedDate(), true) << ","
             << utility::getDateString(all_product.getLastModifiedDate(), true) << ","
             << all_product.getStatusString() << "\n";

        if (!fout.good())
        {
            status = false;
        }
    }

    fout.close();

    if (status)
    {
        project_setup::updateFile(project_setup::filenames["product"], new_filename);
    }

    // update cart || sold products
    fout.open(project_setup::filenames["sold_products"], std::ios::app);

    for (Product &product : cart)
    {
        fout << product.getSalesId() << ","
             << product.getId() << ","
             << product.getName() << ","
             << product.getRate() << ","
             << product.getQuantity() << "\n";

        if (!fout.good())
        {
            status = false;
        }
    }

    return status;
}

// search by name
std::vector<Product> ProductManager::searchByName(std::string &target_name) const
{
    std::string name;

    std::vector<Product> products = ProductManager::fetchAllProducts(); // fetch all products

    utility::convertToLowerCase(target_name); // convert target name into lowercase

    for (Product temp : products)
    {
        name = temp.getName();
        utility::convertToLowerCase(name); // convert name into lowercase

        if (name.find(target_name) != std::string::npos)
        {
            products.push_back(temp);
        }
    }

    return products;
}

// fetch products by status
std::vector<Product> ProductManager::fetchProductsByStatus(PRODUCT_STATUS status)
{
    std::ifstream fin(project_setup::filenames["product"]);

    if (!fin)
    {
        return {};
    }

    std::string buffer;
    std::vector<Product> products;

    std::getline(fin, buffer); // skip header

    while (std::getline(fin, buffer))
    {
        Product temp_product;

        bool response = temp_product.setByLineData(utility::getLineData(buffer));

        if (response && temp_product.getStatus() == status)
        {
            products.push_back(std::move(temp_product));
        }
    }

    return products;
}

// fetch sold products by sales id
std::vector<Product> ProductManager::fetchSoldProductsBySalesId(int sales_id)
{
    std::ifstream fin(project_setup::filenames["sold_products"]);

    if (!fin)
    {
        return {};
    }

    std::string buffer;
    std::vector<Product> products;

    std::getline(fin, buffer); // skip header

    while (std::getline(fin, buffer))
    {
        Product product;
        std::vector<std::any> data = utility::getLineData(buffer);

        try
        {
            product.setSalesId(std::stoi(std::any_cast<std::string>(data[0])));
            product.setId(std::stoi(std::any_cast<std::string>(data[1])));
            product.setName(std::any_cast<std::string>(data[2]));
            product.setRate(std::stod(std::any_cast<std::string>(data[3])));
            product.setQuantity(std::stoi(std::any_cast<std::string>(data[4])));

            if (product.getSalesId() == sales_id)
            {
                products.push_back(product);
            }
        }
        catch (const std::invalid_argument &e)
        {
            continue;
        }
    }

    return products;
}

// fetch all sold products
std::vector<Product> ProductManager::fetchAllSoldProducts()
{
    std::ifstream fin(project_setup::filenames["sold_products"]);

    if (!fin)
    {
        return {};
    }

    std::string buffer;
    std::vector<std::any> data;
    std::vector<Product> products;

    std::getline(fin, buffer); // header

    while (std::getline(fin, buffer))
    {
        Product product;

        data = utility::getLineData(buffer);

        try
        {
            product.setSalesId(std::stoi(std::any_cast<std::string>(data[0])));
            product.setId(std::stoi(std::any_cast<std::string>(data[1])));
            product.setName(std::any_cast<std::string>(data[2]));
            product.setRate(std::stod(std::any_cast<std::string>(data[3])));
            product.setQuantity(std::stoi(std::any_cast<std::string>(data[4])));

            products.push_back(product);
        }
        catch (const std::invalid_argument &e)
        {
            continue;
        }
    }

    fin.close();

    std::reverse(products.begin(), products.end()); // for placing latest sold product on top

    return products;
}

// fetch sold products by sales id
std::vector<Product> fetchSoldProductsBySalesId(int)
{
    std::ifstream fin(project_setup::filenames["sold_products"]);

    if (!fin)
    {
        return {};
    }

    std::vector<Product> sold_products;

    std::string line;

    std::getline(fin, line);

    while (std::getline(fin, line))
    {
        Product product;

        // individual data check
        if (product.setByLineData(utility::getLineData(line)))
        {
            sold_products.push_back(product);
        }
    }

    return sold_products;
}
