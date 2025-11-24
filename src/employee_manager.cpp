// include header file
#include "../include/employee_manager.h"

// add new employee
bool EmployeeManager::add(Employee emp)
{
    std::fstream file;

    // open file and get latest id + 1
    file.open(project_setup::filenames["employee"], std::ios::in); // open file in append mode

    if (!file)
    {
        return false;
    }

    int valid_id = 1;

    std::string line, headline;
    std::getline(file, headline); // get headline

    // get valid id
    while (std::getline(file, line))
    {
        Employee temp_employee;

        if (temp_employee.setByLineData(utility::getLineData(line)))
        {
            valid_id = temp_employee.getId() + 1;
        }
    }

    file.close(); // close file

    emp.setId(valid_id);

    // add process
    file.open(project_setup::filenames["employee"], std::ios::app); // open file in append mode

    file
        << emp.getId() << ","
        << emp.getUsername() << ","
        << emp.getPassword() << ","
        << emp.getName() << ","
        << emp.getContactNumber() << ","
        << utility::getDateString(emp.getAddedDate(), true) << ","
        << utility::getDateString(emp.getRemovedDate(), true) << ","
        << utility::getDateString(emp.getLastModified(), true) << ","
        << emp.getStatusString() << "\n";

    bool status = file.good();

    return status;
}

// update username
bool EmployeeManager::update(Employee emp)
{
    std::fstream file(project_setup::filenames["employee"], std::ios::in);

    if (!file)
    {
        return false;
    }

    std::string heading, temp_file = "new_employee.csv";
    std::getline(file, heading);
    file.close();

    // // open file and update line
    file.open(temp_file, std::ios::out);
    file << heading << "\n"; // write heading

    for (Employee &temp : EmployeeManager::fetchAllEmployees())
    {
        if (temp.getId() != emp.getId())
        {
            file
                << temp.getId() << ","
                << temp.getUsername() << ","
                << temp.getPassword() << ","
                << temp.getName() << ","
                << temp.getContactNumber() << ","
                << utility::getDateString(temp.getAddedDate(), true) << ","
                << utility::getDateString(temp.getRemovedDate(), true) << ","
                << utility::getDateString(temp.getLastModified(), true) << ","
                << temp.getStatusString() << "\n";
        }
        else
        {
            file
                << emp.getId() << ","
                << emp.getUsername() << ","
                << emp.getPassword() << ","
                << emp.getName() << ","
                << emp.getContactNumber() << ","
                << utility::getDateString(emp.getAddedDate(), true) << ","
                << utility::getDateString(emp.getRemovedDate(), true) << ","
                << utility::getDateString(emp.getLastModified(), true) << ","
                << emp.getStatusString() << "\n";
        }
    }

    file.close(); // close file

    return project_setup::updateFile(project_setup::filenames["employee"], temp_file);
}

// remove employee
bool EmployeeManager::remove(int target_id)
{
    std::fstream file;

    // open file and get headline
    file.open(project_setup::filenames["employee"], std::ios::in);

    if (!file)
    {
        return false;
    }

    std::string heading, temporay_file = "employees_temp.csv";
    std::getline(file, heading);
    file.close();

    // open file and update line
    file.open(temporay_file, std::ios::out);
    file << heading << "\n"; // write heading

    for (Employee temp : EmployeeManager::fetchAllEmployees())
    {
        if (temp.getId() == target_id)
        {
            temp.setRemovedDate(utility::getCurrentDateTime());
            temp.setStatus(EMPLOYEE_STATUS::INACTIVE);
        }

        file
            << temp.getId() << ","
            << temp.getUsername() << ","
            << temp.getPassword() << ","
            << temp.getName() << ","
            << temp.getContactNumber() << ","
            << utility::getDateString(temp.getAddedDate(), true) << ","
            << utility::getDateString(temp.getRemovedDate(), true) << ","
            << utility::getDateString(temp.getLastModified(), true) << ","
            << temp.getStatusString() << "\n";
    }

    file.close();

    return project_setup::updateFile(project_setup::filenames["employee"], temporay_file);
}

// fetch employee
bool EmployeeManager::fetch(int target_id, Employee &employee)
{
    std::ifstream fin(project_setup::filenames["employee"]);

    if (!fin)
    {
        return false;
    }

    bool employee_found = false;

    std::string line;
    std::getline(fin, line); // heading

    while (std::getline(fin, line))
    {
        Employee temp_employee;

        if (temp_employee.setByLineData(utility::getLineData(line)) && temp_employee.getId() == target_id)
        {
            employee_found = true;
            employee = temp_employee;
            break;
        }
    }

    return employee_found;
}

// login
bool EmployeeManager::login(std::string username, std::string password, int &current_emp_id)
{
    bool status = false;

    for (Employee employee : EmployeeManager::fetchAllEmployees())
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

// get employee name
std::string EmployeeManager::getEmployeeName(int target_id)
{
    std::ifstream fin(project_setup::filenames["employee"]);

    if (!fin)
    {
        return "Unknown";
    }

    std::string name = "Unknown";
    std::string line;

    while (std::getline(fin, line))
    {
        Employee temp_employee;

        if (temp_employee.setByLineData(utility::getLineData(line)) && temp_employee.getId() == target_id)
        {
            name = temp_employee.getName();
            break;
        }
    }

    return name;
}

// fetch all employees
std::vector<Employee> EmployeeManager::fetchAllEmployees()
{
    std::ifstream fin(project_setup::filenames["employee"]);

    if (!fin)
    {
        return {};
    }

    std::string line;
    std::vector<Employee> employees;
    std::vector<std::any> line_data;

    std::getline(fin, line); // heading

    while (std::getline(fin, line))
    {
        Employee employee;

        if (employee.setByLineData(utility::getLineData(line)))
        {
            employees.push_back(employee);
        }
    }

    return employees;
}