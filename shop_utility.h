#include <iostream>
#include <any>
#include <vector>
#include <fstream>
#include <string>

// import user-defined files
#include "file_setup.h"
#include "shop_class.h"

#ifndef SHOPMASTER_SHOP_UTILITY_H
#define SHOPMASTER_SHOP_UTILITY_H

namespace shop_utility
{
    bool isRegistered(); // check for shop registration
}

// check for shop registration
bool shop_utility::isRegistered()
{
    std::string line;
    std::vector<std::any> data;
    std::ifstream file(app_files::filenames["shop"]);

    std::getline(file, line); // healine
    std::getline(file, line); // get shop details
    file.close();

    return line.length() > 0;
}

#endif