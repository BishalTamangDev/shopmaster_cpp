#pragma once

// include header file
#include "project_setup.h"

// employee status enum
enum class EMPLOYEE_STATUS
{
    INACTIVE,
    ACTIVE,
};

// class :: Employee
class Employee
{
private:
    int id;
    std::string username;
    std::string password;
    std::string name;
    std::string contact_number;
    EMPLOYEE_STATUS status;
    std::array<int, 3> added_date = {0, 0, 0};
    std::array<int, 3> removed_date = {0, 0, 0};
    std::array<int, 3> last_modified = {0, 0, 0};

public:
    Employee() // constructor
    {
        this->id = 0;
        this->username = "";
        this->password = "";
        this->name = "";
        this->contact_number = "";
        this->status = EMPLOYEE_STATUS::INACTIVE;
        this->added_date = {0, 0, 0};
        this->removed_date = {0, 0, 0};
        this->last_modified = {0, 0, 0};
    }

    // setters
    void setId(int);
    void setUsername(std::string);
    void setPassword(std::string);
    void setName(std::string);
    void setContactNumber(std::string);
    void setStatus(EMPLOYEE_STATUS);
    void setStatusByString(std::string);
    void setAddedDate(std::array<int, 3>);
    void setRemovedDate(std::array<int, 3>);
    void setModifiedDate(std::array<int, 3>);
    bool setByLineData(std::vector<std::any>); // set admin using line data

    // getters
    int getId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getName() const;
    std::string getContactNumber();
    EMPLOYEE_STATUS getStatus() const;
    std::string getStatusString() const;
    std::array<int, 3> getAddedDate() const;
    std::array<int, 3> getRemovedDate() const;
    std::array<int, 3> getLastModified() const;
    int getStatusInteger(EMPLOYEE_STATUS) const;

    void show(bool); // show employee details
};