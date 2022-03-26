
#ifndef FORFEDREDIAGRAM_DATE_HPP
#define FORFEDREDIAGRAM_DATE_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <regex>
#include <chrono>

//#include "commonFunctions.hpp"

class Date{
public:
    Date() = default;

    Date(int d, int m, int y):
            _day(d),
            _month(m),
            _year(y)
    {};

    explicit Date(std::string dateAsString)
    {
        setDate(dateAsString);
    }


    [[nodiscard]] std::string getDate() const{
        return (_day < 10 ? "0" : "") + std::to_string(_day)
               + "-" + (_month < 10 ? "0" : "") + std::to_string(_month)
               + "-" + std::to_string(_year);
    }


    [[nodiscard]] int getDay() const {
        return _day;
    }

    [[nodiscard]] int getMonth() const {
        return _month;
    }

    [[nodiscard]] int getYear() const {
        return _year;
    }

    void setDate(std::string& dateAsString){
        if (checkStringFormat(dateAsString)){
            std::vector<std::string> numbers = COM::splitString(dateAsString, '-');
            _day = std::stoi(numbers[0]);
            _month = std::stoi(numbers[1]);
            _year = std::stoi(numbers[2]);
        } else {
            std::cout << "Invalid date format, Fuck You!" << std::endl;
        }
    }


    [[nodiscard]]static bool checkStringFormat(const std::string& dateAsString) {
        std::regex format{R"(\d{2}\-\d{2}\-\d{4})"}; // Date should be in format DD-MM-YYYY
        std::smatch match;
        return std::regex_match(dateAsString, match, format);
    }


protected:
    int _day = 0;
    int _month = 0;
    int _year = 0;



};

class Today : public Date{
public:

    std::string operator()(){
        update();
        return getDate();
    }

    void update(){
        // Used for updating TODAY-date
        auto nowPoint = std::chrono::system_clock::now();
        std::time_t now = std::chrono::system_clock::to_time_t(nowPoint);

        std::tm localTime = *std::localtime(&now);
        _day = localTime.tm_mday;
        _month = localTime.tm_mon + 1;
        _year = localTime.tm_year + 1900;
    }
};


#endif //FORFEDREDIAGRAM_DATE_HPP
