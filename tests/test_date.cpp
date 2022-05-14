#define CATCH_CONFIG_MAIN

#include <iostream>

#include "catch.hpp"
#include "date.hpp"

TEST_CASE("calculateAge") {
    Today today;

    Date martinBirthday{22,6,1999};
    Date mahammedBirthday{15,5,1999};
    Date amalieBirthday{ 21, 8, 1998};
    Date henrikBirthday{29, 10, 2001};
    Date yallaBirthday{25, 1, 2003};
    Date hassanBirthday{13, 5, 2009};
    Date henningBirthday{29, 1, 1999};
    Date joachimBirthday{5,5,1999};
    





    unsigned int martinActualAge = 22;
    unsigned int mahammedActualAge = 22;
    unsigned int amalieActualAge = 23;
    unsigned int henrikActualAge = 20;
    unsigned int yallaActualAge = 19;
    unsigned int hassanActualAge = 12;
    unsigned int henningActualAge = 23;
    unsigned int joachimActualAge = 23;
    
    



    CHECK(Date::calculateAge(martinBirthday, today()) == martinActualAge );
    CHECK(Date::calculateAge(mahammedBirthday,today()) == mahammedActualAge );
    CHECK(Date::calculateAge(amalieBirthday, today()) == amalieActualAge );
    CHECK(Date::calculateAge(henrikBirthday, today()) == henrikActualAge );
    CHECK(Date::calculateAge(hassanBirthday, today()) == hassanActualAge );
    CHECK(Date::calculateAge(yallaBirthday, today()) == yallaActualAge );
    CHECK(Date::calculateAge(henningBirthday, today()) == henningActualAge );
    CHECK(Date::calculateAge(joachimBirthday, today()) == joachimActualAge );
    


    }

TEST_CASE("isfuturDate"){
    Today today;


}
