// include header file
#include "../include/admin.h"

// setter :: name
void Admin::setName(std::string name)
{
    utility::convertToWordCase(name);
    this->name = name;
}

// setter :: username
void Admin::setUsername(std::string username)
{
    utility::eraseWhiteSpace(username);
    utility::convertToLowerCase(username);
    this->username = username;
}

// setter :: password
void Admin::setPassword(std::string password)
{
    this->password = password;
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
        utility::pauseScreen();
#endif
        return false;
    }
}

// getters
// getter :: username
std::string Admin::getUsername() const
{
    return this->username;
}

// getter :: password
std::string Admin::getPassword() const
{
    return this->password;
}

// getter :: name
std::string Admin::getName() const
{
    return this->name;
}