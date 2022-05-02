#pragma once // FORFEDREDIAGRAM_COMMONFUNCTIONS_HPP

#include <chrono>
#include <fstream>
#include <iostream>
#include <optional>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "json.hpp"
using json = nlohmann::json;

namespace COM
{
// Common functions

inline std::string getString(const std::string &prompt, bool allowEmpty = false)
{
    std::cout << prompt << std::endl;

    std::string input;
    std::noskipws(std::cin);

    std::getline(std::cin, input);

    while (!allowEmpty && input.empty())
    {
        std::cout << "\nThis field may not be empty, try again:" << std::endl;
        std::getline(std::cin, input);
    }

    std::skipws(std::cin);

    return input;
}

template <class T> inline T convert(const std::string &str)
{
    // https://gist.github.com/mark-d-holmberg/862733
    std::istringstream iss(str);
    T num;
    iss >> num;

    return num;
}

inline bool isNumber(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), [](char c) { return std::isdigit(c); });
}

template <class T> inline T getNum(const std::string &prompt)
{
    std::cout << prompt << std::endl;

    std::string inputAsString;
    std::getline(std::cin, inputAsString);

    while (!isNumber(inputAsString))
    {
        std::cout << "That was not a number, please try again:" << std::endl;
        std::getline(std::cin, inputAsString);
    }

    return convert<T>(inputAsString);
}

inline std::vector<std::string> splitString(const std::string &str, char delimiter)
{
    // Split a string by a delimiter. Return a vector of all the elements
    std::vector<std::string> split;

    std::string token;
    std::stringstream s(str);

    while (std::getline(s, token, delimiter))
    {
        split.push_back(token);
    }

    return split;
}

inline void debug(const std::string &prompt)
{
    if (true)
        std::cout << "\n"
                  << "DEBUG: " << prompt << std::endl;
}

inline bool fileExists(const std::string &filepath)
{
    std::ifstream fileStream(filepath);
    return fileStream.is_open();
}

inline bool isAlphaNumeric(const std::string &str)
{
    //        std::regex format{R"(\A[a-zA-Z0-9 ]+\Z)"};
    std::regex format{R"([a-zA-Z])"};
    std::smatch match;
    std::regex_search(str, match, format);
    std::cout << "match_size:  " << match.size() << std::endl;
    for (auto m : match)
    {
        std::cout << m << std::endl;
    }

    return std::regex_match(str, format);
}

inline bool fileIsType(const std::string &mainStr, const std::string &filetype)
{
    if (!isAlphaNumeric(filetype))
    {
        std::cout << "Filetype: " << filetype << " is not alphanumeric" << std::endl;
        return false;
    }
    std::string testStr = "(\\." + filetype + ")\\z";
    std::cout << "testStr is: " << testStr << std::endl;
    std::regex format{testStr}; // Example (\.json)\z
    std::smatch match;
    return std::regex_match(mainStr, format);
}

inline bool stringHasEnding(const std::string &mainStr, const std::string &ending)
{
    if (mainStr.size() >= ending.size() && mainStr.compare(mainStr.size() - ending.size(), ending.size(), ending) == 0)
        return true;
    else
        return false;
}

inline std::optional<json> openFileAsJson(const std::string &filepath)
{
    std::cout << filepath << std::endl;
    // Sjekk at filen faktisk er ".json"-fil
    if (!stringHasEnding(filepath, ".json"))
    {
        return std::nullopt;
    }

    std::ifstream fileStream(filepath);
    json jsonFile;
    fileStream >> jsonFile;

    return jsonFile;
}

} // namespace COM

// FORFEDREDIAGRAM_COMMONFUNCTIONS_HPP
