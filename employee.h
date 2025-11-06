#include <iostream>
#include <fstream>
#include <any>
#include <sstream>
#include <string>
#include <algorithm>

// import user-defined files :: header
#include "utils.h"
#include "file_setup.h"

#ifndef SHOPMASTER_EMPLOYEE_H
#define SHOPMASTER_EMPLOYEE_H

class Employee
{
private:
    std::string username;
    std::string password;
    std::string first_name;
    std::string middle_name;
    std::string last_name;
    std::string contact_number;

public:
    // setters
    void setUsername(std::string);
    void setPassword(std::string);
    void setFirstName(std::string);
    void setMiddleName(std::string);
    void setLastName(std::string);
    void setContactNumber(std::string);

    // getters
    std::string getUsername();
    std::string getPassword();
    std::string getFirstName();
    std::string getMiddleName();
    std::string getLastName();
    std::string getFullName();
    std::string getContactNumber();

    bool registerEmployee(); // register
    bool loginEmployee();    // login
    bool isRegistered();     // check for employee registration
    void fetchDetails();     // fetch employee details
    bool update();           // update
};

// setters
// setter :: set username
void Employee::setUsername(std::string username)
{
    utils::convertToWordCase(username);
    this->username = username;
}

// setter :: set password
void Employee::setPassword(std::string password)
{
    utils::eraseWhiteSpace(password);
    this->password = password;
}

// setter :: first name
void Employee::setFirstName(std::string first_name)
{
    utils::convertToWordCase(first_name);
    this->first_name = first_name;
}

// setter :: middle name
void Employee::setMiddleName(std::string middle_name)
{
    utils::convertToWordCase(middle_name);
    this->middle_name = middle_name;
}

// setter :: last name
void Employee::setLastName(std::string last_name)
{
    utils::convertToWordCase(last_name);
    this->last_name = last_name;
}

// getters
// getter :: get username
std::string Employee::getUsername()
{
    return this->username;
}

// getter :: get password
std::string Employee::getPassword()
{
    return this->password;
}

// getter :: get first name
std::string Employee::getFirstName()
{
    return this->first_name;
}

// getter :: get middle name
std::string Employee::getMiddleName()
{
    return this->middle_name;
}

// getter :: get last name
std::string Employee::getLastName()
{
    return this->last_name;
}

// getter :: get full name
std::string Employee::getFullName()
{
    if (this->middle_name.length() == 0)
        return this->first_name + " " + this->last_name;
    else
        return this->first_name + " " + this->middle_name + " " + this->last_name;
}

// register
bool Employee::registerEmployee()
{
    std::string username, password, first_name, middle_name, last_name;

    utils::header("EMPLOYEE REGISTRATION");

    utils::showMessage(MESSAGE_TYPE::INFO, "Employee has not been registered yet!");

    std::cout << "\n\nUsername :: ";
    std::getline(std::cin, username);
    this->setUsername(username);

    std::cout << "\nPassword :: ";
    std::getline(std::cin, password);
    this->setPassword(password);

    std::cout << "\nFirst name :: ";
    std::getline(std::cin, first_name);
    this->setFirstName(first_name);

    std::cout << "\nMiddle name [Press enter if you don't have a middle name] :: ";
    std::getline(std::cin, middle_name);
    this->setMiddleName(middle_name);

    std::cout << "\nLast name :: ";
    std::getline(std::cin, last_name);
    this->setLastName(last_name);

    // show Employee details
    utils::header("Employee REGISTRATION DETAILS");
    std::cout << "Username    :: " << this->username << "\n\n";
    std::cout << "Password    :: " << this->password << "\n\n";
    std::cout << "Name        :: " << this->getFullName() << "\n";

    std::ofstream file(app_files::employees_file, std::ios::app);
    file << this->username << "," << this->password << "," << this->first_name << "," << this->middle_name << "," << this->last_name << "\n";
    file.close();

    return file.good();
}

// login
bool Employee::loginEmployee()
{
    std::string username, password;

    utils::header("EMPLOYEE LOGIN");

    std::cout << "Username :: ";
    std::getline(std::cin, username);

    std::cout << "\nPassword :: ";
    std::getline(std::cin, password);

    return username == this->username && password == this->password;
}

// check for Employee registration
bool Employee::isRegistered()
{
    std::string line;
    std::vector<std::any> data;
    std::ifstream file(app_files::employees_file);

    std::getline(file, line); // healine
    std::getline(file, line);
    file.close(); // close file

    if (line.length() == 0)
        return false;
    else
    {
        data = utils::getLineData(line);

        this->setUsername(std::any_cast<std::string>(data[0]));
        this->setPassword(std::any_cast<std::string>(data[1]));

        return true;
    }
}

// fetch Employee details
void Employee::fetchDetails()
{
    std::ifstream file(app_files::employees_file);

    std::string line;

    std::getline(file, line); // heading
    std::getline(file, line);

    std::vector<std::any> data = utils::getLineData(line);

    this->username = std::any_cast<std::string>(data[0]);
    this->password = std::any_cast<std::string>(data[1]);
    this->first_name = std::any_cast<std::string>(data[2]);
    this->middle_name = std::any_cast<std::string>(data[3]);
    this->last_name = std::any_cast<std::string>(data[4]);

    file.close();
}

// update username
bool Employee::update()
{
    std::string heading;

    // open file and get headline
    std::fstream file(app_files::employees_file, std::ios::in);
    std::getline(file, heading);
    file.close();

    // open file and update line
    file.open(app_files::employees_file, std::ios::out);

    file << heading << "\n"; // write heading
    file << this->username << "," << this->password << "," << this->first_name << "," << this->middle_name << "," << this->last_name << "\n";

    file.close();

    return file.good();
}

#endif