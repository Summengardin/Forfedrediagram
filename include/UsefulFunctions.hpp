//
// Created by Martin on 24.03.2022.
//

#ifndef FORFEDREDIAGRAM_USEFULFUNCTIONS_HPP
#define FORFEDREDIAGRAM_USEFULFUNCTIONS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>

namespace MM{
    // Mahammed og Martin = MM

    template<class T>
    T getUserInput(const std::string& prompt){
        std::cout << prompt << std::endl;

        T input;
        std::cin >> input;

        return input;
    }

    std::vector<std::string> splitString(const std::string& str, char delimiter){
        std::vector<std::string> split;

        std::string token;
        std::stringstream s(str);

        while(std::getline(s, token, delimiter)){
            split.push_back(token);
        }

        return split;
    }


    void debug(const std::string& prompt){
        std::cout << "\n" << "DEBUG: " << prompt << std::endl;
    }


    struct Date{
        Date() = default;

        Date(int d, int m, int y):
        day(d),
        month(m),
        year(y)
        {};

        explicit Date(std::string dateAsString)
        {
            setDate(dateAsString);
        }

        [[nodiscard]] std::string getDate() const{
            if(day == -1 and month == -1 and year == -1){
                return "Unknown";
            } else if(day == -1 and month == -1){
                return std::to_string(year);
            } else if(day == -1 and year == -1){
                return std::to_string(month);
            } else if(month == -1 and year == -1){
                return std::to_string(year);
            } else if(day == -1){
                return std::to_string(month) + "-" + std::to_string(year);
            } else if(month == -1){
                return std::to_string(day) + "--" + std::to_string(year);
            } else if(year == -1){
                return std::to_string(day) + "-" + std::to_string(month);
            } else{
                return std::to_string(day) + "-" + std::to_string(month) + "-" + std::to_string(year);
            }
        }

        void setDate(std::string& dateAsString){
            if (checkStringFormat(dateAsString)){
                std::vector<std::string> numbers = splitString(dateAsString, '-');
                day = std::stoi(numbers[0]);
                month = std::stoi(numbers[1]);
                year = std::stoi(numbers[2]);
            } else {
                std::cout << "Invalid date format, Fuck You!" << std::endl;
            }
        }

        [[nodiscard]]static bool checkStringFormat(const std::string& dateAsString) {
            std::regex format{R"(\d{2}\-\d{2}\-\d{4})"};
            std::smatch match;
            return std::regex_match(dateAsString, match, format);
        }

        int day = -1;
        int month = -1;
        int year = -1;
    };


}



#endif //FORFEDREDIAGRAM_USEFULFUNCTIONS_HPP
