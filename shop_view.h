#include <iostream>

// import user-defined header files
#include "shop_class.h"
#include "shop_utility.h"

#ifndef SHOPMASTER_SHOP_VIEW_H
#define SHOPMASTER_SHOP_VIEW_H

// namespace :: shop
namespace shop_view
{
    void menu();         // my shop menu
    bool registration(); // register shop
    void update(Shop &); // update shop
}

// menu
void shop_view::menu()
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
            std::cout << "\n\nPress any key to go back...";
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
            shop_view::update(shop);
        else if (choice == "2")
            return;
        else
        {
            utils::showMessage(MESSAGE_TYPE::FAILURE, "\nInvalid choice!");
            utils::pauseScreen();
        }
    }
}

// registration
bool shop_view::registration()
{
    Shop shop;

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

        status = shop.registration();

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

// update
void shop_view::update(Shop &shop)
{
    int ward;
    bool details_changed = false;

    std::string choice;
    Shop new_shop;
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
    std::cout << "Name             :: " << shop.getName() << "\n";
    std::cout << "PAN              :: " << shop.getPan() << "\n";
    std::cout << "Currency         :: " << shop.getCurrency() << "\n";
    std::cout << "Contact Number   :: " << shop.getContactNumber() << "\n";
    std::cout << "Address          :: " << shop.getAddress() << "\n";

    std::cout << "\nAre you sure you want to update [y/n]? ";
    std::getline(std::cin, choice);

    if (choice != "Y" && choice != "y")
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

#endif