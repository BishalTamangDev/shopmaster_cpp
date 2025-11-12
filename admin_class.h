#include <iostream>
#include <fstream>
#include <any>
#include <sstream>
#include <string>
#include <algorithm>

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
    std::string name;

public:
    // setters
    void setUsername(std::string);
    void setPassword(std::string);
    void setName(std::string);
    bool setByLineData(std::vector<std::any>); // set admin using line data

    // getters
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getName();

    bool registration();                  // register
    bool login(std::string, std::string); // login
    bool fetch();                         // fetch admin details
    bool update();                        // update admin details
};

// setters
// setter :: set username
void Admin::setUsername(std::string username)
{
    utils::eraseWhiteSpace(username);
    utils::convertToLowerCase(username);
    this->username = username;
}

// setter :: set password
void Admin::setPassword(std::string password)
{
    utils::eraseWhiteSpace(password);
    this->password = password;
}

// setter :: name
void Admin::setName(std::string name)
{
    utils::convertToWordCase(name);
    this->name = name;
}

// set by line data
bool Admin::setByLineData(std::vector<std::any> data)
{
    try
    {
        this->username = std::any_cast<std::string>(data[0]);
        this->password = std::any_cast<std::string>(data[1]);
        this->name = std::any_cast<std::string>(data[2]);
        return true;
    }
    catch (const char *e)
    {
#ifdef DEBUG_MODE
        std::cerr << "\n\nError: " << e << "\n";
        utils::pauseScreen();
#endif
        return false;
    }
}

// getters
// getter :: get username
std::string Admin::getUsername() const
{
    return this->username;
}

// getter :: get password
std::string Admin::getPassword() const
{
    return this->password;
}

// getter :: name
std::string Admin::getName()
{
    utils::convertToWordCase(this->name);
    return this->name;
}

// register
bool Admin::registration()
{
    std::ofstream file(app_files::filenames["admin"], std::ios::app);
    file << this->username << "," << this->password << "," << this->name << "\n";
    file.close();

    return file.good();
}

// login
bool Admin::login(std::string username, std::string password)
{
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
        this->setByLineData(data); // set admin using line data
        return username == this->username && password == this->password;
    }
}

// fetch admin details
bool Admin::fetch()
{
    std::string line;
    std::ifstream file(app_files::filenames["admin"]);

    std::getline(file, line); // heading
    std::getline(file, line);
    file.close();

    return this->setByLineData(utils::getLineData(line));
}

// update username
bool Admin::update()
{
    std::string heading;

    std::fstream file;

    // open file and get headline
    file.open(app_files::filenames["admin"], std::ios::in);
    std::getline(file, heading);
    file.close();

    // open file and update line
    file.open(app_files::filenames["admin"], std::ios::out);

    file << heading << "\n"; // write heading
    file << this->username << "," << this->password << "," << this->name << "\n";

    bool status = file.good();

    file.close();

    return status;
}

#endif