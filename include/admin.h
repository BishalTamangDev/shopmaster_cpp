#pragma once

// include header file
#include "utility.h"

class Admin
{
private:
    std::string name;
    std::string username;
    std::string password;

public:
    // constructor
    Admin()
    {
        this->username = "";
        this->password = "";
        this->name = "";
    }

    // setters
    void setName(std::string);
    void setUsername(std::string);
    void setPassword(std::string);
    bool setByLineData(std::vector<std::any>); // set admin using line data

    // getters
    std::string getName() const;
    std::string getUsername() const;
    std::string getPassword() const;
};