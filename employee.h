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

enum class EMPLOYEE_STATUS
{
    INACTIVE = 0,
    ACTIVE = 1,
};

class Employee
{
private:
    int id;
    std::string username;
    std::string password;
    std::string first_name;
    std::string middle_name;
    std::string last_name;
    std::string contact_number;
    EMPLOYEE_STATUS status;
    std::array<int, 6> added_date = {0, 0, 0};
    std::array<int, 6> removed_date = {0, 0, 0};
    std::array<int, 6> modified_date = {0, 0, 0};

public:
    Employee() // constructor
    {
        this->id = 0;
        this->username = "";
        this->password = "";
        this->first_name = "";
        this->middle_name = "";
        this->last_name = "";
        this->contact_number = "";
        this->status = EMPLOYEE_STATUS::INACTIVE;
        this->added_date = {0, 0, 0};
        this->removed_date = {0, 0, 0};
        this->modified_date = {0, 0, 0};
    }

    // setters
    void setId(int);
    void setUsername(std::string);
    void setPassword(std::string);
    void setFirstName(std::string);
    void setMiddleName(std::string);
    void setLastName(std::string);
    void setContactNumber(std::string);
    void setStatus(EMPLOYEE_STATUS);
    void setStatusByString(std::string);
    void setAddedDate(std::array<int, 6>);
    void setRemovedDate(std::array<int, 6>);
    void setModifiedDate(std::array<int, 6>);
    bool setByLineData(std::vector<std::any>); // set admin using line data

    // getters
    int getId();
    std::string getUsername();
    std::string getPassword();
    std::string getFirstName();
    std::string getMiddleName();
    std::string getLastName();
    std::string getFullName();
    std::string getContactNumber();
    EMPLOYEE_STATUS getStatus();
    std::string getStatusString();
    std::array<int, 6> getAddedDate();
    std::array<int, 6> getRemovedDate();
    std::array<int, 6> getModifiedDate();

    int getStatusInteger(EMPLOYEE_STATUS);

    bool add();                                  // add new employee
    bool login(std::string, std::string, int &); // login
    bool fetch(int id);                          // fetch employee details
    bool update();                               // update

    // static variables & functions
    static bool remove(int id); // remove
    static std::vector<Employee> LIST;
    static void fetchAll(); // fetch employee details
};

std::vector<Employee> Employee::LIST;

// setters
// setter :: id
void Employee::setId(int id)
{
    this->id = id;
}

// setter :: set username
void Employee::setUsername(std::string username)
{
    utils::convertToLowerCase(username);
    this->username = username;
}

// setter :: set password
void Employee::setPassword(std::string password)
{
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

// setter :: last name
void Employee::setContactNumber(std::string contact_number)
{
    this->contact_number = contact_number;
}

// setter :: last name
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
    this->modified_date = date;
}

// set admin using line data
bool Employee::setByLineData(std::vector<std::any> data)
{
    try
    {
        this->id = std::stoi(std::any_cast<std::string>(data[0]));
        this->username = std::any_cast<std::string>(data[1]);
        this->password = std::any_cast<std::string>(data[2]);

        this->setFirstName(std::any_cast<std::string>(data[3]));
        this->setMiddleName(std::any_cast<std::string>(data[4]));
        this->setLastName(std::any_cast<std::string>(data[5]));

        this->contact_number = std::any_cast<std::string>(data[6]);

        std::string date_string;

        // added date
        date_string = std::any_cast<std::string>(data[7]);
        if (date_string.empty())
            this->setAddedDate({0, 0, 0, 0, 0, 0});
        else
        {
            std::array<int, 6> arr_added_date = utils::getDateFromString(date_string);
            this->setAddedDate(arr_added_date);
        }

        // removed date
        date_string = std::any_cast<std::string>(data[8]);
        if (date_string.empty())
            this->setRemovedDate({0, 0, 0, 0, 0, 0});
        else
        {
            std::array<int, 6> arr_added_date = utils::getDateFromString(date_string);
            this->setRemovedDate(arr_added_date);
        }

        // modified date
        date_string = std::any_cast<std::string>(data[9]);

        if (date_string.empty())
            this->setModifiedDate({0, 0, 0, 0, 0, 0});
        else
        {
            std::array<int, 6> arr_modified_date = utils::getDateFromString(date_string);
            this->setModifiedDate(arr_modified_date);
        }

        this->setStatusByString(std::any_cast<std::string>(data[10]));

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
// getter :: id
int Employee::getId()
{
    return this->id;
}

// getter :: username
std::string Employee::getUsername()
{
    return this->username;
}

// getter :: password
std::string Employee::getPassword()
{
    return this->password;
}

// getter :: first name
std::string Employee::getFirstName()
{
    return this->first_name;
}

// getter :: middle name
std::string Employee::getMiddleName()
{
    return this->middle_name;
}

// getter :: last name
std::string Employee::getLastName()
{
    return this->last_name;
}

// getter :: full name
std::string Employee::getFullName()
{
    if (this->middle_name.length() == 0)
        return this->first_name + " " + this->last_name;
    else
        return this->first_name + " " + this->middle_name + " " + this->last_name;
}

// getter :: contact number
std::string Employee::getContactNumber()
{
    return this->contact_number;
}

// getter :: status
EMPLOYEE_STATUS Employee::getStatus()
{
    return this->status;
}

std::string Employee::getStatusString()
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
std::array<int, 6> Employee::getAddedDate()
{
    return this->added_date;
}

// getter :: removed date
std::array<int, 6> Employee::getRemovedDate()
{
    return this->removed_date;
}

// getter :: modified date
std::array<int, 6> Employee::getModifiedDate()
{
    return this->modified_date;
}

// get status integer
int Employee::getStatusInteger(EMPLOYEE_STATUS status)
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

// add new employee
bool Employee::add()
{
    int valid_id = 1;
    std::fstream file;
    std::string line, headline;

    Employee temp_employee;

    // open file and get latest id + 1
    file.open(app_files::employees_file, std::ios::in); // open file in append mode
    std::getline(file, headline);                       // get headline

    // get valid id
    while (std::getline(file, line))
    {
        temp_employee.setByLineData(utils::getLineData(line));
        valid_id = temp_employee.getId() + 1;
    }
    file.close();

    this->setId(valid_id); // set new valid id

    // add process
    file.open(app_files::employees_file, std::ios::app); // open file in append mode

    file
        << this->id << ","
        << this->username << ","
        << this->password << ","
        << this->first_name << ","
        << this->middle_name << ","
        << this->last_name << ","
        << this->contact_number << ","
        << utils::getDateString(this->added_date, true) << ","
        << utils::getDateString(this->removed_date, true) << ","
        << utils::getDateString(this->modified_date, true) << ","
        << this->getStatusString() << "\n";
    file.close();

    return file.good();
}

// login
bool Employee::login(std::string username, std::string password, int &current_emp_id)
{
    bool status = false;

    Employee::fetchAll(); // update employee list

    for (Employee employee : Employee::LIST)
    {
        if (employee.getUsername() == username && employee.getPassword() == password)
        {
            current_emp_id = employee.getId();
            status = true;
            break;
        }
    }

    return status;
}

// fetch employee details
bool Employee::fetch(int id)
{
    bool employee_found = false;

    for (Employee temp : Employee::LIST)
    {
        if (temp.getId() == id)
        {
            this->id = temp.getId();
            this->username = temp.getUsername();
            this->password = temp.getPassword();
            this->first_name = temp.getFirstName();
            this->middle_name = temp.getMiddleName();
            this->last_name = temp.getLastName();
            this->contact_number = temp.getContactNumber();
            this->status = temp.getStatus();
            this->added_date = temp.getAddedDate();
            this->removed_date = temp.getRemovedDate();
            this->modified_date = temp.getModifiedDate();

            employee_found = true;
            break;
        }
    }

    return employee_found;
}

// fetch employee details
void Employee::fetchAll()
{
    Employee employee;
    std::string line;
    std::vector<Employee> employees;
    std::vector<std::any> line_data;

    std::ifstream file(app_files::employees_file);

    std::getline(file, line); // heading

    while (std::getline(file, line))
    {
        line_data = utils::getLineData(line);
        employee.setByLineData(line_data);
        employees.push_back(employee);
    }
    Employee::LIST = employees;

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

    // // open file and update line
    file.open("new_employee.csv", std::ios::out);
    file << heading << "\n"; // write heading

    for (Employee &temp : Employee::LIST)
    {
        if (temp.getId() != this->id)
        {
            file
                << temp.getId() << ","
                << temp.getUsername() << ","
                << temp.getPassword() << ","
                << temp.getFirstName() << ","
                << temp.getMiddleName() << ","
                << temp.getLastName() << ","
                << temp.getContactNumber() << ","
                << utils::getDateString(temp.getAddedDate(), true) << ","
                << utils::getDateString(temp.getRemovedDate(), true) << ","
                << utils::getDateString(temp.getModifiedDate(), true) << ","
                << temp.getStatusString() << "\n";
        }
        else
        {
            file
                << this->id << ","
                << this->username << ","
                << this->password << ","
                << this->first_name << ","
                << this->middle_name << ","
                << this->last_name << ","
                << this->contact_number << ","
                << utils::getDateString(this->added_date, true) << ","
                << utils::getDateString(this->removed_date, true) << ","
                << utils::getDateString(this->modified_date, true) << ","
                << this->getStatusString() << "\n";
        }
    }
    file.close();

    return app_files::updateFile(app_files::employees_file, "new_employee.csv");
}

// remove
bool Employee::remove(int target_id)
{
    std::fstream file;
    std::string heading;

    // open file and get headline
    file.open(app_files::employees_file, std::ios::in);
    std::getline(file, heading);
    file.close();

    // open file and update line
    file.open("new_employees.csv", std::ios::out);
    file << heading << "\n"; // write heading

    for (Employee temp : Employee::LIST)
    {
        if (temp.getId() == target_id)
        {
            temp.setRemovedDate(utils::getCurrentDateTime());
            temp.setStatus(EMPLOYEE_STATUS::INACTIVE);
        }

        file
            << temp.getId() << ","
            << temp.getUsername() << ","
            << temp.getPassword() << ","
            << temp.getFirstName() << ","
            << temp.getMiddleName() << ","
            << temp.getLastName() << ","
            << temp.getContactNumber() << ","
            << utils::getDateString(temp.getAddedDate(), true) << ","
            << utils::getDateString(temp.getRemovedDate(), true) << ","
            << utils::getDateString(temp.getModifiedDate(), true) << ","
            << temp.getStatusString() << "\n";
    }

    file.close();

    return app_files::updateFile(app_files::employees_file, "new_employees.csv");
}

#endif