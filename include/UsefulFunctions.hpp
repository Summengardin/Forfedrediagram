//
// Created by Martin on 24.03.2022.
//

#ifndef FORFEDREDIAGRAM_USEFULFUNCTIONS_HPP
#define FORFEDREDIAGRAM_USEFULFUNCTIONS_HPP

#include <iostream>
#include <string>

namespace MM{
    // Mahammed og Martin = MM

    template<class T>
    T& getUserInput(const std::string& prompt){
        std::cout << prompt << std::endl;

        T input;
        std::cin >> input;

        return input;
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

        explicit Date(std::string dateAsString){
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
            day = (int)(dateAsString[0]) * 10 + (int)(dateAsString[1]);
            month = static_cast<int>(dateAsString[3]) * 10 + static_cast<int>(dateAsString[4]);
            month = static_cast<int>(dateAsString[6]) * 1000 + static_cast<int>(dateAsString[7]) * 100 + static_cast<int>(dateAsString[8]) * 10 + static_cast<int>(dateAsString[9]);
        }

        int day = -1;
        int month = -1;
        int year = -1;
    };


}



#endif //FORFEDREDIAGRAM_USEFULFUNCTIONS_HPP
