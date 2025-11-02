#include <iostream>
#include <fstream>
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
    // files
    const std::string admin_file = "admin.csv";
    const std::string shop_file = "shop.csv";

    const std::map<std::string, std::vector<std::string>> files = {
        {
            admin_file,                                                         // file
            {"Username", "Password", "First Name", "Middle Name", "Last Name"}, // heading titles
        },
        {
            shop_file,
            {"Name", "PAN", "Contact Number", "Currency", "District", "Municipality", "Tole/Village", "Ward"},
        },
    };

    void setup();                                              // setup files
    void createNewFile(std::string, std::vector<std::string>); // create new file
}

// setup files :: check for the presence of files
void app_files::setup()
{
    std::string line, cell;
    std::ifstream fin;
    std::ofstream fout;

    std::vector<std::string> required_heading_titles = {};
    std::vector<std::string> actual_heading_titles = {};

    for (const auto &file : files)
    {
        required_heading_titles = file.second; // get heading titles
        actual_heading_titles.clear();         // clear actual heading titles

        fin.open(file.first);

        if (!fin.is_open()) // file not found
            createNewFile(file.first, required_heading_titles);
        else
        {
            std::getline(fin, line); // get a line
            fin.close();

            std::stringstream row(line);         // convert line into stream of string
            while (std::getline(row, cell, ',')) // access each string :: separated by comma
                actual_heading_titles.push_back(cell);

            if (required_heading_titles != actual_heading_titles)
                createNewFile(file.first, required_heading_titles); //  create new file
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

#endif