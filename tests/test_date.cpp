#define CATCH_CONFIG_MAIN

#include <iostream>

#include "catch.hpp"
#include "date/date.hpp"

TEST_CASE("calculateAge")
{


    Date date1{19, 5, 1999}; // testing one on same date as the test
    Date date2{5, 5, 1999};  // testing one before the test date


    unsigned int date1ActualAge = 23;
    unsigned int date2ActualAge = 23;


    CHECK(Date::calculateAge(date1) == date1ActualAge);
    CHECK(Date::calculateAge(date2) == date2ActualAge);
}

TEST_CASE("isfuturDate")
{

    Date date1{19, 5, 2000}; // testing one on the test date
    Date date2{29, 6, 1999}; // tesing one before the test date
    Date date3{17, 8, 2026}; // testing one after the test date


    CHECK_FALSE(Date::isFutureDate(date1));
    CHECK_FALSE(Date::isFutureDate(date2));
    CHECK(Date::isFutureDate(date3));
}

TEST_CASE("isDateValid"){
    Date date1{19, 5, 2022};
    Date date2{34,13,2022};
    Date date3{};

    CHECK(Date::isDateValid(date1));
    CHECK_FALSE(Date::isDateValid(date2));
}