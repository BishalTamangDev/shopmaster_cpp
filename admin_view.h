#include <iostream>

// import user-defined header files
#include "admin_class.h"
#include "admin_utility.h"

#ifndef SHOPMASTER_ADMIN_VIEW_H
#define SHOPMASTER_ADMIN_VIEW_H

namespace admin_view
{
    bool registration();        // admin registration
    bool login();               // admin login
    void profileMenu();         // profile menu
    void updateUsername(Admin); // update username
    void updatePassword(Admin); // update password
    void updateName(Admin);     // update admin name
}

// profile menu
void admin_view::profileMenu()
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
        std::cout << "Name     :: " << admin.getName() << "\n\n";

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

// registration
bool admin_view::registration()
{
    Admin admin;

    std::string username, password, name;

    utils::header("ADMIN REGISTRATION");

    utils::showMessage(MESSAGE_TYPE::INFO, "Admin has not been registered yet!");

    std::cout << "\n\nUsername    :: ";
    std::getline(std::cin, username);
    admin.setUsername(username);

    std::cout << "\nPassword    :: ";
    std::getline(std::cin, password);
    admin.setPassword(password);

    std::cout << "\nName        :: ";
    std::getline(std::cin, name);
    admin.setName(name);

    // show admin details
    utils::header("ADMIN REGISTRATION DETAILS");
    std::cout << "Username    :: " << admin.getUsername() << "\n\n";
    std::cout << "Password    :: " << admin.getPassword() << "\n\n";
    std::cout << "Name        :: " << admin.getName() << "\n";

    return admin.registration();
}

// login
bool admin_view::login()
{
    Admin admin;

    std::string username, password;

    utils::header("ADMIN LOGIN");

    std::cout << "Username    :: ";
    std::getline(std::cin, username);

    std::cout << "\nPassword    :: ";
    std::getline(std::cin, password);

    return admin.login(username, password);
}

// update username
void admin_view::updateUsername(Admin admin)
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

        std::cout << "\n\nPress any key to continue...";

        utils::pauseScreen();

        break;
    }
}

// update password
void admin_view::updatePassword(Admin admin)
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

        std::cout << "\n\nPress any key to continue...";

        utils::pauseScreen();

        break;
    }
}

// update name
void admin_view::updateName(Admin admin)
{
    utils::clearScreen();
    utils::header("UPDATE NAME");
    std::string name;

    std::cout << "Old name    :: " << admin.getName();

    std::cout << "\n\nNew Name    :: ";
    std::getline(std::cin, name);
    admin.setName(name);

    std::cout << "\nNew name :: " << admin.getName();

    if (admin.update())
        utils::showMessage(MESSAGE_TYPE::SUCCESS, "\n\nName updated successfully!");
    else
        utils::showMessage(MESSAGE_TYPE::FAILURE, "\n\nName updation failed!");

    std::cout << "\n\nPress any key to continue...";

    utils::pauseScreen();
}

#endif