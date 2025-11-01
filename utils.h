#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <map>

#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#endif

#ifndef SHOPMASTER_UTILS_H
#define SHOPMASTER_UTILS_H

// global variables
const std::string app_name = "ShopMaster - Shop Management"; // app name

// message type
enum class MESSAGE_TYPE
{
    RESET,
    INFO,
    SUCCESS,
    FAILURE
};

std::map<MESSAGE_TYPE, std::string> message_type_map = {
    {MESSAGE_TYPE::RESET, "\033[0m"},
    {MESSAGE_TYPE::INFO, "\033[33m"},
    {MESSAGE_TYPE::SUCCESS, "\033[32m"},
    {MESSAGE_TYPE::FAILURE, "\033[31m"},
};

namespace Utils
{
    // function declarations
    void clearScreen();                                 // clear screen
    void pauseScreen();                                 // pause screen
    void header(std::string);                           // header
    inline void showMessage(MESSAGE_TYPE, std::string); // show message
    inline void showOption(int, std::string);           // show option
}

// function definitions
// clear screen
void Utils::clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// pause screen
void Utils::pauseScreen()
{
#ifdef _WIN32
    _getch(); // Windows only
#else
    std::cin.get(); // Linux/macOS
#endif
}

// header
void Utils::header(std::string title)
{
    const int total_dash = 50;

    int remaining_dash = 50 - title.length();

    std::cout << std::string(total_dash, '=') << "\n";
    std::cout << std::setw(remaining_dash / 2) << "" << title << "\n";
    std::cout << std::string(total_dash, '=') << "\n\n";
}

// show message
inline void Utils::showMessage(MESSAGE_TYPE type, std::string message)
{
    std::cout << message_type_map[type] << message << message_type_map[MESSAGE_TYPE::RESET] << "\n";
}

// show options
inline void Utils::showOption(int serial, std::string title)
{
    std::cout << std::left << std::setw(47) << title << "[" << serial << "]\n";
}

#endif