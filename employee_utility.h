#include <iostream>

// import user-defined header files
#include "utils.h"
#include "file_setup.h"
#include "employee_class.h"

#ifndef SHOPMASTER_EMPLOYEE_UTILITY_H
#define SHOPMASTER_EMPLOYEE_UTILITY_H

namespace employee_utility
{
    bool remove(int);                          // remove employees
}

// remove employee
bool employee_utility::remove(int target_id)
{
    std::fstream file;
    std::string heading, temporay_file = "employees_temp.csv";

    // open file and get headline
    file.open(app_files::filenames["employee"], std::ios::in);
    std::getline(file, heading);
    file.close();

    // open file and update line
    file.open(temporay_file, std::ios::out);
    file << heading << "\n"; // write heading

    for (Employee temp : Employee::fetchAllEmployees())
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
            << temp.getName() << ","
            << temp.getContactNumber() << ","
            << utils::getDateString(temp.getAddedDate(), true) << ","
            << utils::getDateString(temp.getRemovedDate(), true) << ","
            << utils::getDateString(temp.getLastModified(), true) << ","
            << temp.getStatusString() << "\n";
    }

    file.close();

    return app_files::updateFile(app_files::filenames["employee"], temporay_file);
}

#endif