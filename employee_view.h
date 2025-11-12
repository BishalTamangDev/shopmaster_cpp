#include <iostream>
#include <thread>

// import user-defined header files
#include "utils.h"
#include "employee_class.h"
#include "employee_utility.h"

#ifndef SHOPMASTER_EMPLOYEE_VIEW_H
#define SHOPMASTER_EMPLOYEE_VIEW_H

namespace employee_view
{
    void adminMenu();        // menu
    void add();              // add new employee
    void showDetails(int);   // my details
    void update();           // update employee details
    void remove();           // remove employee
    bool login(int &);       // login
    void viewAll();          // view all employees
    void searchById();       // search employee by id
    void searchByUsername(); // search employee by username
}

// admin menu
void employee_view::adminMenu()
{
    std::string choice;
    const std::map<int, std::string> options = {
        {1, "View Employeess"},
        {2, "Search Employee By ID"},
        {3, "Search Employee By Username"},
        {4, "Add Employees"},
        {5, "Update Employee Details"},
        {6, "Remove Employee"},
        {7, "Go Back"},
    };

    while (true)
    {
        utils::header("EMPLOYEE view MENU");

        for (const auto &options : options)
            utils::showOption(options.first, options.second);

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
            employee_view::viewAll(); // view employees
        else if (choice == "2")
            employee_view::searchById(); // search employee by id
        else if (choice == "3")
            employee_view::searchByUsername(); // search employee by username
        else if (choice == "4")
            employee_view::add(); // add employee
        else if (choice == "5")
            employee_view::update(); // update
        else if (choice == "6")
            employee_view::remove(); // remove employee
        else if (choice == "7")
            return;
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            utils::pauseScreen();
        }
    }
}

// employee :: show details
void employee_view::showDetails(int current_employee_id)
{
    Employee employee;

    bool response = employee.fetch(current_employee_id);

    utils::header("MY ACCOUNT DETAILS");

    if (!response)
        utils::showMessage(MESSAGE_TYPE::FAILURE, "Couldn't fetch employee details!");
    else
        employee.show(false);

    std::cout << "\n\nPress any key to continue...";

    utils::pauseScreen();
}

// login
bool employee_view::login(int &current_employee_id)
{
    int chance = 3;
    bool status = false;
    std::string username, password;
    Employee employee;

    while (true)
    {
        chance--;

        utils::header("EMPLOYEE LOGIN");

        std::cout << "Username :: ";
        std::getline(std::cin, username);

        std::cout << "\nPassword :: ";
        std::getline(std::cin, password);

        if (employee.login(username, password, current_employee_id))
        {
            status = true;
            break;
        }

        utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid username or password!");

        if (chance == 0)
        {
            utils::showMessage(MESSAGE_TYPE::INFO, "\n\nYou entered your credentials 3 times incorrectly!");
            break;
        }

        std::cout << "\n\nPress any key to try again...";
        utils::pauseScreen();
    }

    return status;
}

// employee :: view all employees
void employee_view::viewAll()
{
    utils::header("VIEW ALL EMPLOYEES");

    if (Employee::LIST.size() == 0)
    {
        utils::showMessage(MESSAGE_TYPE::INFO, "No employees found!");
        std::cout << "\n\nPress any key to go back...";
        utils::pauseScreen();
        return;
    }

    std::vector<int> spaces = {7, 22, 13, 12, 13, 12, 12, 16, 9};
    utils::showLine(spaces, {"ID", "Name", "Username", "Password", "Contact No.", "Added On", "Removed On", "Last Modified", "Status"});

    for (Employee &employee : Employee::LIST)
        utils::showLine(spaces, {std::to_string(employee.getId()), employee.getName(), employee.getUsername(), employee.getPassword(), employee.getContactNumber(), utils::getDateString(employee.getAddedDate(), false), utils::getDateString(employee.getRemovedDate(), false), utils::getDateString(employee.getLastModified(), false), employee.getStatusString()});

    std::cout << "\nPress any key to continue...";
    utils::pauseScreen();
}

// employee :: search employee by id
void employee_view::searchById()
{
    int id;
    bool found = false;
    std::string id_str, choice;

    while (true)
    {
        found = false;

        utils::header("SEARCH EMPLOYEE BY ID");
        std::cout << "Enter employee ID to search :: ";
        std::getline(std::cin, id_str);

        try
        {
            id = std::stoi(id_str);

            for (Employee employee : Employee::LIST)
            {
                if (employee.getId() == id)
                {
                    found = true;
                    std::cout << "\n";
                    employee.show(false);
                }
            }

            if (!found)
                utils::showMessage(MESSAGE_TYPE::INFO, "\nNo employee found with this ID.");
        }
        catch (const std::invalid_argument &e)
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid input!");
        }

        std::cout << "\n\nDo you want to search another employee [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "Y")
            break;
    }
}

// employee :: search employee by username
void employee_view::searchByUsername()
{
    bool found = false;
    std::string username, choice;

    while (true)
    {
        found = false;
        utils::header("SEARCH EMPLOYEE BY USERNAME");

        std::cout << "Enter username to search :: ";
        std::getline(std::cin, username);

        for (Employee employee : Employee::LIST)
        {
            if (employee.getUsername() == username)
            {
                found = true;
                std::cout << "\n";
                employee.show(false);
            }
        }

        if (!found)
            utils::showMessage(MESSAGE_TYPE::INFO, "\nNo employee found with this username.");

        std::cout << "\n\nDo you want to search another employee [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "Y")
            break;
    }
}

// employee :: add new employee
void employee_view::add()
{
    Employee employee;

    bool valid_username;

    std::string choice, username, password, name, contact_number;

    while (true)
    {
        valid_username = true;

        utils::header("ADD NEW EMPLOYEE");
        std::cout << "Username          :: ";
        std::getline(std::cin, username);

        for (Employee temp_employee : Employee::LIST)
        {
            if (temp_employee.getUsername() == username)
            {
                valid_username = false;
                break;
            }
        }

        if (valid_username)
            break;
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nThis username is already take!");
            std::cout << "\n\nDo you want to try again [y/n]? ";
            std::getline(std::cin, choice);

            if (choice != "Y" && choice != "y")
                return;
        }
    }

    employee.setUsername(username);

    std::cout << "\nPassword          :: ";
    std::getline(std::cin, password);
    employee.setPassword(password);

    std::cout << "\nName              :: ";
    std::getline(std::cin, name);
    employee.setName(name);

    std::cout << "\nContact Number    :: ";
    std::getline(std::cin, contact_number);
    employee.setContactNumber(contact_number);

    employee.setStatus(EMPLOYEE_STATUS::ACTIVE);
    employee.setAddedDate(utils::getCurrentDateTime());

    // show employee details
    utils::header("ADD NEW EMPLOYEE");
    std::cout << "Username          :: " << employee.getUsername() << "\n";
    std::cout << "Password          :: " << employee.getPassword() << "\n";
    std::cout << "Name              :: " << employee.getName() << "\n";
    std::cout << "Contact Number    :: " << employee.getContactNumber() << "\n";
    std::cout << "Added Date        :: " << utils::getDateString(employee.getAddedDate(), false) << "\n";
    std::cout << "Status            :: " << employee.getStatusString() << "\n";

    // ask user to proceed
    std::cout << "\nAre you sure you want to add [y/n]? ";
    std::getline(std::cin, choice);

    if (choice != "Y" && choice != "y")
        utils::showMessage(MESSAGE_TYPE::INFO, "\nEmployee addition cancelled.");
    else
    {
        if (employee.add())
        {
            utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nEmployee added successfully!");
            std::thread fetch_employees_thread(Employee::fetchAll);
            fetch_employees_thread.detach();
        }
        else
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nEmployee addition failed!");
    }

    std::cout << "\n\nPress any key to continue...";
    utils::pauseScreen();
}

// employee :: update employee details
void employee_view::update()
{
    int id;
    bool id_found;

    std::string id_str, choice;
    Employee employee;

    while (true)
    {
        utils::header("UPDATE EMPLOYEE DETAILS");

        std::cout << "Enter employee ID to update :: ";
        std::getline(std::cin, id_str);

        try
        {
            id = std::stoi(id_str);

            // check for id presence
            id_found = false;
            for (Employee temp : Employee::LIST)
                if (temp.getId() == id)
                {
                    id_found = true;
                    employee = temp;
                    break;
                }

            if (id_found)
                break;
            else
            {
                utils::showMessage(MESSAGE_TYPE::FAILURE, "\nNo employee found with this ID!");

                // try again
                std::cout << "\n\nDo you want to try again [y/n]? ";
                std::getline(std::cin, choice);

                if (choice != "Y" && choice != "y")
                    return;

                continue;
            }

            std::cout << "\nID found :: " << std::boolalpha << id_found;

            utils::pauseScreen();
        }
        catch (const std::invalid_argument &e)
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid input!");

            std::cout << "\n\nDo you want to try again [y/n]? ";
            std::getline(std::cin, choice);

            if (choice != "Y" && choice != "y")
                return;

            continue;
        }
    }

    // update logics starts from here
    utils::header("UPDATE EMPLOYEE DETAILS");

    // initial details
    std::cout << "INITIAL DETAILS";
    std::cout << "\n\nUsername       :: " << employee.getUsername();
    std::cout << "\nPassword       :: " << employee.getPassword();
    std::cout << "\nName           :: " << employee.getName();
    std::cout << "\nContact Number :: " << employee.getContactNumber();
    std::cout << "\nAdded on       :: " << utils::getDateString(employee.getAddedDate(), false);
    std::cout << "\nRemoved on     :: " << utils::getDateString(employee.getLastModified(), false);
    std::cout << "\nLast modified  :: " << utils::getDateString(employee.getRemovedDate(), false);
    std::cout << "\nStatus         :: " << employee.getStatusString();

    std::cout << "\n\nYou can press enter if you don't want to update the specific details...";

    // get new details
    bool valid_username;
    bool detail_modified = false;
    std::string username, password, name, contact_number;

    // gettting username
    while (true)
    {
        valid_username = true;

        std::cout << "\n\nUsername       :: ";
        std::getline(std::cin, username);

        if (username.empty())
            break;

        for (Employee temp : Employee::LIST)
        {
            if (temp.getUsername() == username)
            {
                valid_username = false;
                break;
            }
        }

        if (valid_username)
        {
            employee.setUsername(username);
            detail_modified = true;
            break;
        }
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nThis username is already taken!");

            std::cout << "\n\nDo you want to try again [y/n]? ";
            std::getline(std::cin, choice);

            if (choice != "Y" && choice != "y")
                return;
        }
    }

    // getting password
    std::cout << "\nPassword       :: ";
    std::getline(std::cin, password);

    if (!password.empty())
    {
        employee.setPassword(password);
        detail_modified = true;
    }

    // getting first name
    std::cout << "\nName           :: ";
    std::getline(std::cin, name);

    if (!name.empty())
    {
        employee.setName(name);
        detail_modified = true;
    }

    // getting contact number
    std::cout << "\nContact number :: ";
    std::getline(std::cin, contact_number);

    if (!contact_number.empty())
    {
        employee.setContactNumber(contact_number);
        detail_modified = true;
    }

    if (!detail_modified)
    {
        utils::showMessage(MESSAGE_TYPE::INFO, "\nNothing to update!");
        std::cout << "\n\nPress any key to go back...";
        utils::pauseScreen();
        return;
    }

    // display new details
    utils::header("UPDATE EMPLOYEE DETAILS");
    std::cout << "NEW DETAILS";
    std::cout << "\n\nUsername       :: " << employee.getUsername();
    std::cout << "\nPassword       :: " << employee.getPassword();
    std::cout << "\nName           :: " << employee.getName();
    std::cout << "\nContact Number :: " << employee.getContactNumber();

    std::cout << "\n\nAre your sure you want to update [y/n]? ";
    std::getline(std::cin, choice);

    if (choice != "Y" && choice != "y")
    {
        utils::showMessage(MESSAGE_TYPE::INFO, "\nEmployee updation cancelled!");
        std::cout << "\n\nPress any key to continue...";
        utils::pauseScreen();
        return;
    }

    employee.setModifiedDate(utils::getCurrentDateTime()); // update modified date

    bool response = employee.update();

    if (response)
    {
        // background :: fetch employees
        std::thread fetch_employees_thread(Employee::fetchAll);
        fetch_employees_thread.detach();

        utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nEmployee updated successfully!");
    }
    else
        utils::showMessage(MESSAGE_TYPE::FAILURE, "\nEmployee updation failed!");

    std::cout << "\n\nPress any key to continue...";
    utils::pauseScreen();
}

// employee :: remove employee
void employee_view::remove()
{
    int id;
    bool id_found, valid_id, already_removed;
    std::string id_str, choice;
    Employee employee;

    while (true)
    {
        valid_id = false;
        id_found = false;
        already_removed = false;

        utils::header("REMOVE EMPLOYEE");

        std::cout << "Enter employee ID to remove :: ";
        std::getline(std::cin, id_str);

        // employee id validity test
        try
        {
            id = std::stoi(id_str);
            valid_id = true;
        }
        catch (const std::invalid_argument &e)
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid input!");
        }

        if (valid_id) // valid employee id
        {
            // check the presence of id
            for (Employee temp : Employee::LIST)
            {
                if (temp.getId() == id)
                {
                    employee = temp;

                    id_found = true;

                    if (temp.getStatus() == EMPLOYEE_STATUS::INACTIVE)
                        already_removed = true;

                    break;
                }
            }

            if (!id_found)
                utils::showMessage(MESSAGE_TYPE::INFO, "\nEmployee with this ID not found!");
            else
            {
                // preview employee details
                std::cout << "\nEMPLOYEE DETAILS";
                std::cout << "\n\nUsername        :: " << employee.getUsername();
                std::cout << "\nName            :: " << employee.getName();
                std::cout << "\nContact Number  :: " << employee.getContactNumber();
                std::cout << "\nAdded On        :: " << utils::getDateString(employee.getAddedDate(), false);
                std::cout << "\nRemoved On      :: " << utils::getDateString(employee.getRemovedDate(), false);
                std::cout << "\nLast Modified   :: " << utils::getDateString(employee.getLastModified(), false);
                std::cout << "\nStatus          :: " << employee.getStatusString();

                // check if employee is already removed
                if (already_removed)
                    utils::showMessage(MESSAGE_TYPE::INFO, "\n\nThis employee is already removed!");
                else
                {
                    std::cout << "\n\nAre you sure you want to remove this employee [y/n]? ";
                    std::getline(std::cin, choice);

                    if (choice != "y" && choice != "Y")
                        utils::showMessage(MESSAGE_TYPE::INFO, "\nEmployee removal cancelled!");
                    else
                    {
                        // remove employee
                        if (employee_utility::remove(id))
                        {
                            utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nEmployee removed successfully!");

                            // background :: update employee list
                            std::thread fetch_employees_thread(Employee::fetchAll);
                            fetch_employees_thread.detach();
                        }
                        else
                            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nCouldn't remove employee!");
                    }
                }
            }
        }

        std::cout << "\n\nDo you want to remove another employee [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "Y")
            return;
    }
}

#endif