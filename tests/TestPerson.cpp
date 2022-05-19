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
    bPerson.setFirstName("12Gunnar");
    cPerson.setFirstName("12Gunna!%%r");
    dPerson.setFirstName("");
    CHECK("Simen" == aPerson.getFirstName());
    CHECK("12Gunnar" != bPerson.getFirstName());
    CHECK("12Gunna!%%r" != cPerson.getFirstName());
    CHECK("" == dPerson.getFirstName());


    // Middle name
    aPerson.setMiddleName("Simmo");
    bPerson.setMiddleName("13Millo");
    cPerson.setMiddleName("Gille!%%r");
    dPerson.setMiddleName("");
    CHECK("Simmo" == aPerson.getMiddleName());
    CHECK("13Millo" != bPerson.getMiddleName());
    CHECK("Gille!%%r" != cPerson.getMiddleName());
    CHECK("" == dPerson.getMiddleName());


    // Last name
    aPerson.setLastName("Simensen");
    bPerson.setLastName("1400Greroiud");
    cPerson.setLastName("Gires!%%r");
    dPerson.setLastName("");
    CHECK("Simensen" == aPerson.getLastName());
    CHECK("1400Greroiud" != bPerson.getLastName());
    CHECK("Gires!%%r" != cPerson.getLastName());
    CHECK("" == dPerson.getLastName());


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
    bPerson.setBirth("22-06-99");
    cPerson.setBirth(Date{2, 5, 2024});
    dPerson.setBirth(Date{23, 9, 2011});
    CHECK("22-06-1999" == aPerson.getBirth().toString());
    CHECK("22-06-99" != bPerson.getBirth().toString());
    CHECK("02-05-2024" != cPerson.getBirth().toString());
    CHECK("23-09-2011" == dPerson.getBirth().toString());


    // Death
    aPerson.setDeath("22-06-2099");
    bPerson.setDeath("22-06-99");
    cPerson.setDeath(Date{2, 5, 2024});
    dPerson.setDeath(Date{23, 9, 2019});
    CHECK(Date{22, 6, 2099} == aPerson.getDeath());
    CHECK(Date{22, 6, 99} != bPerson.getDeath());
    CHECK(Date{2, 5, 2024} == cPerson.getDeath());
    CHECK(Date{23, 9, 2019} == dPerson.getDeath());

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
