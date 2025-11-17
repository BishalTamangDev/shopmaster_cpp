// include header file
#include "../include/employee_manager.h"

// add new employee
bool EmployeeManager::add(Employee emp)
{
    int valid_id = 1;

    std::fstream file;
    std::string line, headline;

    Employee temp_employee;

    // open file and get latest id + 1
    file.open(project_setup::filenames["employee"], std::ios::in); // open file in append mode
    std::getline(file, headline);                              // get headline

    // get valid id
    while (std::getline(file, line))
    {
        temp_employee.setByLineData(utility::getLineData(line));
        valid_id = temp_employee.getId() + 1;
    }
    file.close();

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

    file.close();

    return status;
}

// update username
bool EmployeeManager::update(Employee emp)
{
    std::string heading;

    // open file and get headline
    std::fstream file(project_setup::filenames["employee"], std::ios::in);
    std::getline(file, heading);
    file.close();

    // // open file and update line
    file.open("new_employee.csv", std::ios::out);
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
    file.close();

    return project_setup::updateFile(project_setup::filenames["employee"], "new_employee.csv");
}

// remove employee
bool EmployeeManager::remove(int target_id)
{
    std::fstream file;
    std::string heading, temporay_file = "employees_temp.csv";

    // open file and get headline
    file.open(project_setup::filenames["employee"], std::ios::in);
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
bool EmployeeManager::fetch(int id, Employee &emp)
{
    bool employee_found = false;

    for (Employee temp : EmployeeManager::fetchAllEmployees())
    {
        if (temp.getId() == id)
        {
            emp.setId(temp.getId());
            emp.setUsername(temp.getUsername());
            emp.setPassword(temp.getPassword());
            emp.setName(temp.getName());
            emp.setContactNumber(temp.getContactNumber());
            emp.setStatus(temp.getStatus());
            emp.setAddedDate(temp.getAddedDate());
            emp.setRemovedDate(temp.getRemovedDate());
            emp.setModifiedDate(temp.getLastModified());

            employee_found = true;
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
std::string EmployeeManager::getEmployeeName(int id)
{
    std::string name = "Unknown";

    auto employees = fetchAllEmployees();

    for(Employee employee : employees)
    {
        if(employee.getId() == id)
        {
            name = employee.getName();
            break;
        }
    }

    return name;
}

// fetch all employees
std::vector<Employee> EmployeeManager::fetchAllEmployees()
{
    Employee employee;

    std::string line;
    std::vector<Employee> employees;
    std::vector<std::any> line_data;

    std::ifstream file(project_setup::filenames["employee"]);

    std::getline(file, line); // heading

    while (std::getline(file, line))
    {
        line_data = utility::getLineData(line);
        employee.setByLineData(line_data);
        employees.push_back(employee);
    }

    file.close();

    return employees;
}