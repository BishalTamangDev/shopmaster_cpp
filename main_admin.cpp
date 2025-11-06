#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>

// importing user-defined files
#include "utils.h"
#include "file_setup.h"
#include "admin.h"
#include "shop.h"

// function declarations
void menu(); // main menu

// section :: inventory
void inventoryManagementMenu(); // inventory management menu

// section :: employee
void employeeManagementMenu(); // employee management menu

// section :: customer
void customerManagementMenu(); // customer management menu

// section :: admin profile
void myProfileMenu();       // my profile menu
bool adminRegistration();   // admin registration
bool adminLogin(Admin &);   // admin login
void updateUsername(Admin); // update username
void updatePassword(Admin); // update password
void updateName(Admin);     // update admin name

// section :: shop
void myShopMenu();             // my shop menu
bool shopRegistration(Shop &); // register shop
void updateShop(Shop &);       // update shop

// main
int main()
{
    myShopMenu(); // temporary
    return 0;     // temporary

    std::thread file_setup(app_files::setup); // file setup thread
    file_setup.detach();                      // run file setup task in the background independently

    Admin admin;

    // check if admain has been registered yet
    if (!admin.isRegistered())
    {
        if (adminRegistration())
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

        if (adminLogin(admin))
        {
            utils::showMessage(MESSAGE_TYPE::SUCCESS, "\nLogin successful!");
            utils::showMessage(MESSAGE_TYPE::INFO, "\n\nRedirecting to main menu...");
            std::this_thread::sleep_for(std::chrono::seconds(1));
            menu();
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
        if (!shopRegistration(shop))
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            exit(1);
        }
    }

    return 0;
}

// menu
void menu()
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
            inventoryManagementMenu();
        else if (choice == "2")
            employeeManagementMenu();
        else if (choice == "3")
            customerManagementMenu();
        else if (choice == "4")
            myProfileMenu();
        else if (choice == "5")
            myShopMenu();
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

// section :: inventory
// inventory management menu
void inventoryManagementMenu() {}

// section :: employee
// employee management menu
void employeeManagementMenu() {}

// section :: customer
// customer management menu
void customerManagementMenu() {}

// section :: admin profile
// admin registration
bool adminRegistration()
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

// admin login
bool adminLogin(Admin &admin)
{
    std::string username, password;

    utils::header("ADMIN LOGIN");

    std::cout << "Username :: ";
    std::getline(std::cin, username);

    std::cout << "\nPassword :: ";
    std::getline(std::cin, password);

    return admin.login(username, password);
}

// my profile menu
void myProfileMenu()
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

// update username
void updateUsername(Admin admin)
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

// update password
void updatePassword(Admin admin)
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

// update name
void updateName(Admin admin)
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

// section :: sop
// my shop menu
void myShopMenu()
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
            utils::showMessage(MESSAGE_TYPE::FAILURE, "Could not fetch shop details!");
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
            updateShop(shop);
        else if (choice == "2")
            return;
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            utils::pauseScreen();
        }
    }
}

// register shop
bool shopRegistration(Shop &shop)
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

// update shop
void updateShop(Shop &shop)
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
