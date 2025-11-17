#pragma once

// include header file
#include "shop.h"

class ShopManager
{
public:
    bool registrationStatus(); // check registration status
    bool registration(Shop);   // register shop
    bool fetch(Shop &);        // fetch shop details
    bool update(Shop);         // update shop details

    static std::string getCurrency(); // get currency
};