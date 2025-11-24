// include header file
#include "../include/admin_interface.h"

// profile menu
void admin_interface::profileMenu()
{
    bool response;

    Admin admin;
    AdminManager adminManager;

    while (true)
    {
        utility::header("MY PROFILE");

        response = adminManager.fetch(admin); // fetch admin details

        if (!response)
        {
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "Could not fetch admin details!");
            utility::showMessage(utility::MESSAGE_TYPE::INFO, "\n\nPress any key to go back...");
            utility::pauseScreen();
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
        {
            utility::showOption(option.first, option.second);
        }

        std::string choice;

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "1")
        {
            admin_interface::updateUsername(admin);
        }
        else if (choice == "2")
        {
            admin_interface::updatePassword(admin);
        }
        else if (choice == "3")
        {
            admin_interface::updateName(admin);
        }
        else if (choice == "4")
        {
            break;
        }
        else
        {
            utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\n\nInvalid choice!");
            utility::pauseScreen();
        }
    }
}

// registration
bool admin_interface::registration()
{
    Admin admin;
    AdminManager adminManager;

    std::string username, password, name;

    utility::header("ADMIN REGISTRATION");

    utility::showMessage(utility::MESSAGE_TYPE::INFO, "Admin has not been registered yet!");

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
    utility::header("ADMIN REGISTRATION DETAILS");
    std::cout << "Username    :: " << admin.getUsername() << "\n\n";
    std::cout << "Password    :: " << admin.getPassword() << "\n\n";
    std::cout << "Name        :: " << admin.getName() << "\n";

    return adminManager.registration(admin);
}

// login
bool admin_interface::login()
{
    Admin admin;
    AdminManager adminManager;

    std::string username, password;

    utility::header("ADMIN LOGIN");

    std::cout << "Username    :: ";
    std::getline(std::cin, username);

    std::cout << "\nPassword    :: ";
    std::getline(std::cin, password);

    return adminManager.login(username, password);
}

// update name
void admin_interface::updateName(Admin admin)
{
    std::string new_name, old_name, choice;

    AdminManager adminManager;

    while (true)
    {
        utility::header("UPDATE NAME");

        old_name = admin.getName();

        std::cout << "Old name    :: " << old_name;

        std::cout << "\n\nNew Name    :: ";
        std::getline(std::cin, new_name);

        utility::convertToLowerCase(new_name);
        utility::convertToLowerCase(old_name);

        if (new_name == old_name)
        {
            utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nYou entered old name!");
        }
        else
        {
            admin.setName(new_name);

            if (!adminManager.update(admin))
            {
                utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nName updation failed!");
            }
            else
            {
                utility::showMessage(utility::MESSAGE_TYPE::SUCCESS, "\nName updated successfully!");
                std::cout << "\n\nPress any key to continue...";
                utility::pauseScreen();
                break;
            }
        }

        std::cout << "\n\nDo you want to try again [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "Y" && choice != "y")
        {
            break;
        }
    }
}

// update username
void admin_interface::updateUsername(Admin admin)
{
    std::string choice;
    std::string new_username;

    AdminManager adminManager;

    while (true)
    {
        utility::header("UPDATE USERNAME");

        std::cout << "Old username       :: " << admin.getUsername() << "\n\n";

        std::cout << "Enter new username :: ";
        std::getline(std::cin, new_username);

        if (new_username == admin.getUsername())
        {
            utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nYou entered old username!");
        }
        else
        {
            std::cout << "\nNew username       :: " << new_username;

            admin.setUsername(new_username); // set new username

            // proceed update
            if (!adminManager.update(admin))
            {
                utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\n\nUsername updation failed!");
            }
            else
            {
                utility::showMessage(utility::MESSAGE_TYPE::SUCCESS, "\n\nUsername updated successfully!");
                std::cout << "\n\nPress any key to continue...";
                utility::pauseScreen();
                break;
            }
        }

        std::cout << "\n\nDo you want to try again [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "Y" && choice != "y")
        {
            break;
        }
        else
        {
            continue;
        }
    }
}

// update password
void admin_interface::updatePassword(Admin admin)
{
    AdminManager adminManager;

    std::string choice;
    std::string old_password, new_password, new_password_confirmation;

    while (true)
    {
        utility::header("UPDATE PASSWORD");

        // get old password
        std::cout << "Enter old password :: ";
        std::getline(std::cin, old_password);

        if (old_password != admin.getPassword())
        {
            utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nInvalid password!");
        }
        else
        {
            std::cout << "\nEnter new password :: ";
            std::getline(std::cin, new_password);

            if (new_password == admin.getPassword())
            {
                utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nYou entered old password!");
            }
            else
            {
                std::cout << "\nEnter again for confirmation :: ";
                std::getline(std::cin, new_password_confirmation);

                if (new_password != new_password_confirmation)
                {
                    utility::showMessage(utility::MESSAGE_TYPE::INFO, "\nPassword confirmation failed!");
                }
                else
                {
                    admin.setPassword(new_password); // set new password

                    // proceed update
                    if (!adminManager.update(admin))
                    {
                        utility::showMessage(utility::MESSAGE_TYPE::FAILURE, "\nPassword updation failed!");
                    }
                    else
                    {
                        utility::showMessage(utility::MESSAGE_TYPE::SUCCESS, "\nPassword updated successfully!");
                        std::cout << "\n\nPress any key to continue...";
                        utility::pauseScreen();
                        break;
                    }
                }
            }
        }

        std::cout << "\n\nDo you want to try again [y/n]? ";
        std::getline(std::cin, choice);

        if (choice != "Y" && choice != "y")
        {
            break;
        }
    }
}
