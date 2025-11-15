// include header files
#include "../include/project_setup.h"
#include "../include/admin_interface.h"

// project name
std::string project_setup::project_name = "ShopMaster - Shop Management"; // app name

// filenames
std::map<std::string, std::string> project_setup::filenames = {
    {"admin", "admin.csv"},
    {"shop", "shop.csv"},
    {"employee", "employees.csv"},
    {"customer", "customers.csv"},
    {"product", "products.csv"},
    {"sales", "sales.csv"},
    {"sold_products", "sold_products.csv"},
};

// headlines
std::map<std::string, std::vector<std::string>> project_setup::headlines = {
    {
        filenames["admin"], // file
        {
            "Username",
            "Password",
            "Name",
        }, // heading titles
    },
    {
        filenames["shop"],
        {
            "Name",
            "PAN",
            "Contact Number",
            "Currency",
            "District",
            "Municipality",
            "Tole/Village",
            "Ward",
        },
    },
    {
        filenames["employee"],
        {
            "ID",
            "Username",
            "Password",
            "Name",
            "Contact Number",
            "Added Date",
            "Removed Date",
            "Last Modified",
            "Status",
        },
    },
    {
        filenames["customer"],
        {
            "Sales ID",
            "Name",
        },
    },
    {
        filenames["sales"],
        {
            "Sales ID",
            "Customer ID",
            "Employee ID",
            "Net Amount",
            "Discount",
            "Gross Amount",
            "Tender",
            "Change",
            "Date",
        },
    },
    {
        filenames["product"],
        {
            "ID",
            "Name",
            "Rate",
            "Quantity",
            "Added On",
            "Removed On",
            "Last Modified",
            "Status",
        },
    },
    {
        filenames["sold_products"],
        {
            "Sales ID",
            "Product ID",
            "Name",
            "Rate",
            "Quantity",
        },
    },
};

// file setup
bool project_setup::fileSetup()
{
    bool status = false;

    std::string line, cell;
    std::ifstream fin;
    std::ofstream fout;

    std::vector<std::string> required_heading_titles = {};
    std::vector<std::string> actual_heading_titles = {};

    for (const auto &headline : headlines)
    {
        required_heading_titles = headline.second; // get heading titles
        actual_heading_titles.clear();             // clear actual heading titles

        fin.open(headline.first);

        if (!fin.is_open()) // file not found
            createNewFile(headline.first, required_heading_titles);
        else
        {
            std::getline(fin, line); // get a line
            fin.close();

            std::stringstream row(line);         // convert line into stream of string
            while (std::getline(row, cell, ',')) // access each string :: separated by comma
                actual_heading_titles.push_back(cell);

            if (required_heading_titles != actual_heading_titles)
                createNewFile(headline.first, required_heading_titles); //  create new file
        }
    }

    return status;
}

// create new file
bool project_setup::createNewFile(std::string filename, std::vector<std::string> titles)
{
    std::ofstream fout(filename);

    for (size_t i = 0; i < titles.size(); i++)
    {
        fout << titles[i];
        if (i < titles.size() - 1)
            fout << ",";
    }

    fout << "\n";

    fout.close();

    return true;
}

// update file
bool project_setup::updateFile(std::string old_file, std::string new_file)
{
    try
    {
        std::filesystem::remove(old_file);
        std::filesystem::rename(new_file, old_file);
        return true;
    }
    catch (std::filesystem::filesystem_error &e)
    {
        return false;
    }
}