#include <iostream>
#include <thread>
#include <map>
#include <string>

// import user-defined files
#include "utils.h"
#include "file_setup.h"

// function declarations
void menu(); // menu

// main
int main()
{
    std::thread file_setup(app_files::setup); // file setup thread
    file_setup.detach();                      // run file setup task in the background independently
    menu();
    return 0;
}

// menu
void menu()
{
    std::string choice;

    std::map<int, std::string> options = {
        {1, "Sell Product"},
        {2, "Search Product"},
        {3, "View Products"},
        {4, "View Today's Sales"},
        {5, "My Account Details"},
        {6, "Exit"},
    };

    while (true)
    {
        utils::clearScreen();

        utils::header("EMPLOYEE MENU");

        for (const auto &option : options)
            utils::showOption(option.first, option.second);

        std::cout << "\nYour choice :: ";
        std::getline(std::cin, choice);

        if (choice == "6")
            exit(0);

        utils::showMessage(MESSAGE_TYPE::INFO, "\nWork in progress!");

        utils::pauseScreen();
    }

    utils::pauseScreen();
}