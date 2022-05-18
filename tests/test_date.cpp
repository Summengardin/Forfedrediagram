#define CATCH_CONFIG_MAIN

#include <iostream>

#include "catch.hpp"
#include "date.hpp"

TEST_CASE("calculateAge") {


    Date martinBirthday{22,6,1999};
    Date mahammedBirthday{15,5,1999};
    Date amalieBirthday{ 21, 8, 1998};
    Date henrikBirthday{29, 10, 2001};
    Date yallaBirthday{25, 1, 2003};
    Date hassanBirthday{13, 5, 2009};
    Date henningBirthday{29, 1, 1999};
    Date joachimBirthday{5,5,1999};
    





    unsigned int martinActualAge = 22;
    unsigned int mahammedActualAge = 23;
    unsigned int amalieActualAge = 23;
    unsigned int henrikActualAge = 20;
    unsigned int yallaActualAge = 19;
    unsigned int hassanActualAge = 13;
    unsigned int henningActualAge = 23;
    unsigned int joachimActualAge = 23;
    
    



    CHECK(Date::calculateAge(martinBirthday) == martinActualAge );
    CHECK(Date::calculateAge(mahammedBirthday) == mahammedActualAge );
    CHECK(Date::calculateAge(amalieBirthday) == amalieActualAge );
    CHECK(Date::calculateAge(henrikBirthday) == henrikActualAge );
   // CHECK(Date::calculateAge(hassanBirthday) == hassanActualAge );
    CHECK(Date::calculateAge(yallaBirthday) == yallaActualAge );
   // CHECK(Date::calculateAge(henningBirthday) == henningActualAge );
    //CHECK(Date::calculateAge(joachimBirthday) == joachimActualAge );
    


    }

TEST_CASE("isfuturDate"){
    Date martinBirthday{22,6,1999};
    Date mahammedBirthday{15,5,1999};
    Date amalieBirthday{ 21, 8, 1998};
    Date henrikBirthday{29, 10, 2001};
    Date yallaBirthday{25, 1, 2003};
    Date hassanBirthday{18, 5, 2022}; //testing one on the test date
    Date henningBirthday{29, 7, 2025}; // tesing on after the test dat
    Date joachimBirthday{19,6,2024};


    unsigned int martinActualAge = 22;
    unsigned int mahammedActualAge = 23;
    unsigned int amalieActualAge = 23;
    unsigned int henrikActualAge = 20;
    unsigned int yallaActualAge = 19;
    unsigned int hassanActualAge = 12;
    unsigned int henningActualAge = 23;
    unsigned int joachimActualAge = 23;



    CHECK(Date::isFuturDate(martinBirthday)== martinActualAge );
    CHECK(Date::isFuturDate(mahammedBirthday)== mahammedActualAge );
    CHECK(Date::isFuturDate(amalieBirthday) == amalieActualAge );
    CHECK(Date::isFuturDate(henrikBirthday) == henrikActualAge );
    CHECK(Date::isFuturDate(hassanBirthday) == hassanActualAge );
    CHECK(Date::isFuturDate(yallaBirthday) == yallaActualAge );
    CHECK(Date::isFuturDate(henningBirthday) == henningActualAge );
    CHECK(Date::isFuturDate(joachimBirthday) == joachimActualAge );


}
