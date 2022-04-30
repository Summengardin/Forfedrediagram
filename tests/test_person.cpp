#define CATCH_CONFIG_MAIN

#include <iostream>

#include "catch.hpp"
#include "../CLI/include/Person.hpp"

TEST_CASE("Getters Person"){
    std::string fName = "Martin";
    std::string lName = "Simengard";

    enum gender{
        unknown,
        male,
        female
    };
    Person Martin = Person(fName, lName);

    REQUIRE(fName == Martin.getFirstName());
    REQUIRE(lName == Martin.getLastName());
}

TEST_CASE("Get _age"){
    std::string date = "22-06-1999";
    int actualAge = 23;

    Person person;
    person.setBirth(date);

    REQUIRE(person.getAge() == actualAge);
}

