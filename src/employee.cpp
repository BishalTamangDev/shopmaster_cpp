// include header file
#include "../include/employee.h"

// setter :: id
void Employee::setId(int id)
{
    this->id = id;
}

// setter :: set username
void Employee::setUsername(std::string username)
{
    utility::convertToLowerCase(username);
    this->username = username;
}

// setter :: set password
void Employee::setPassword(std::string password)
{
    this->password = password;
}

// setter :: name
void Employee::setName(std::string name)
{
    utility::convertToWordCase(name);
    this->name = name;
}

// setter :: contact number
void Employee::setContactNumber(std::string contact_number)
{
    this->contact_number = contact_number;
}

// setter :: status
void Employee::setStatus(EMPLOYEE_STATUS status)
{
    this->status = status;
}

// setter :: set status by string
void Employee::setStatusByString(std::string str)
{
    if (str == "Inactive" || str == "inactive" || str == "INACTIVE")
        this->status = EMPLOYEE_STATUS::INACTIVE;
    if (str == "Active" || str == "active" || str == "ACTIVE")
        this->status = EMPLOYEE_STATUS::ACTIVE;
    else
        this->status = EMPLOYEE_STATUS::INACTIVE;
}

// setter :: added date
void Employee::setAddedDate(std::array<int, 6> date)
{
    this->added_date = date;
}

// setter :: removed date
void Employee::setRemovedDate(std::array<int, 6> date)
{
    this->removed_date = date;
}

// setter :: modified date
void Employee::setModifiedDate(std::array<int, 6> date)
{
    this->last_modified = date;
}

// set admin using line data
bool Employee::setByLineData(std::vector<std::any> data)
{
    try
    {
        this->id = std::stoi(std::any_cast<std::string>(data[0]));
        this->username = std::any_cast<std::string>(data[1]);
        this->password = std::any_cast<std::string>(data[2]);
        this->setName(std::any_cast<std::string>(data[3]));
        this->contact_number = std::any_cast<std::string>(data[4]);

        std::string date_string;

        // added date
        date_string = std::any_cast<std::string>(data[5]);
        if (date_string.empty())
            this->setAddedDate({0, 0, 0, 0, 0, 0});
        else
        {
            std::array<int, 6> arr_added_date = utility::getDateFromString(date_string);
            this->setAddedDate(arr_added_date);
        }

        // removed date
        date_string = std::any_cast<std::string>(data[6]);
        if (date_string.empty())
            this->setRemovedDate({0, 0, 0, 0, 0, 0});
        else
        {
            std::array<int, 6> arr_added_date = utility::getDateFromString(date_string);
            this->setRemovedDate(arr_added_date);
        }

        // modified date
        date_string = std::any_cast<std::string>(data[7]);

        if (date_string.empty())
            this->setModifiedDate({0, 0, 0, 0, 0, 0});
        else
        {
            std::array<int, 6> arr_last_modified = utility::getDateFromString(date_string);
            this->setModifiedDate(arr_last_modified);
        }

        this->setStatusByString(std::any_cast<std::string>(data[8]));

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
// getter :: id
int Employee::getId() const
{
    return this->id;
}

// getter :: username
std::string Employee::getUsername() const
{
    return this->username;
}

// getter :: password
std::string Employee::getPassword() const
{
    return this->password;
}

// getter :: name
std::string Employee::getName() const
{
    return this->name;
}

// getter :: contact number
std::string Employee::getContactNumber()
{
    utility::convertToWordCase(this->contact_number);
    return this->contact_number;
}

// getter :: status
EMPLOYEE_STATUS Employee::getStatus() const
{
    return this->status;
}

std::string Employee::getStatusString() const
{
    switch (this->status)
    {
    case EMPLOYEE_STATUS::INACTIVE:
        return "Inactive";
    case EMPLOYEE_STATUS::ACTIVE:
        return "Active";
    default:
        return "Inactive";
    }
}

// getter :: added date
std::array<int, 6> Employee::getAddedDate() const
{
    return this->added_date;
}

// getter :: removed date
std::array<int, 6> Employee::getRemovedDate() const
{
    return this->removed_date;
}

// getter :: modified date
std::array<int, 6> Employee::getLastModified() const
{
    return this->last_modified;
}

// get status integer
int Employee::getStatusInteger(EMPLOYEE_STATUS status) const
{
    switch (status)
    {
    case EMPLOYEE_STATUS::INACTIVE:
        return 0;
    case EMPLOYEE_STATUS::ACTIVE:
        return 1;
    default:
        return 0;
    }
}

// show employee details
void Employee::show(bool adding)
{
    if (!adding)
        std::cout << "ID               :: " << this->getId() << "\n";
    std::cout << "Username         :: " << this->getUsername();
    std::cout << "\nPassword         :: " << this->getPassword();
    std::cout << "\nName             :: " << this->getName();
    std::cout << "\nContact Number   :: " << this->getContactNumber();
    std::cout << "\nJoined Date      :: " << utility::getDateString(this->getAddedDate(), false);
    std::cout << "\nRemoved Date     :: " << utility::getDateString(this->getRemovedDate(), false);
    std::cout << "\nLast Modified    :: " << utility::getDateString(this->getLastModified(), false);
    std::cout << "\nStatus           :: " << this->getStatusString();
}
