#include <iostream>
#include <vector>
#include <any>
#include <string>
#include <fstream>

#include "file_setup.h"
#include "admin_class.h"

#ifndef SHOPMASTER_ADMIN_UTILITY_H
#define SHOPMASTER_ADMIN_UTILITY_H

namespace admin_utility
{
    bool adminRegistered(); // check if admin has been already registered
}

// check if admin has been already registered
bool admin_utility::adminRegistered()
{
    Admin admin;

    std::string line;
    std::vector<std::any> data;
    std::ifstream file(app_files::filenames["admin"]);

    std::getline(file, line); // healine
    std::getline(file, line);
    file.close(); // close file

    if (line.length() == 0)
        return false;
    else
    {
        data = utils::getLineData(line);
        return admin.setByLineData(data); // set admin using line data
    }
}

#endif