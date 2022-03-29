//
// Created by Martin on 24.03.2022.
//

#ifndef FORFEDREDIAGRAM_COMMONFUNCTIONS_HPP
#define FORFEDREDIAGRAM_COMMONFUNCTIONS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include <regex>

namespace COM{
    // Common functions


    std::string getString(const std::string& prompt){
        std::cout << prompt << std::endl;

        std::string input;
        std::getline(std::cin >> std::ws, input);

        return input;
    }

    template<class T>
    T getNum(const std::string& prompt){
        std::cout << prompt << std::endl;

        T input;
        std::cin >> input;
        while(!std::cin.good()){
            std::cout << "Det der var ingen gyldig verdi, prøv igjen." << std::endl;
            std::cin.clear();
            std::cin.ignore(100000, '\n');
            std::cin >> input;

        }

        return input;
    }


    std::vector<std::string> splitString(const std::string& str, char delimiter){
        // Split a string by a delimiter. Return a vector of all the elements
        std::vector<std::string> split;

        std::string token;
        std::stringstream s(str);

        while(std::getline(s, token, delimiter)){
            split.push_back(token);
        }

        return split;
    }


    void debug(const std::string& prompt){
        if(false)
            std::cout << "\n" << "DEBUG: " << prompt << std::endl;
    }



}



#endif //FORFEDREDIAGRAM_COMMONFUNCTIONS_HPP
