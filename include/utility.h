#pragma once

// include header file
#include "project_setup.h"

// utility
namespace utility
{
    // variable
    enum class MESSAGE_TYPE
    {
        RESET,
        INFO,
        SUCCESS,
        FAILURE
    };

    extern std::map<MESSAGE_TYPE, std::string> message_type_map;

    // functions
    void clearScreen();                                        // clear screen
    void pauseScreen();                                        // pause screen
    void header(std::string);                                  // header
    void showLine(std::vector<int>, std::vector<std::string>); // show headline
    void showMessage(MESSAGE_TYPE, std::string);               // show message
    void showOption(int, std::string);                         // show option
    void convertToLowerCase(std::string &);                    // convert strign into lowercase string
    void convertToWordCase(std::string &);                     // convert string into wordcase string
    void convertToUpperCase(std::string &);                    // convert string into uppercase
    void eraseWhiteSpace(std::string &);                       // erase white space

    std::string getDateString(std::array<int, 6>, bool); // get date string
    std::string getFormattedDouble(double);              // get formatted double as string

    std::array<int, 6> getDateFromString(std::string); // get date from string
    std::array<int, 6> getCurrentDateTime();           // get current date & time

    std::vector<std::any> getLineData(std::string); // get line data
}
