// import header files
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <vector>
#include <map>
#include <array>

// import user files
#include "utils.h"

#ifndef SHOPMASTER_FILE_H
#define SHOPMASTER_FILE_H

// app files
namespace app_files
{
    // filenames
    std::map<std::string, std::string> filenames = {
        {"admin", "admin.csv"},
        {"shop", "shop.csv"},
        {"employee", "employees.csv"},
        {"customer", "customers.csv"},
        {"product", "products.csv"},
    };

    // headlines
    std::map<std::string, std::vector<std::string>> headlines = {
        {
            filenames["admin"],               // file
            {"Username", "Password", "Name"}, // heading titles
        },
        {
            filenames["shop"],
            {"Name", "PAN", "Contact Number", "Currency", "District", "Municipality", "Tole/Village", "Ward"},
        },
        {
            filenames["employee"],
            {"ID", "Username", "Password", "Name", "Contact Number", "Added Date", "Removed Date", "Last Modified", "Status"},
        },
        {
            filenames["customer"],
            {"Sales ID", "Name"},
        },
        {filenames["product"],
         {"ID", "Name", "Rate", "Quantity", "Added On", "Removed On", "Last Modified", "Status"}},
    };

    void setup();                                              // setup files
    void createNewFile(std::string, std::vector<std::string>); // create new file
    bool updateFile(std::string, std::string);                 // updating file
}

// setup files :: check for the presence of files
void app_files::setup()
{
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
}

// create new file
void app_files::createNewFile(std::string filename, std::vector<std::string> titles)
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
}

// update file :: delete and rename
bool app_files::updateFile(std::string old_file, std::string new_file)
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

#endif