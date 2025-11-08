#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>

// importing user-defined files
#include "utils.h"
#include "file_setup.h"
#include "admin.h"
#include "shop.h"
#include "employee.h"
#include "customer.h"

// namespace :: inventory
namespace ns_inventory
{
    void menu(); // menu
}

// namespace :: employee
namespace ns_employee
{
    void menu();             // menu
    void viewAll();          // view all employees
    void searchById();       // search employee by id
    void searchByUsername(); // search employee by username
    void add();              // add new employee
    void update();           // update employee details
    void remove();           // remove employee
}

// namespace :: customer
namespace ns_customer
{
    void menu();            //  menu
    void viewAll();         // view all customer
    void searchBySalesId(); // search by sales id
    void searchByName();    // search by name
};

// namespace :: admin
namespace ns_admin
{
    void menu();                // menu
    bool registration();        // admin registration
    bool login(Admin &);        // admin login
    void profileMenu();         // profile menu
    void updateUsername(Admin); // update username
    void updatePassword(Admin); // update password
    void updateName(Admin);     // update admin name
};

// namespace :: shop
namespace ns_shop
{
    void menu();               // my shop menu
    bool registration(Shop &); // register shop
    void update(Shop &);       // update shop
}

// main function
int main()
{
    // background process :: file setup
    std::thread file_setup(app_files::setup); // file setup thread
    file_setup.detach();

    // background process :: fetch employees
    std::thread fetch_employees_thread(Employee::fetchAll);
    fetch_employees_thread.detach();

    Admin admin;

    // check if admain has been registered yet
    if (!admin.isRegistered())
    {
        if (ns_admin::registration())
        {
            utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nAdmin been registered successfully. Press any key to login.");
            utils::pauseScreen();
        }
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nAdmin registration failed!");
            utils::pauseScreen();
            exit(1);
        }
    }

    // login
    int chance = 3;

    while (true)
    {
        utils::clearScreen();

        if (ns_admin::login(admin))
        {
            utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nLogin successful!");
            utils::showMessage(MESSAGE_TYPE::INFO, "\n\nRedirecting to main menu...");
            std::this_thread::sleep_for(std::chrono::seconds(1));
            ns_admin::menu();
        }
        else
        {
            chance--;

            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid username or password!");

            if (chance > 0)
            {
                std::string choice;

                std::cout << "\n\nDo you want to try again [y/n]? :: ";
                std::getline(std::cin, choice);

                if (choice != "Y" && choice != "y")
                {
                    utils::showMessage(MESSAGE_TYPE::INFO, "\nExiting program...\n");
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    break;
                }
            }
            else
            {
                utils::showMessage(MESSAGE_TYPE::INFO, "\n\nYou entered your credentials 3 times incorrectly!");
                utils::showMessage(MESSAGE_TYPE::INFO, "\n\nExiting program...\n");
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
            }
        }
    }

    Shop shop;

    if (!shop.isRegistered())
    {
        if (!ns_shop::registration(shop))
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            exit(1);
        }
    }

    return 0;
}

// section :: admin
void ns_admin::menu()
{
    std::string choice;

    std::map<int, std::string> options = {
        {1, "Inventory Management"},
        {2, "Employee Management"},
        {3, "Customer Management"},
        {4, "My Profile"},
        {5, "My Shop"},
        {6, "Exit"},
    };

    while (true)
    {
        utils::clearScreen();

        utils::header("ADMIN MENU");

        for (const auto &option : options)
            utils::showOption(option.first, option.second);

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
            ns_inventory::menu();
        else if (choice == "2")
            ns_employee::menu();
        else if (choice == "3")
            ns_customer::menu();
        else if (choice == "4")
            ns_admin::profileMenu();
        else if (choice == "5")
            ns_shop::menu();
        else if (choice == "6")
        {
            utils::showMessage(MESSAGE_TYPE::INFO, "\nExiting program...\n");
            std::this_thread::sleep_for(std::chrono::seconds(1));
            exit(0);
        }
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid choice! Press any key to try again.");
            utils::pauseScreen();
        }
    }
}

// admin :: profile menu
void ns_admin::profileMenu()
{
    bool response;

    Admin admin;

    while (true)
    {
        utils::header("MY PROFILE");

        response = admin.fetch(); // fetch admin details

        if (!response)
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "Could not fetch admin details!");
            utils::showMessage(MESSAGE_TYPE::INFO, "\n\nPress any key to go back...");
            utils::pauseScreen();
            return;
        }

        // show details
        std::cout << "Username :: " << admin.getUsername() << "\n";
        std::cout << "Name     :: " << admin.getFullName() << "\n\n";

        // options
        std::map<int, std::string> options = {
            {1, "Update Username"},
            {2, "Update Password"},
            {3, "Update Name"},
            {4, "Go Back"},
        };

        for (const auto &option : options)
            utils::showOption(option.first, option.second);

        std::string choice;

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
            updateUsername(admin);
        else if (choice == "2")
            updatePassword(admin);
        else if (choice == "3")
            updateName(admin);
        else if (choice == "4")
            break;
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\n\nInvalid choice!");
            utils::pauseScreen();
        }
    }
}

// admin :: registration
bool ns_admin::registration()
{
    Admin admin;

    std::string username, password, first_name, middle_name, last_name;

    utils::header("ADMIN REGISTRATION");

    utils::showMessage(MESSAGE_TYPE::INFO, "Admin has not been registered yet!");

    std::cout << "\n\nUsername :: ";
    std::getline(std::cin, username);
    admin.setUsername(username);

    std::cout << "\nPassword :: ";
    std::getline(std::cin, password);
    admin.setPassword(password);

    std::cout << "\nFirst name :: ";
    std::getline(std::cin, first_name);
    admin.setFirstName(first_name);

    std::cout << "\nMiddle name [Press enter if you don't have a middle name] :: ";
    std::getline(std::cin, middle_name);
    admin.setMiddleName(middle_name);

    std::cout << "\nLast name :: ";
    std::getline(std::cin, last_name);
    admin.setLastName(last_name);

    // show admin details
    utils::header("ADMIN REGISTRATION DETAILS");
    std::cout << "Username    :: " << admin.getUsername() << "\n\n";
    std::cout << "Password    :: " << admin.getPassword() << "\n\n";
    std::cout << "Name        :: " << admin.getFullName() << "\n";

    return admin.registerAdmin();
}

// admin :: login
bool ns_admin::login(Admin &admin)
{
    std::string username, password;

    utils::header("ADMIN LOGIN");

    std::cout << "Username :: ";
    std::getline(std::cin, username);

    std::cout << "\nPassword :: ";
    std::getline(std::cin, password);

    return admin.login(username, password);
}

// admin :: update username
void ns_admin::updateUsername(Admin admin)
{
    std::string choice;
    std::string new_username;

    while (true)
    {
        utils::clearScreen();

        utils::header("UPDATE USERNAME");

        std::cout << "Old username       :: " << admin.getUsername() << "\n\n";

        std::cout << "Enter new username :: ";
        std::getline(std::cin, new_username);

        if (new_username == admin.getUsername())
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nYou entered old username!");

            std::cout << "\n\nDo you want to try again [y/n]? ";
            std::getline(std::cin, choice);

            if (choice != "Y" && choice != "y")
                break;
            else
                continue;
        }

        std::cout << "\nNew username       :: " << new_username;

        admin.setUsername(new_username); // set new username

        // proceed update
        if (admin.update())
            utils::showMessage(MESSAGE_TYPE::SUCCESS, "\n\nUsername updated successfully!");
        else
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\n\nUsername updation failed!");

        utils::showMessage(MESSAGE_TYPE::INFO, "\n\nPress any key to continue...");

        utils::pauseScreen();

        break;
    }
}

// admin :: update password
void ns_admin::updatePassword(Admin admin)
{
    std::string choice;
    std::string old_password, new_password, new_password_confirmation;

    while (true)
    {
        utils::clearScreen();

        utils::header("UPDATE PASSWORD");

        // get old password
        std::cout << "Enter old password :: ";
        std::getline(std::cin, old_password);

        if (old_password != admin.getPassword())
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid password!");

            std::cout << "\n\nDo you want to try again [y/n]? ";
            std::getline(std::cin, choice);

            if (choice != "Y" && choice != "y")
                break;
            else
                continue;
        }

        std::cout << "\nEnter new password :: ";
        std::getline(std::cin, new_password);

        if (new_password == admin.getPassword())
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nYou entered old password!");
            std::cout << "\n\nPress any key to go back...";
            utils::pauseScreen();
            break;
        }

        std::cout << "\nEnter again for confirmation :: ";
        std::getline(std::cin, new_password_confirmation);

        if (new_password != new_password_confirmation)
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nPassword confirmation failed!");
            std::cout << "\n\nPress any key to go back...";
            utils::pauseScreen();
            break;
        }

        admin.setPassword(new_password); // set new password

        // proceed update
        if (admin.update())
            utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nPassword updated successfully!");
        else
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nPassword updation failed!");

        utils::showMessage(MESSAGE_TYPE::INFO, "\n\nPress any key to continue...");

        utils::pauseScreen();

        break;
    }
}

// admin :: update name
void ns_admin::updateName(Admin admin)
{
    utils::clearScreen();
    utils::header("UPDATE NAME");
    std::string first_name, middle_name, last_name;

    std::cout << "Old name :: " << admin.getFullName();

    std::cout << "\n\nFirst name :: ";
    std::getline(std::cin, first_name);
    admin.setFirstName(first_name);

    std::cout << "\nMiddle name [Press enter if you don't have a middle name] :: ";
    std::getline(std::cin, middle_name);
    admin.setMiddleName(middle_name);

    std::cout << "\nLast name :: ";
    std::getline(std::cin, last_name);
    admin.setLastName(last_name);

    std::cout << "\nNew name :: " << admin.getFullName();

    if (admin.update())
        utils::showMessage(MESSAGE_TYPE::SUCCESS, "\n\nName updated successfully!");
    else
        utils::showMessage(MESSAGE_TYPE::FAILURE, "\n\nName updation failed!");

    utils::showMessage(MESSAGE_TYPE::INFO, "\n\nPress any key to continue...");

    utils::pauseScreen();
}

// section :: inventory
// inventory :: menu
void ns_inventory::menu()
{
    utils::header("INVENTORY MANAGEMENT MENU");
    utils::pauseScreen();
}

// section :: employee
// employee :: menu
void ns_employee::menu()
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
        utils::header("EMPLOYEE MANAGEMENT MENU");

        for (const auto &options : options)
            utils::showOption(options.first, options.second);

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
            ns_employee::viewAll(); // view employees
        else if (choice == "2")
            ns_employee::searchById(); // search employee by id
        else if (choice == "3")
            ns_employee::searchByUsername(); // search employee by username
        else if (choice == "4")
            ns_employee::add(); // add employee
        else if (choice == "5")
            ns_employee::update(); // update
        else if (choice == "6")
            ns_employee::remove(); // remove employee
        else if (choice == "7")
            return;
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            utils::pauseScreen();
        }
    }
}

// employee :: view all employees
void ns_employee::viewAll()
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
        utils::showLine(spaces, {std::to_string(employee.getId()), employee.getFullName(), employee.getUsername(), employee.getPassword(), employee.getContactNumber(), utils::getDateString(employee.getAddedDate(), false), utils::getDateString(employee.getRemovedDate(), false), utils::getDateString(employee.getModifiedDate(), false), employee.getStatusString()});

    std::cout << "\nPress any key to continue...";
    utils::pauseScreen();
}

// employee :: search employee by id
void ns_employee::searchById()
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
                    std::cout << "\nUsername       :: " << employee.getUsername();
                    std::cout << "\nPassword       :: " << employee.getPassword();
                    std::cout << "\nName           :: " << employee.getFullName();
                    std::cout << "\nContact Number :: " << employee.getContactNumber();
                    std::cout << "\nAdded Date     :: " << utils::getDateString(employee.getAddedDate(), false);
                    std::cout << "\nRemoved Date   :: " << utils::getDateString(employee.getRemovedDate(), false);
                    std::cout << "\nModified Date  :: " << utils::getDateString(employee.getModifiedDate(), false);
                    std::cout << "\nStatus         :: " << employee.getStatusString();
                }
            }

            if (!found)
                utils::showMessage(MESSAGE_TYPE::INFO, "\nNo employee found with this ID.");
        }
        catch (const std::invalid_argument &e)
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nPlease enter number input!");
        }

        std::cout << "\n\nDo you want to search another employee [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "Y")
            break;
    }
}

// employee :: search employee by username
void ns_employee::searchByUsername()
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
                std::cout << "\nUsername       :: " << employee.getUsername();
                std::cout << "\nPassword       :: " << employee.getPassword();
                std::cout << "\nName           :: " << employee.getFullName();
                std::cout << "\nContact Number :: " << employee.getContactNumber();
                std::cout << "\nAdded Date     :: " << utils::getDateString(employee.getAddedDate(), false);
                std::cout << "\nRemoved Date   :: " << utils::getDateString(employee.getRemovedDate(), false);
                std::cout << "\nModified Date  :: " << utils::getDateString(employee.getModifiedDate(), false);
                std::cout << "\nStatus         :: " << employee.getStatusString();
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
void ns_employee::add()
{
    Employee employee;

    bool valid_username;
    std::string choice;
    std::string username, password;
    std::string first_name, middle_name, last_name;
    std::string contact_number;

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

    std::cout << "\nFirst Name        :: ";
    std::getline(std::cin, first_name);
    employee.setFirstName(first_name);

    std::cout << "\nMiddle Name [Press enter if not available]    :: ";
    std::getline(std::cin, middle_name);
    employee.setMiddleName(middle_name);

    std::cout << "\nLast Name         :: ";
    std::getline(std::cin, last_name);
    employee.setLastName(last_name);

    std::cout << "\nContact Number    :: ";
    std::getline(std::cin, contact_number);
    employee.setContactNumber(contact_number);

    employee.setStatus(EMPLOYEE_STATUS::ACTIVE);
    employee.setAddedDate(utils::getCurrentDateTime());

    // show employee details
    utils::header("ADD NEW EMPLOYEE");
    std::cout << "Username          :: " << employee.getUsername() << "\n";
    std::cout << "Password          :: " << employee.getPassword() << "\n";
    std::cout << "Name              :: " << employee.getFullName() << "\n";
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
void ns_employee::update()
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
    std::cout << "\nName           :: " << employee.getFullName();
    std::cout << "\nContact Number :: " << employee.getContactNumber();
    std::cout << "\nAdded on       :: " << utils::getDateString(employee.getAddedDate(), false);
    std::cout << "\nRemoved on     :: " << utils::getDateString(employee.getModifiedDate(), false);
    std::cout << "\nLast modified  :: " << utils::getDateString(employee.getRemovedDate(), false);
    std::cout << "\nStatus         :: " << employee.getStatusString();

    std::cout << "\n\nYou can press enter if you don't want to update the specific details...";

    // get new details
    bool valid_username;
    bool detail_modified = false;
    std::string username, password, first_name, middle_name, last_name, contact_number;

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
    std::cout << "\nFirst name     :: ";
    std::getline(std::cin, first_name);

    if (!first_name.empty())
    {
        employee.setFirstName(first_name);
        detail_modified = true;
    }

    // getting middle name
    std::cout << "\nMiddle name    :: ";
    std::getline(std::cin, middle_name);

    if (!middle_name.empty())
    {
        employee.setMiddleName(middle_name);
        detail_modified = true;
    }

    // getting last name
    std::cout << "\nLast name      :: ";
    std::getline(std::cin, last_name);

    if (!last_name.empty())
    {
        employee.setLastName(last_name);
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
    std::cout << "\nName           :: " << employee.getFullName();
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
void ns_employee::remove()
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
            {
                utils::showMessage(MESSAGE_TYPE::INFO, "\nEmployee with this ID not found!");
            }
            else
            {
                // preview employee details
                std::cout << "\nEMPLOYEE DETAILS";
                std::cout << "\n\nUsername        :: " << employee.getUsername();
                std::cout << "\nName            :: " << employee.getFullName();
                std::cout << "\nContact Number  :: " << employee.getContactNumber();
                std::cout << "\nAdded On        :: " << utils::getDateString(employee.getAddedDate(), false);
                std::cout << "\nRemoved On      :: " << utils::getDateString(employee.getRemovedDate(), false);
                std::cout << "\nLast Modified   :: " << utils::getDateString(employee.getModifiedDate(), false);
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
                        if (Employee::remove(id))
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

// section :: customer
// customer :: menu
void ns_customer::menu()
{
    std::string choice;

    const std::map<int, std::string> options = {
        {1, "View Customer"},
        {2, "Search Customer by Sales ID"},
        {3, "Search Customer by Name"},
        {4, "Go Back"},
    };

    while (true)
    {
        utils::header("CUSTOMER MANAGEMENT MENU");

        for (const auto &option : options)
            utils::showOption(option.first, option.second);

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
            ns_customer::viewAll();
        else if (choice == "2")
            ns_customer::searchBySalesId();
        else if (choice == "3")
            ns_customer::searchByName();
        else if (choice == "4")
            return;
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            utils::pauseScreen();
        }
    }
}

// view all customer
void ns_customer::viewAll()
{
    utils::header("ALL CUSTOMERS");

    std::vector<Customer> customers = Customer::fetchAll();

    if (customers.size() == 0)
        utils::showMessage(MESSAGE_TYPE::INFO, "No customers found!");
    else
    {
        utils::showLine({11, 25}, {"Sales ID", "Name"});
        for (Customer customer : customers)
            utils::showLine({11, 25}, {std::to_string(customer.getSalesId()), customer.getName()});
    }

    std::cout << "\nPress any key to continue...";
    utils::pauseScreen();
}

// search by sales id
void ns_customer::searchBySalesId()
{
    int sales_id;
    bool found, valid_id;
    std::string sales_id_str, choice;

    std::vector<Customer> customers = Customer::fetchAll();

    while (true)
    {
        found = false;
        valid_id = true;

        utils::header("SEARCH CUSTOMER BY SALES ID");

        if (customers.size() == 0)
        {
            utils::showMessage(MESSAGE_TYPE::INFO, "No customers found!");
            break;
        }

        std::cout << "Enter sales ID to search :: ";
        std::getline(std::cin, sales_id_str);

        try
        {
            sales_id = std::stoi(sales_id_str);
        }
        catch (const std::invalid_argument &e)
        {
            valid_id = false;
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid input");
        }

        if (valid_id) // search
        {
            for (Customer customer : customers)
            {
                if (customer.getSalesId() == sales_id)
                {
                    found = true;
                    utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nCustomer found!");
                    std::cout << "\n\nSales ID     :: " << sales_id;
                    std::cout << "\n\nName         :: " << customer.getName();
                    break;
                }
            }

            if (!found)
                utils::showMessage(MESSAGE_TYPE::INFO, "\nCustomer not found!");
        }

        std::cout << "\n\nDo you want to search another customer [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "Y")
            break;
    }
}

// search by name
void ns_customer::searchByName()
{
    bool found;
    std::string name, target_name, choice;

    std::vector<Customer> customers = Customer::fetchAll();

    while (true)
    {
        found = false;

        utils::header("SEARCH CUSTOMER BY NAME");

        if (customers.size() == 0)
        {
            utils::showMessage(MESSAGE_TYPE::INFO, "No customers found!\n");
            break;
        }

        std::cout << "Enter customer name to search :: ";
        std::getline(std::cin, target_name);

        std::cout << "\n";
        utils::showLine({11, 25}, {"Sales ID", "Name"});

        for (Customer &customer : customers)
        {
            name = customer.getName();
            utils::convertToLowerCase(name);
            utils::convertToLowerCase(target_name);

            if (name.find(target_name) != std::string::npos)
            {
                found = true;
                utils::showLine({11, 25}, {std::to_string(customer.getSalesId()), customer.getName()});
            }
        }

        if (!found)
            utils::showMessage(MESSAGE_TYPE::INFO, "\nCustomer not found!\n");

        std::cout << "\nDo you want to search another customer [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "y" && choice != "Y")
            break;
    }
}

// section :: shop
// shop :: menu
void ns_shop::menu()
{
    Shop shop;
    bool response;
    std::string choice;

    std::map<int, std::string> options = {
        {1, "Update"},
        {2, "Go Back"},
    };

    while (true)
    {
        response = shop.fetch(); // fetch shop details

        utils::header("MY SHOP");

        if (!response)
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "Couldn't fetch shop details!");
            utils::showMessage(MESSAGE_TYPE::INFO, "\n\nPress any key to go back...");
            utils::pauseScreen();
            return;
        }

        std::cout << "Name            :: " << shop.getName() << "\n";
        std::cout << "PAN             :: " << shop.getPan() << "\n";
        std::cout << "Contact Number  :: " << shop.getContactNumber() << "\n";
        std::cout << "Currency        :: " << shop.getCurrency() << "\n";
        std::cout << "Address         :: " << shop.getAddress() << "\n\n";

        for (const auto &option : options)
            utils::showOption(option.first, option.second);

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
            ns_shop::update(shop);
        else if (choice == "2")
            return;
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            utils::pauseScreen();
        }
    }
}

// shop :: registration
bool ns_shop::registration(Shop &shop)
{
    bool status = false;

    int ward;
    std::string name, pan, contact_number, currency, district, municipality, tole_village;

    while (true)
    {
        utils::clearScreen();
        utils::header("SHOP REGISTRATION");
        utils::showMessage(MESSAGE_TYPE::INFO, "Shop has not been registered yet!");

        std::cout << "\n\nName                   :: ";
        std::getline(std::cin, name);
        shop.setName(name);

        std::cout << "\nPAN                    :: ";
        std::getline(std::cin, pan);
        shop.setPan(pan);

        std::cout << "\nContact Number         :: ";
        std::getline(std::cin, contact_number);
        shop.setContactNumber(contact_number);

        std::cout << "\nCurrency               :: ";
        std::getline(std::cin, currency);
        shop.setCurrency(currency);

        std::cout << "\nAddress (District)     :: ";
        std::getline(std::cin, district);

        std::cout << "\nAddress (Municipality) :: ";
        std::getline(std::cin, municipality);

        std::cout << "\nAddress (Tole/Village) :: ";
        std::getline(std::cin, tole_village);

        while (true)
        {
            std::cout << "\nAddress (Ward)         :: ";
            std::cin >> ward;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid input!\n");
            }
            else
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clean up leftover newline
                break;                                                              // valid input, exit loop
            }
        }

        shop.setAddress(district, municipality, tole_village, ward);

        // show shop details
        utils::header("SHOP REGISTRATION");
        std::cout << "SHOP DETAILS\n\n";

        std::cout << "Name           :: " << shop.getName() << "\n";
        std::cout << "PAN            :: " << shop.getPan() << "\n";
        std::cout << "Contact Number :: " << shop.getContactNumber() << "\n";
        std::cout << "Currency       :: " << shop.getCurrency() << "\n";
        std::cout << "Address        :: " << shop.getAddress() << "\n";

        status = shop.registerShop();

        if (status)
        {
            utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nShop registered successfully!");
            break;
        }
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nShop registration failed!");

            std::string choice;

            std::cout << "Do you want to try again [y/n]?";
            std::getline(std::cin, choice);

            if (choice != "Y" && choice != "y")
                break;
        }

        utils::pauseScreen();
    }

    return status;
}

// shop :: update
void ns_shop::update(Shop &shop)
{
    int ward;
    bool details_changed = false;
    std::string choice;
    std::string name, pan, contact_number, currency, district, municipality, tole_village, ward_str;

    utils::header("UPDATE SHOP DETAILS");

    utils::showMessage(MESSAGE_TYPE::INFO, "You can press enter key to skip the detail that you don't want to update.");

    // get new details
    std::cout << "\n\nName                   :: ";
    std::getline(std::cin, name);

    std::cout << "\nPAN                    :: ";
    std::getline(std::cin, pan);

    std::cout << "\nContact Number         :: ";
    std::getline(std::cin, contact_number);

    std::cout << "\nCurrency               :: ";
    std::getline(std::cin, currency);

    std::cout << "\nAddress (District)     :: ";
    std::getline(std::cin, district);

    std::cout << "\nAddress (Municipality) :: ";
    std::getline(std::cin, municipality);

    std::cout << "\nAddress (Tole/Village) :: ";
    std::getline(std::cin, tole_village);

    std::cout << "\nAddress (Ward)         :: ";
    std::getline(std::cin, ward_str);

    // change only the intended data
    if (name != "" && name != shop.getName())
    {
        shop.setName(name);
        details_changed = true;
    }

    if (pan != "" && pan != shop.getPan())
    {
        details_changed = true;
        shop.setPan(pan);
    }

    if (contact_number != "" && contact_number != shop.getContactNumber())
    {
        details_changed = true;
        shop.setContactNumber(contact_number);
    }

    if (currency != "" && currency != shop.getCurrency())
    {
        details_changed = true;
        shop.setCurrency(currency);
    }

    if (district != "" && district != shop.getDistrict())
    {
        details_changed = true;
        shop.setDistrict(district);
    }

    if (municipality != "" && municipality != shop.getMunicipality())
    {
        details_changed = true;
        shop.setMunicipality(municipality);
    }

    if (tole_village != "" && tole_village != shop.getToleVillage())
    {
        details_changed = true;
        shop.setToleVillage(tole_village);
    }

    if (!ward_str.empty())
    {
        try
        {
            ward = std::stoi(ward_str);

            if (ward != shop.getWard())
            {
                details_changed = true;
                shop.setWard(ward);
            }
        }
        catch (const std::invalid_argument &e)
        {
#ifdef DEBUG_MODE
            std::cerr << "\nError: " << e.what() << "\n";
#endif
        }
        catch (const std::out_of_range &e)
        {
#ifdef DEBUG_MODE
            std::cerr << "\nError: " << e.what() << "\n";
#endif
        }
    }

    if (!details_changed)
    {
        utils::showMessage(MESSAGE_TYPE::INFO, "\nNothing to update...");
        std::cout << "\n\nPress any key to go back...";
        utils::pauseScreen();
        return;
    }

    // show new details
    utils::header("UPDATE SHOP DETAILS :: NEW DETAILS");
    std::cout << "Name           :: " << shop.getName() << "\n";
    std::cout << "PAN            :: " << shop.getPan() << "\n";
    std::cout << "Currency       :: " << shop.getCurrency() << "\n";
    std::cout << "Contact Number :: " << shop.getContactNumber() << "\n";
    std::cout << "Address        :: " << shop.getAddress() << "\n";

    std::cout << "\nAre you sure you want to update [y/n]? ";
    std::getline(std::cin, choice);

    if (choice != "Y" || choice != "y")
    {
        utils::showMessage(MESSAGE_TYPE::INFO, "\nShop details updation cancelled.");
        std::cout << "\n\nPress any key to go back...";
        utils::pauseScreen();
        return;
    }

    // update details
    if (shop.update())
        utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nShop updated successfully!");
    else
        utils::showMessage(MESSAGE_TYPE::FAILURE, "\nShop updation failed!");

    std::cout << "\n\nPress any key to continue...";
    utils::pauseScreen();
}