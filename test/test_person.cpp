//
// Created by Martin on 15.03.2022.
//

#define CATCH_CONFIG_MAIN

#include <iostream>

#include "catch.hpp"
#include "../src/Person.hpp"

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

TEST_CASE("Get age"){
    std::string date = "22-06-1999";
    int actualAge = 22;

    Person person;
    person.setBirth(date);

    REQUIRE(person.getAge() == actualAge);
}

