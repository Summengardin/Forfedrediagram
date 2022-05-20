
#pragma once // FORFEDREDIAGRAM_DATE_HPP

#include <chrono>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

#include "Helpers.hpp"

class Date
{
  public:
    Date() = default;

    Date(int d, int m, int y)
        : _day(d)
        , _month(m)
        , _year(y){};

    explicit Date(const std::string &dateAsString)
    {
        setDate(dateAsString);
    }

    [[nodiscard]] Date getDate() const
    {
        return *this;
    }

    [[nodiscard]] bool isNull() const
    {
        return (_day == 0 || _month == 0 || _year == 0);
    }

    [[nodiscard]] std::string toString() const
    {
        if (!isNull())
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

    [[nodiscard]] unsigned int getDay() const
    {
        return _day;
    }

    [[nodiscard]] unsigned int getMonth() const
    {
        return _month;
    }

    [[nodiscard]] unsigned int getYear() const
    {
        return _year;
    }

    void setDate(const std::string &dateAsString)
    {
        if (!validateStringFormat(dateAsString))
            throw std::invalid_argument("Invalid date format");

        std::vector<std::string> numbers = COM::splitString(dateAsString, '-');
        _day = std::stoi(numbers[0]);
        _month = std::stoi(numbers[1]);
        _year = std::stoi(numbers[2]);
    }

    [[nodiscard]] static bool validateStringFormat(const std::string &dateAsString)
    {
        // Date must be in format DD-MM-YYYY
        std::regex format{R"(\d{2}\-\d{2}\-\d{4})"};
        std::smatch match;
        return std::regex_match(dateAsString, match, format);
    }


    [[nodiscard]] static bool dayIsValid(const Date &date)
    {
        if (!date.isNull() && (1 <= date.getMonth() && date.getMonth() <= 12))
        {
            unsigned int monthIndex = date.getMonth() - 1;
            return date.getDay() <= DAYS_IN_MONTH[monthIndex];
        }

        return false;
    }


    [[nodiscard]] static bool monthIsValid(const Date &date)
    {
        return date.getMonth() <= MONTHS_IN_YEAR;
    }

    [[nodiscard]] bool isReal() const
    {
        if (!isNull() && (1 <= _month && _month <= 12))
        {
            unsigned int monthIndex = _month - 1;
            return _day <= DAYS_IN_MONTH[monthIndex];
        }

        return false;
    }

    [[nodiscard]] static unsigned int calculateAge(const Date &birth)
    {
        return calculateAge(birth, today());
    }


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
        return (date > today());
    }

    [[nodiscard]] bool isFutureDate() const
    {
        return isFutureDate(*this);
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

    bool operator<(const Date &other) const
    {
        if (_year < other.getYear() || (_year == other.getYear() && _month < other.getMonth()) ||
            (_year == other.getYear() && _month == other.getMonth() && _day < other.getDay()))
            return true;
        return false;
    }

    bool operator>(const Date &other) const
    {
        if (_year > other.getYear() || (_year == other.getYear() && _month > other.getMonth()) ||
            (_year == other.getYear() && _month == other.getMonth() && _day > other.getDay()))
            return true;
        return false;
    }

    bool operator<=(const Date &other) const
    {
        if (_year <= other.getYear() || (_year == other.getYear() && _month <= other.getMonth()) ||
            (_year == other.getYear() && _month == other.getMonth() && _day <= other.getDay()))
            return true;
        return false;
    }

    bool operator>=(const Date &other) const
    {
        if (_year >= other.getYear() || (_year == other.getYear() && _month >= other.getMonth()) ||
            (_year == other.getYear() && _month == other.getMonth() && _day >= other.getDay()))
            return true;
        return false;
    }

  protected:
    unsigned int _day = 0;
    unsigned int _month = 0;
    unsigned int _year = 0;

    static inline const std::array<unsigned int, 12> DAYS_IN_MONTH = {31, 30, 28, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    static inline const unsigned int MONTHS_IN_YEAR = 12;
};


// FORFEDREDIAGRAM_DATE_HPP
