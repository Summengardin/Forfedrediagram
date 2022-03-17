//
// Created by Martin on 15.03.2022.
//

#include <iostream>

#include "catch.hpp"
#include "../src/Person.hpp"

TEST_CASE("Getters Person"){
    std::string fName = "Martin";
    std::string lName = "Simengard";
    int age = 22;
    enum gender{
        unknown,
        male,
        female
    };
    Person Martin = Person(fName, lName, age);

    REQUIRE(fName == Martin.getFirstName());
    REQUIRE(lName == Martin.getLastName());
    REQUIRE(age == Martin.getAge());
}

