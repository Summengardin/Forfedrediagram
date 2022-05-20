#define CATCH_CONFIG_MAIN

#include <iostream>

#include "catch.hpp"
#include "person/Person.hpp"

TEST_CASE("Constructors")
{
    std::string firstName = "For";
    std::string middleName = "Mellom";
    std::string lastName = "Etter";
    Person::GenderType gender = Person::MALE;
    Date birth{22, 06, 1999};
    Date death{22, 06, 2015};

    Person aPerson{firstName, lastName};
    Person bPerson{firstName, lastName, gender};
    Person cPerson{firstName, middleName, lastName};
    Person dPerson{firstName, middleName, lastName, gender};
    Person ePerson{firstName, middleName, lastName, birth};
    Person fPerson{firstName, middleName, lastName, gender, birth};
    Person gPerson{firstName, middleName, lastName, birth, death};
    Person hPerson{firstName, middleName, lastName, gender, birth, death};

    // First name , Last name
    CHECK(firstName == aPerson.getFirstName());
    CHECK(lastName == aPerson.getLastName());

    // First name , Last name , Gender
    CHECK(firstName == bPerson.getFirstName());
    CHECK(lastName == bPerson.getLastName());
    CHECK(gender == bPerson.getGender());

    // First name , Middle name , Last name
    CHECK(firstName == cPerson.getFirstName());
    CHECK(middleName == cPerson.getMiddleName());
    CHECK(lastName == cPerson.getLastName());

    // First name , Middle name , Last name , Gender
    CHECK(firstName == dPerson.getFirstName());
    CHECK(middleName == dPerson.getMiddleName());
    CHECK(lastName == dPerson.getLastName());
    CHECK(gender == dPerson.getGender());

    // First name , Middle name , Last name , Birth
    CHECK(firstName == ePerson.getFirstName());
    CHECK(middleName == ePerson.getMiddleName());
    CHECK(lastName == ePerson.getLastName());
    CHECK(birth == ePerson.getBirth());
    CHECK(ePerson.isAlive());

    // First name , Middle name , Last name , Gender, Birth
    CHECK(firstName == fPerson.getFirstName());
    CHECK(middleName == fPerson.getMiddleName());
    CHECK(lastName == fPerson.getLastName());
    CHECK(gender == fPerson.getGender());
    CHECK(birth == fPerson.getBirth());
    CHECK(fPerson.isAlive());

    // First name , Middle name , Last name , Birth, Death
    CHECK(firstName == gPerson.getFirstName());
    CHECK(middleName == gPerson.getMiddleName());
    CHECK(lastName == gPerson.getLastName());
    CHECK(birth == gPerson.getBirth());
    CHECK(death == gPerson.getDeath());
    CHECK(!gPerson.isAlive());

    // First name , Middle name , Last name , Gender , Birth , Death
    CHECK(firstName == hPerson.getFirstName());
    CHECK(middleName == hPerson.getMiddleName());
    CHECK(lastName == hPerson.getLastName());
    CHECK(gender == hPerson.getGender());
    CHECK(birth == hPerson.getBirth());
    CHECK(death == hPerson.getDeath());
    CHECK(!hPerson.isAlive());
}

TEST_CASE("Setters and Getters")
{
    Person aPerson;
    Person bPerson;
    Person cPerson;
    Person dPerson;


    // First name
    aPerson.setFirstName("Simen");
    dPerson.setFirstName("");
    REQUIRE("Simen" == aPerson.getFirstName());
    REQUIRE(dPerson.getFirstName().empty());
    REQUIRE_THROWS(bPerson.setFirstName("12Gunnar"));
    REQUIRE_THROWS(cPerson.setFirstName("12Gunna!%%r"));


    // Middle name
    aPerson.setMiddleName("Simmo");
    dPerson.setMiddleName("");
    REQUIRE("Simmo" == aPerson.getMiddleName());
    REQUIRE(dPerson.getMiddleName().empty());
    REQUIRE_THROWS(bPerson.setMiddleName("13Millo"));
    REQUIRE_THROWS(cPerson.setMiddleName("Gille!%%r"));


    // Last name
    aPerson.setLastName("Simensen");
    dPerson.setLastName("");
    REQUIRE("Simensen" == aPerson.getLastName());
    REQUIRE(dPerson.getLastName().empty());
    REQUIRE_THROWS(bPerson.setLastName("1400Greroiud"));
    REQUIRE_THROWS(cPerson.setLastName("Gires!%%r"));


    // Gender
    aPerson.setGender("male");
    bPerson.setGender("KLAME");
    cPerson.setGender(Person::FEMALE);
    dPerson.setGender("other");
    CHECK("male" == aPerson.getGenderString());
    CHECK(Person::MALE == aPerson.getGender());
    CHECK("unknown" == bPerson.getGenderString());
    CHECK(Person::UNKNOWN == bPerson.getGender());
    CHECK("female" == cPerson.getGenderString());
    CHECK(Person::FEMALE == cPerson.getGender());
    CHECK("other" == dPerson.getGenderString());
    CHECK(Person::OTHER == dPerson.getGender());


    // Birth
    aPerson.setBirth("22-06-1999");
    dPerson.setBirth(Date{23, 9, 2011});
    REQUIRE("22-06-1999" == aPerson.getBirth().toString());
    REQUIRE("23-09-2011" == dPerson.getBirth().toString());
    REQUIRE_THROWS(bPerson.setBirth("22-06-99"));
    REQUIRE_THROWS(cPerson.setBirth(Date{2, 5, 2024}));


    // Death
    aPerson.setDeath("15-08-2015");
    dPerson.setDeath(Date{23, 9, 2019});
    REQUIRE(Date{15, 8, 2015} == aPerson.getDeath());
    REQUIRE(Date{23, 9, 2019} == dPerson.getDeath());
    REQUIRE_THROWS(bPerson.setDeath("22-06-99"));
    REQUIRE_THROWS(cPerson.setDeath(Date{2, 5, 2024}));


    // Age
    aPerson.setBirth("22-06-1999");
    bPerson.setBirth("02-03-1980");
    cPerson.setBirth(Date{12, 5, 2011});
    dPerson.setBirth(Date{24, 12, 1});
    aPerson.setDeath("00-00-0000");
    bPerson.setDeath("00-00-0000");
    cPerson.setDeath("04-02-2019");
    dPerson.setDeath(Date{14, 8, 2018});
    CHECK(22 == aPerson.getAge());
    CHECK(42 == bPerson.getAge());
    CHECK(7 == cPerson.getAge());
    CHECK(2016 == dPerson.getAge());
}
