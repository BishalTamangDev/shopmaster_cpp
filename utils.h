#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <limits>
#include <vector>
#include <any>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <ctime>  // for std::localtime
#include <format> // C++20 feature

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
    void clearScreen();                                        // clear screen
    void pauseScreen();                                        // pause screen
    void header(std::string);                                  // header
    void showLine(std::vector<int>, std::vector<std::string>); // show headline
    inline void showMessage(MESSAGE_TYPE, std::string);        // show message
    inline void showOption(int, std::string);                  // show option
    std::vector<std::any> getLineData(std::string);            // get line data
    void convertToLowerCase(std::string &);                    // convert strign into lowercase string
    void convertToWordCase(std::string &);                     // convert string into wordcase string
    void convertToUpperCase(std::string &);                    // convert string into uppercase
    void eraseWhiteSpace(std::string &);                       // erase white space
    std::string getDateString(std::array<int, 6>, bool);       // get date string
    std::array<int, 6> getDateFromString(std::string);         // get date from string
    std::array<int, 6> getCurrentDateTime();                   // get current date & time
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

// headline
void utils::showLine(std::vector<int> space, std::vector<std::string> data)
{
    int i = 0;
    std::cout << std::left;

    for (const auto &datum : data)
        std::cout << std::setw(space[i++]) << datum;

    std::cout << "\n";
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

// get date string
std::string utils::getDateString(std::array<int, 6> date, bool adding)
{
    if (date[0] == 0)
        return adding ? "" : "-";
    else
        return std::to_string(date[0]) + "-" + std::to_string(date[1]) + "-" + std::to_string(date[2]);
}

// get date from string
std::array<int, 6> utils::getDateFromString(std::string str)
{
    std::string cell;
    std::array<int, 6> date = {0, 0, 0, 0, 0, 0};

    std::stringstream ss(str);

    std::getline(ss, cell, '-');
    date[0] = std::stoi(cell);

    std::getline(ss, cell, '-');
    date[1] = std::stoi(cell);

    std::getline(ss, cell, '-');
    date[2] = std::stoi(cell);

    return date;
}

// get current date & time
std::array<int, 6> utils::getCurrentDateTime()
{
    std::array<int, 6> data;

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now(); // get current time as a time_point

    std::time_t current_time = std::chrono::system_clock::to_time_t(now); // convert to time_t (for c-tyle representation)

    std::tm *local_time = std::localtime(&current_time); // convert to local time || convert to tm struct

    // std::cout << "Current date & time :: " << std::put_time(local_time, "%Y-%m-%d %H:%M:%S"); // print the formatted date & time

    data[0] = 1900 + local_time->tm_year; // date :: year
    data[1] = local_time->tm_mon + 1;     // date :: month
    data[2] = local_time->tm_mday;        // date :: day
    data[3] = local_time->tm_hour;        // time :: hour
    data[4] = local_time->tm_min;         // time :: minute
    data[5] = local_time->tm_sec;         // time :: second

    return data;
}

#endif