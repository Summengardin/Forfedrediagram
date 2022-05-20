
#define CATCH_CONFIG_MAIN

#include <iostream>

#include "catch.hpp"
#include "date/Date.hpp"

TEST_CASE("calculateAge")
{

    Date date1{19, 5, 1999}; // testing one on same date as the test
    Date date2{5, 5, 1999};  // testing one before the test date


    unsigned int date1ActualAge = 23;
    unsigned int date2ActualAge = 23;


    CHECK(Date::calculateAge(date1) == date1ActualAge);
    CHECK(Date::calculateAge(date2) == date2ActualAge);
}

TEST_CASE("isFutureDate")
{

    Date date1{19, 5, 2000}; // testing one on the test date
    Date date2{29, 7, 2025}; // tesing one after the test date
    Date date3{19, 5, 2022}; // testing one before the test date


    CHECK_FALSE(Date::isFutureDate(date1));
    CHECK(Date::isFutureDate(date2));
    CHECK_FALSE(Date::isFutureDate(date3));
}
