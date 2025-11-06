#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <vector>
#include <any>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

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

// message type map
std::map<MESSAGE_TYPE, std::string> message_type_map = {
    {MESSAGE_TYPE::RESET, "\033[0m"},
    {MESSAGE_TYPE::INFO, "\033[33m"},
    {MESSAGE_TYPE::SUCCESS, "\033[32m"},
    {MESSAGE_TYPE::FAILURE, "\033[31m"},
};

// utils
namespace utils
{
    // function declarations
    void clearScreen();                                 // clear screen
    void pauseScreen();                                 // pause screen
    void header(std::string);                           // header
    inline void showMessage(MESSAGE_TYPE, std::string); // show message
    inline void showOption(int, std::string);           // show option
    std::vector<std::any> getLineData(std::string);     // get line data
    void convertToLowerCase(std::string &);             // convert strign into lowercase string
    void convertToWordCase(std::string &);              // convert string into wordcase string
    void convertToUpperCase(std::string &);             // convert string into uppercase
    void eraseWhiteSpace(std::string &);                // erase white space
}

// function definitions
// clear screen
void utils::clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// pause screen
void utils::pauseScreen()
{
#ifdef _WIN32
    _getch(); // Windows only
#else
    std::cin.get(); // Linux/macOS
#endif
}

// header
void utils::header(std::string title)
{
    const int total_dash = 50;

    int remaining_dash = 50 - title.length();

    utils::clearScreen();
    std::cout << std::string(total_dash, '=') << "\n";
    std::cout << std::setw(remaining_dash / 2) << "" << title << "\n";
    std::cout << std::string(total_dash, '=') << "\n\n";
}

// show message
inline void utils::showMessage(MESSAGE_TYPE type, std::string message)
{
    std::cout << message_type_map[type] << message << message_type_map[MESSAGE_TYPE::RESET];
}

// show options
inline void utils::showOption(int serial, std::string title)
{
    std::cout << std::left << std::setw(47) << title << "[" << serial << "]\n";
}

// get line data
std::vector<std::any> utils::getLineData(std::string line)
{
    std::string cell;
    std::stringstream ss(line);
    std::vector<std::any> data;

    while (std::getline(ss, cell, ','))
        data.push_back(cell);

    return data;
}

// convert string into lowercase string
void utils::convertToLowerCase(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c)
                   { return static_cast<char>(std::tolower(c)); });
}

// convert string into wordcase string
void utils::convertToWordCase(std::string &str)
{
    bool newWord = true; // Track if we’re at the start of a new word

    std::transform(str.begin(), str.end(), str.begin(), [&](unsigned char c)
                   {
                       if (std::isspace(c))
                       {
                           newWord = true; // Next character starts a new word
                           return c;
                       }

                       if (newWord)
                       {
                           newWord = false;
                           return static_cast<unsigned char>(std::toupper(c));
                       }

                       return static_cast<unsigned char>(std::tolower(c)); // lowercase rest
                   });
}

// convert string into uppercase
void utils::convertToUpperCase(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c)
                   { return std::toupper(c); });
}

// erase white space
void utils::eraseWhiteSpace(std::string &str)
{
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
}

#endif