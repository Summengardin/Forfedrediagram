//
// Created by Martin on 15.03.2022.
//

#include <iostream>
#include <string>

#include "catch.hpp"
#include "../include/UsefulFunctions.hpp"

TEST_CASE("Split string"){
    std::string string1 = "22-06-1999";
    std::string string2 = "En liten tur i skogen";
    std::string string3 = "1;2;3;4;5;6;7;8;9";

    std::vector<std::string> correctString1 = {"22", "06", "1999"};
    std::vector<std::string> correctString2 = {"En", "liten", "tur", "i", "skogen"};
    std::vector<std::string> correctString3 = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

    REQUIRE(correctString1 == MM::splitString(string1, '-'));
    REQUIRE(correctString2 == MM::splitString(string2, ' '));
    REQUIRE(correctString3 == MM::splitString(string3, ';'));
}

TEST_CASE("Check date format")
{
    std::string birth = "22-06-1999";
    std::string death = "23061999";
    std::string unknownDelimiter = "23.06.1999";

    REQUIRE(MM::Date::checkStringFormat((birth)) == true);
    REQUIRE(MM::Date::checkStringFormat((death)) == false);
    REQUIRE(MM::Date::checkStringFormat((unknownDelimiter)) == false);
}
