#define CATCH_CONFIG_MAIN

#include <iostream>

#include "catch.hpp"
#include "person/person.hpp"

TEST_CASE("Getters Person"){
    std::string firstName = "For";
    std::string middleName = "Mellom";
    std::string lastName = "Etter";
    Date birth{22,6,1999};

    Person aPerson = Person(firstName, middleName, lastName, birth);
    Person bPerson;

    CHECK(firstName == aPerson.getFirstName());
    CHECK(middleName == aPerson.getMiddleName());
    CHECK(lastName == aPerson.getLastName());
    CHECK(birth == aPerson.getBirth());

    CHECK(firstName == bPerson.getFirstName());
    CHECK(middleName == bPerson.getMiddleName());
    CHECK(lastName == bPerson.getLastName());
    CHECK(birth == bPerson.getBirth());
}


