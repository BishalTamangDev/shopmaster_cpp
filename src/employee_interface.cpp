// include header file
#include "../include/employee_interface.h"

// admin menu
void employee_interface::adminMenu()
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
        utility::header("EMPLOYEE view MENU");

        for (const auto &options : options)
            utility::showOption(options.first, options.second);

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
            employee_interface::viewAll(); // view employees
        else if (choice == "2")
            employee_interface::searchById(); // search employee by id
        else if (choice == "3")
            employee_interface::searchByUsername(); // search employee by username
        else if (choice == "4")
            employee_interface::add(); // add employee
        else if (choice == "5")
            employee_interface::update(); // update
        else if (choice == "6")
            employee_interface::remove(); // remove employee
        else if (choice == "7")
            return;
        else
        {
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            utility::pauseScreen();
        }
    }
}

// employee :: show details
void employee_interface::showDetails(int current_employee_id)
{
    Employee employee;

    EmployeeManager employeeManager;

    bool response = employeeManager.fetch(current_employee_id, employee);

    utility::header("MY ACCOUNT DETAILS");

    if (!response)
        utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "Couldn't fetch employee details!");
    else
        employee.show(false);

    std::cout << "\n\nPress any key to continue...";

    utility::pauseScreen();
}

// login
bool employee_interface::login(int &current_employee_id)
{
    Employee employee;
    EmployeeManager employeeManager;

    int chance = 3;
    bool status = false;

    std::string choice, username, password;

    while (true)
    {
        chance--;

        utility::header("EMPLOYEE LOGIN");

        std::cout << "Username :: ";
        std::getline(std::cin, username);

        std::cout << "\nPassword :: ";
        std::getline(std::cin, password);

        if (employeeManager.login(username, password, current_employee_id))
        {
            status = true;
            break;
        }

        utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid username or password!");

        if (chance == 0)
        {
            utility::showMessage(utility::MESSAGE_TYPE::INFO, "\n\nYou entered your credentials 3 times incorrectly!");

            std::cout << "\n\nExiting the program...";

            std::this_thread::sleep_for(std::chrono::seconds(1));

            exit(0);
        }
        else
        {
            std::cout << "\n\nDo you want to try again [y/n]? ";
            std::getline(std::cin, choice);

            if (choice != "Y" && choice != "y")
            {
                std::cout << "\nExiting program...\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                exit(0);
            }
        }
    }

    return status;
}

// employee :: view all employees
void employee_interface::viewAll()
{
    utility::header("VIEW ALL EMPLOYEES");

    std::vector<Employee> employees = EmployeeManager::fetchAllEmployees();

    if (employees.size() == 0)
    {
        utility::showMessage(utility::MESSAGE_TYPE::INFO, "No employees found!");
        std::cout << "\n\nPress any key to go back...";
        utility::pauseScreen();
        return;
    }

    std::vector<int> spaces = {7, 22, 13, 12, 13, 12, 12, 16, 9};
    utility::showLine(spaces, {"ID", "Name", "Username", "Password", "Contact No.", "Added On", "Removed On", "Last Modified", "Status"});

    for (Employee &employee : employees)
        utility::showLine(spaces, {std::to_string(employee.getId()), employee.getName(), employee.getUsername(), employee.getPassword(), employee.getContactNumber(), utility::getDateString(employee.getAddedDate(), false), utility::getDateString(employee.getRemovedDate(), false), utility::getDateString(employee.getLastModified(), false), employee.getStatusString()});

    std::cout << "\nPress any key to continue...";
    utility::pauseScreen();
}

// employee :: search employee by id
void employee_interface::searchById()
{
    int id;
    bool found = false;
    std::string id_str, choice;

    std::vector<Employee> employees;

    while (true)
    {
        found = false;

        employees = EmployeeManager::fetchAllEmployees(); // fetch all employees

        utility::header("SEARCH EMPLOYEE BY ID");
        std::cout << "Enter employee ID to search :: ";
        std::getline(std::cin, id_str);

        try
        {
            id = std::stoi(id_str);

            for (Employee employee : employees)
            {
                if (employee.getId() == id)
                {
                    found = true;
                    std::cout << "\n";
                    employee.show(false);
                }
            }

            if (!found)
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nNo employee found with this ID.");
        }
        catch (const std::invalid_argument &e)
        {
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid input!");
        }

        std::cout << "\n\nDo you want to search another employee [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "Y")
            break;
    }
}

// employee :: search employee by username
void employee_interface::searchByUsername()
{
    bool found = false;
    std::string username, choice;
    std::vector<Employee> employees;

    while (true)
    {
        found = false;
        employees = EmployeeManager::fetchAllEmployees(); // fetch all employees

        utility::header("SEARCH EMPLOYEE BY USERNAME");

        std::cout << "Enter username to search :: ";
        std::getline(std::cin, username);

        for (Employee employee : employees)
        {
            if (employee.getUsername() == username)
            {
                found = true;
                std::cout << "\n";
                employee.show(false);
            }
        }

        if (!found)
            utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nNo employee found with this username.");

        std::cout << "\n\nDo you want to search another employee [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "Y")
            break;
    }
}

// employee :: add new employee
void employee_interface::add()
{
    Employee employee;

    bool valid_username;

    std::string choice, username, password, name, contact_number;

    std::vector<Employee> employees;
    EmployeeManager employeeManager;

    while (true)
    {
        valid_username = true;

        employees = EmployeeManager::fetchAllEmployees(); // fetch all employees

        utility::header("ADD NEW EMPLOYEE");
        std::cout << "Username          :: ";
        std::getline(std::cin, username);

        for (Employee temp_employee : employees)
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
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nThis username is already take!");
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
    employee.setAddedDate(utility::getCurrentDateTime());

    // show employee details
    utility::header("ADD NEW EMPLOYEE");
    std::cout << "Username          :: " << employee.getUsername() << "\n";
    std::cout << "Password          :: " << employee.getPassword() << "\n";
    std::cout << "Name              :: " << employee.getName() << "\n";
    std::cout << "Contact Number    :: " << employee.getContactNumber() << "\n";
    std::cout << "Added Date        :: " << utility::getDateString(employee.getAddedDate(), false) << "\n";
    std::cout << "Status            :: " << employee.getStatusString() << "\n";

    // ask user to proceed
    std::cout << "\nAre you sure you want to add [y/n]? ";
    std::getline(std::cin, choice);

    if (choice != "Y" && choice != "y")
        utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nEmployee addition cancelled.");
    else
    {
        if (employeeManager.add(employee))
            utility::showMessage(utility::MESSAGE_TYPE::SUCCESS, "\nEmployee added successfully!");
        else
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nEmployee addition failed!");
    }

    std::cout << "\n\nPress any key to continue...";
    utility::pauseScreen();
}

// employee :: update employee details
void employee_interface::update()
{
    int id;
    bool id_found;
    std::string id_str, choice;
    std::vector<Employee> employees;

    Employee employee;
    EmployeeManager employeeManager;

    while (true)
    {
        employees = EmployeeManager::fetchAllEmployees(); // fetch all employees

        utility::header("UPDATE EMPLOYEE DETAILS");

        std::cout << "Enter employee ID to update :: ";
        std::getline(std::cin, id_str);

        try
        {
            id = std::stoi(id_str);

            // check for id presence
            id_found = false;
            for (Employee temp : employees)
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
                utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nNo employee found with this ID!");

                // try again
                std::cout << "\n\nDo you want to try again [y/n]? ";
                std::getline(std::cin, choice);

                if (choice != "Y" && choice != "y")
                    return;

                continue;
            }

            std::cout << "\nID found :: " << std::boolalpha << id_found;

            utility::pauseScreen();
        }
        catch (const std::invalid_argument &e)
        {
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid input!");

            std::cout << "\n\nDo you want to try again [y/n]? ";
            std::getline(std::cin, choice);

            if (choice != "Y" && choice != "y")
                return;

            continue;
        }
    }

    // update logics starts from here
    utility::header("UPDATE EMPLOYEE DETAILS");

    // initial details
    std::cout << "INITIAL DETAILS";
    std::cout << "\n\nUsername       :: " << employee.getUsername();
    std::cout << "\nPassword       :: " << employee.getPassword();
    std::cout << "\nName           :: " << employee.getName();
    std::cout << "\nContact Number :: " << employee.getContactNumber();
    std::cout << "\nAdded on       :: " << utility::getDateString(employee.getAddedDate(), false);
    std::cout << "\nRemoved on     :: " << utility::getDateString(employee.getLastModified(), false);
    std::cout << "\nLast modified  :: " << utility::getDateString(employee.getRemovedDate(), false);
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

        for (Employee temp : employees)
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
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nThis username is already taken!");

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
        utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nNothing to update!");
        std::cout << "\n\nPress any key to go back...";
        utility::pauseScreen();
        return;
    }

    // display new details
    utility::header("UPDATE EMPLOYEE DETAILS");
    std::cout << "NEW DETAILS";
    std::cout << "\n\nUsername       :: " << employee.getUsername();
    std::cout << "\nPassword       :: " << employee.getPassword();
    std::cout << "\nName           :: " << employee.getName();
    std::cout << "\nContact Number :: " << employee.getContactNumber();

    std::cout << "\n\nAre your sure you want to update [y/n]? ";
    std::getline(std::cin, choice);

    if (choice != "Y" && choice != "y")
    {
        utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nEmployee updation cancelled!");
        std::cout << "\n\nPress any key to continue...";
        utility::pauseScreen();
        return;
    }

    employee.setModifiedDate(utility::getCurrentDateTime()); // update modified date

    bool response = employeeManager.update(employee);

    if (response)
        utility::showMessage(utility::MESSAGE_TYPE::SUCCESS, "\nEmployee updated successfully!");
    else
        utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nEmployee updation failed!");

    std::cout << "\n\nPress any key to continue...";

    utility::pauseScreen();
}

// employee :: remove employee
void employee_interface::remove()
{
    int id;
    bool id_found, valid_id, already_removed;
    std::string id_str, choice;

    Employee employee;
    std::vector<Employee> employees;

    while (true)
    {
        valid_id = false;
        id_found = false;
        already_removed = false;

        employees = EmployeeManager::fetchAllEmployees(); // fetch all employees

        utility::header("REMOVE EMPLOYEE");

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
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nInvalid input!");
        }

        if (valid_id) // valid employee id
        {
            // check the presence of id
            for (Employee temp : employees)
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
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nEmployee with this ID not found!");
            else
            {
                // preview employee details
                std::cout << "\nEMPLOYEE DETAILS";
                std::cout << "\n\nUsername        :: " << employee.getUsername();
                std::cout << "\nName            :: " << employee.getName();
                std::cout << "\nContact Number  :: " << employee.getContactNumber();
                std::cout << "\nAdded On        :: " << utility::getDateString(employee.getAddedDate(), false);
                std::cout << "\nRemoved On      :: " << utility::getDateString(employee.getRemovedDate(), false);
                std::cout << "\nLast Modified   :: " << utility::getDateString(employee.getLastModified(), false);
                std::cout << "\nStatus          :: " << employee.getStatusString();

                // check if employee is already removed
                if (already_removed)
                    utility::showMessage(utility::MESSAGE_TYPE::INFO, "\n\nThis employee is already removed!");
                else
                {
                    std::cout << "\n\nAre you sure you want to remove this employee [y/n]? ";
                    std::getline(std::cin, choice);

                    if (choice != "y" && choice != "Y")
                        utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nEmployee removal cancelled!");
                    else
                    {
                        // remove employee
                        EmployeeManager employeeManager;
                        if (employeeManager.remove(id))
                            utility::showMessage(utility::MESSAGE_TYPE::SUCCESS, "\nEmployee removed successfully!");
                        else
                            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nCouldn't remove employee!");
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