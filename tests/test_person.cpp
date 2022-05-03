#define CATCH_CONFIG_MAIN

#include <iostream>

#include "catch.hpp"
#include "../examples/include/person.hpp"

TEST_CASE("Getters Person"){
    std::string firstName = "For";
    std::string middleName = "Mellom";
    std::string lastName = "Etter";
    Date birth{22,6,1999};

    enum gender{
        unknown,
        male,
        female
    };
    Person Martin = Person(firstName, lastName);

    REQUIRE(firstName == Martin.getFirstName());
    REQUIRE(lastName == Martin.getLastName());
}

TEST_CASE("Get _age"){
    std::string date = "22-06-1999";
    int actualAge = 23;

    Person person;
    person.setBirth(date);

    REQUIRE(person.getAge() == actualAge);
}

