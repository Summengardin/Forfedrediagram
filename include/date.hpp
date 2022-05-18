
#pragma once//FORFEDREDIAGRAM_DATE_HPP


#include <chrono>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

#include "commonFunctions.hpp"

class Date
{
public:
    Date() = default;

    Date(int d, int m, int y) :
        _day(d),
        _month(m),
        _year(y){};

    explicit Date(std::string dateAsString)
    {
        setDate(dateAsString);
    }



    [[nodiscard]] bool validate() const
    {
        return !(_day == 0 || _month == 0 || _year == 0);
    }


    [[nodiscard]] std::string toString() const
    {
        if (validate())
        {
            std::ostringstream oSStream;

            std::string dayString = std::to_string(_day);
            std::string monthString = std::to_string(_month);
            std::string yearString = std::to_string(_year);

            oSStream << std::setw(2) << std::setfill('0') << dayString << "-";
            oSStream << std::setw(2) << std::setfill('0') << monthString << "-";
            oSStream << std::setw(4) << std::setfill('0') << yearString;

            return oSStream.str();
            return (_day < 10 ? "0" : "") + std::to_string(_day) + "-" + (_month < 10 ? "0" : "") + std::to_string(_month) + "-" + std::to_string(_year);
        }
        return "Unknown date";
    }

    [[nodiscard]] int getDay() const
    {
        return _day;
    }

    [[nodiscard]] int getMonth() const
    {
        return _month;
    }

    [[nodiscard]] int getYear() const
    {
        return _year;
    }

    bool setDate(std::string &dateAsString)
    {
        if (validateStringFormat(dateAsString))
        {
            std::vector<std::string> numbers = COM::splitString(dateAsString, '-');
            _day = std::stoi(numbers[0]);
            _month = std::stoi(numbers[1]);
            _year = std::stoi(numbers[2]);
            return true;
        }
        return false;
    }


    [[nodiscard]] static bool validateStringFormat(const std::string &dateAsString)
    {
        std::regex format{R"(\d{2}\-\d{2}\-\d{4})"};// Date should be in format DD-MM-YYYY
        std::smatch match;
        return std::regex_match(dateAsString, match, format);
    }


    [[nodiscard]] static unsigned int calculateAge(const Date &date){
        unsigned int age = today()._year - date._year;
        if(date._month > today()._month || (date._month == today()._month && date._day > today()._day)) {
            return age - 1;
        }
        return age;
    }


    [[nodiscard]] static bool isFuturDate(const Date &date){
        unsigned int age = today()._year - date._year;
        if (date._month < today()._month || date._day < today()._day || date._year < today()._year) {
            return true;
        }
           else {
               return age;
           }
        }

    static Date today(){
        // Used for updating TODAY-date
        auto nowPtr = std::chrono::system_clock::now();
        std::time_t now = std::chrono::system_clock::to_time_t(nowPtr);

        std::tm localTime = *std::localtime(&now);
       auto day = localTime.tm_mday;
       auto month = localTime.tm_mon + 1;
       auto year = localTime.tm_year + 1900;

       return {day, month, year};
    }


    int LeapYear() {
        std::cout << "enter a year:";
        std::cin >> _year;

        if (_year % 400 == 0) {
            std::cout << _year << "is a leap year.";

        }
        else if (_year % 4 == 0) {
            std::cout << _year << " is a leap year.";

        }
        else {
            std::cout << _year << "is not a leap year.";
        }
        return 0;
    }

protected:
    unsigned int _day = 0;
    unsigned int _month = 0;
    unsigned int _year = 0;

    std::array<unsigned int, 12> daysInMonth = {31, 30, 28, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};



//FORFEDREDIAGRAM_DATE_HPP
