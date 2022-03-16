//
// Created by Martin on 15.03.2022.
//

#include <iostream>

#include "catch.hpp"
#include "../src/Person.hpp"

TEST_CASE("Get Person"){
    std::string fName = "Martin";
    std::string lName = "Simengard";
    int age = 22;
    Person Martin = Person(fName, lName, age);

    REQUIRE(fName == Martin.getFirstName());
    REQUIRE(lName == Martin.getLastName());
    REQUIRE(age == Martin.getAge());
}

