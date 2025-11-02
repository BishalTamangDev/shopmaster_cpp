#include <iostream>
#include <fstream>
#include <string>

// import user-defined files :: header
#include "utils.h"
#include "file_setup.h"

#ifndef SHOPMASTER_ADMIN_H
#define SHOPMASTER_ADMIN_H

class Admin
{
private:
    std::string username;
    std::string password;
    std::string first_name;
    std::string middle_name;
    std::string last_name;

public:
    // setters
    void setUsername(std::string);
    void setPassword(std::string);
    void setFirstName(std::string);
    void setMiddleName(std::string);
    void setLastName(std::string);
    void setName(std::string, std::string, std::string);

    // getters
    std::string getUsername();
    std::string getPassword();
    std::string getFirstName();
    std::string getMiddle();
    std::string getLastName();
    std::string getFullName();

    bool registerAdmin(); // register
    bool loginAdmin();    // login
    bool isRegistered();  // check for admin registration
};

// setters
// setter :: set username
void Admin::setUsername(std::string username)
{
    this->username = username;
}

// setter :: set password
void Admin::setPassword(std::string password)
{
    this->password = password;
}

// setter :: first name
void Admin::setFirstName(std::string first_name)
{
    this->first_name = first_name;
}

// setter :: middle name
void Admin::setMiddleName(std::string middle_name)
{
    this->middle_name = middle_name;
}

// setter :: last name
void Admin::setLastName(std::string last_name)
{
    this->last_name = last_name;
}

// setter :: name
void Admin::setName(std::string first_name, std::string middle_middle, std::string last_last)
{
    this->first_name = first_name;
    this->middle_name = middle_middle;
    this->last_name = last_last;
}

// getters
// getter :: get username
std::string Admin::getUsername()
{
    return this->username;
}

// getter :: get password
std::string Admin::getPassword()
{
    return this->password;
}

// getter :: get first name
std::string Admin::getFirstName()
{
    return this->first_name;
}

// getter :: get middle name
std::string Admin::getMiddle()
{
    return this->middle_name;
}

// getter :: get last name
std::string Admin::getLastName()
{
    return this->last_name;
}

// getter :: get full name
std::string Admin::getFullName()
{
    return this->first_name + " " + this->middle_name + " " + this->last_name;
}

// register
bool Admin::registerAdmin()
{
    return true;
}

// login
bool Admin::loginAdmin()
{
    return true;
}

// check for admin registration
bool Admin::isRegistered()
{
    bool status = false;

    std::ifstream file(app_files::admin_file, std::ios::in);

    file.close();

    return status;
}

#endif