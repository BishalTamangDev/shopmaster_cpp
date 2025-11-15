#pragma once

#define DEBUG_MODE

// include header files
#include <iostream>
#include <iomanip>
#include <limits>
#include <cctype>
#include <ctime>
#include <format>

// file handling
#include <fstream>
#include <sstream>
#include <filesystem>

// multi-threading
#include <thread>
#include <chrono>

// data-types
#include <string>
#include <array>
#include <map>
#include <vector>
#include <any>
#include <algorithm>

#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#endif

// user-defined header files
#include "utility.h"

// namespace
namespace project_setup
{
    // variables
    extern std::string project_name;
    extern std::map<std::string, std::string> filenames;
    extern std::map<std::string, std::vector<std::string>> headlines;

    // functions
    bool fileSetup();                                          // setup files
    bool createNewFile(std::string, std::vector<std::string>); // create new file
    bool updateFile(std::string, std::string);                 // update file
}