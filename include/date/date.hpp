
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

    explicit Date(const std::string &dateAsString) { setDate(dateAsString); }

    [[nodiscard]] Date getDate() const { return *this; }

    [[nodiscard]] bool isValid() const { return !(_day == 0 || _month == 0 || _year == 0); }

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
        return "unknown date";
    }

    [[nodiscard]] unsigned int getDay() const { return _day; }

    [[nodiscard]] unsigned int getMonth() const { return _month; }

    [[nodiscard]] unsigned int getYear() const { return _year; }

    bool setDate(const std::string &dateAsString)
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
    [[nodiscard]] static bool isDateValid(const Date &date) { return dayIsValid(date) && monthIsValid(date); }


    [[nodiscard]] static unsigned int calculateAge(const Date &birth) { return calculateAge(birth, today()); }

    [[nodiscard]] static unsigned int calculateAge(const Date &birth, const Date &death)
    {
        int age = death.getYear() - birth.getYear();
        if (age < 0)
            return 0;

        if (birth.getMonth() > death.getMonth() ||
            (birth.getMonth() == death.getMonth() && birth.getDay() > death.getDay()))
        {
            return age - 1;
        }
        else
        {
            return age;
        }
    }


    [[nodiscard]] static bool isFutureDate(const Date &date)
    {
        if (date.getYear() > today().getYear() ||
            (date.getYear() == today().getYear() && date.getMonth() > today().getMonth()) ||
            (date.getYear() == today().getYear() && date.getMonth() == today().getMonth() &&
             date.getDay() > today().getDay()))
        {
            return true;
        }
        return false;
    }

    [[nodiscard]] bool isFutureDate() const { return isFutureDate(*this); }

    [[nodiscard]] static bool dayIsValid(const Date &date) const
    {
        unsigned int monthIndex = date.getMonth() - 1;
        return date.getDay() <= DAYS_IN_MONTH[monthIndex];
    }

    [[nodiscard]] static bool monthIsValid(const Date &date) const { return date.getMonth() <= MONTHS_IN_YEAR; }

    [[nodiscard]] static unsigned int yearsBetween(const Date &date1, const Date &date2)
    {
        if (date1._year > 0 && date2._year > 0)
        {
            return date1._year - date2._year;
        }
        else
            return 0;
    }

    static Date today()
    {
        auto nowPtr = std::chrono::system_clock::now();
        std::time_t now = std::chrono::system_clock::to_time_t(nowPtr);


        std::tm localTime = *std::localtime(&now);
        auto day = localTime.tm_mday;
        auto month = localTime.tm_mon + 1;
        auto year = localTime.tm_year + 1900;

        return {day, month, year};
    }

    bool operator==(const Date &other) const
    {
        return (other._year == this->_year && other._month == this->_month && other._day == this->_day);
    }

    bool operator!=(const Date &other) const
    {
        return (other._year != this->_year || other._month != this->_month || other._day != this->_day);
    }


  protected:
    unsigned int _day = 0;
    unsigned int _month = 0;
    unsigned int _year = 0;

    static inline const std::array<unsigned int, 12> DAYS_IN_MONTH = {31, 30, 28, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    static inline const unsigned int MONTHS_IN_YEAR = 12;
};


// FORFEDREDIAGRAM_DATE_HPP
