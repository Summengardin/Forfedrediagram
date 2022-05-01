
#pragma once // FORFEDREDIAGRAM_DATE_HPP

#include <chrono>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

#include "helpers.hpp"

class Date
{
  public:
    Date() = default;

    Date(int d, int m, int y) : _day(d), _month(m), _year(y){};

    explicit Date(std::string dateAsString)
    {
        setDate(dateAsString);
    }

    [[nodiscard]] Date getDate() const
    {
        return *this;
    }

    [[nodiscard]] bool isValid() const
    {
        return !(_day == 0 || _month == 0 || _year == 0);
    }

    [[nodiscard]] std::string toString() const
    {
        if (isValid())
        {
            std::ostringstream ssDate;

            std::string dayString = std::to_string(_day);
            std::string monthString = std::to_string(_month);
            std::string yearString = std::to_string(_year);

            ssDate << std::setw(2) << std::setfill('0') << dayString << "-";
            ssDate << std::setw(2) << std::setfill('0') << monthString << "-";
            ssDate << std::setw(4) << std::setfill('0') << yearString;

            return ssDate.str();
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
        // Date must be in format DD-MM-YYYY
        std::regex format{R"(\d{2}\-\d{2}\-\d{4})"};
        std::smatch match;
        return std::regex_match(dateAsString, match, format);
    }

    [[nodiscard]] static int yearsBetween(const Date &date1, const Date &date2)
    {
        if (date1._year > 0 && date2._year > 0)
        {
            return date1._year - date2._year;
        }
        else
            return 0;
    }

  protected:
    int _day = 0;
    int _month = 0;
    int _year = 0;

    std::array<unsigned int, 12> daysInMonth = {31, 30, 28, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};

class Today : public Date
{
  public:
    Date operator()()
    {
        update();
        return getDate();
    }

    void update()
    {
        // Used for updating TODAY-date
        auto nowPtr = std::chrono::system_clock::now();
        std::time_t now = std::chrono::system_clock::to_time_t(nowPtr);

        std::tm localTime = *std::localtime(&now);
        _day = localTime.tm_mday;
        _month = localTime.tm_mon + 1;
        _year = localTime.tm_year + 1900;
    }
};

// FORFEDREDIAGRAM_DATE_HPP
