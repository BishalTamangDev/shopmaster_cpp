#pragma once

// include header file
#include "admin.h"

class AdminManager
{
public:
    bool registrationStatus();            // check admin registration status
    bool registration(Admin);             // register
    bool login(std::string, std::string); // login
    bool fetch(Admin &);                  // fetch admin details
    bool update(Admin);                   // update admin details
};