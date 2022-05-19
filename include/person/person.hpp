#pragma once // FORFEDREDIAGRAM_PERSON_HPP

#include <iostream>
#include <optional>
#include <regex>
#include <sstream>
#include <utility>
#include <variant>

#include "date/date.hpp"
#include "helpers.hpp"


class Person
{
  public:
    enum GenderType
    {
        MALE,
        FEMALE,
        OTHER,
        UNKNOWN
    };

    Person() = default;

    Person(const std::string &firstName, const std::string &lastName);

    Person(const std::string &firstName, const std::string &lastName, GenderType gender);

    Person(const std::string &firstName, const std::string &middleName, const std::string &lastName);

    Person(const std::string &firstName, const std::string &middleName, const std::string &lastName, GenderType gender);

    Person(const std::string &firstName, const std::string &middleName, const std::string &lastName, Date birth);

    Person(const std::string &firstName, const std::string &middleName, const std::string &lastName, GenderType gender,
           Date birth);

    Person(const std::string &firstName, const std::string &middleName, const std::string &lastName, Date birth,
           Date death);

    Person(const std::string &firstName, const std::string &middleName, const std::string &lastName, GenderType gender,
           Date birth, Date death);

    [[nodiscard]] const std::string &getFirstName() const;

    [[nodiscard]] const std::string &getMiddleName() const;

    [[nodiscard]] const std::string &getLastName() const;

    [[nodiscard]] std::string getFullName() const;

    [[nodiscard]] const Date &getBirth() const;

    [[nodiscard]] const Date &getDeath() const;

    [[nodiscard]] unsigned int getAge() const;

    [[nodiscard]] GenderType getGender() const;

    [[nodiscard]] std::string getGenderString() const;

    [[nodiscard]] bool isAlive() const;

    void setFirstName(const std::string &firstName);

    void setMiddleName(const std::string &middleName);

    void setLastName(const std::string &lastName);

    void setBirth(const Date &birth);

    void setBirth(const std::string &birth);

    void setDeath(Date death);

    void setDeath(const std::string &death);

    void setAliveFlag(bool alive);

    void setGender(const std::string &gender);

    void setGender(GenderType gender);

    static bool validateName(const std::string &str);

    friend std::ostream &operator<<(std::ostream &os, const Person &p);

  private:
    std::string _firstName;
    std::string _middleName;
    std::string _lastName;
    Date _birth;
    Date _death;
    GenderType _gender{GenderType::UNKNOWN};
    bool _isAlive{true};
};


std::ostream &operator<<(std::ostream &os, const Person &p)
{
    os << p.getFullName();
    return os;
}


Person::Person(const std::string &firstName, const std::string &lastName)
    : Person(firstName, "", lastName, UNKNOWN, {00, 00, 0000}, {00, 00, 0000})
{}


Person::Person(const std::string &firstName, const std::string &lastName, Person::GenderType gender)
    : Person(firstName, "", lastName, gender, {00, 00, 0000}, {00, 00, 0000})
{}


Person::Person(const std::string &firstName, const std::string &middleName, const std::string &lastName)
    : Person(firstName, middleName, lastName, UNKNOWN, {00, 00, 0000}, {00, 00, 0000})
{}


Person::Person(const std::string &firstName, const std::string &middleName, const std::string &lastName,
               Person::GenderType gender)
    : Person(firstName, middleName, lastName, gender, {00, 00, 0000}, {00, 00, 0000})
{}


Person::Person(const std::string &firstName, const std::string &middleName, const std::string &lastName, Date birth)
    : Person(firstName, middleName, lastName, UNKNOWN, birth, {00, 00, 0000})
{}


Person::Person(const std::string &firstName, const std::string &middleName, const std::string &lastName,
               Person::GenderType gender, Date birth)
    : Person(firstName, middleName, lastName, gender, birth, {00, 00, 0000})
{}


Person::Person(const std::string &firstName, const std::string &middleName, const std::string &lastName, Date birth,
               Date death)
    : Person(firstName, middleName, lastName, UNKNOWN, birth, death)
{}


Person::Person(const std::string &firstName, const std::string &middleName, const std::string &lastName,
               Person::GenderType gender, Date birth, Date death)
{
    setFirstName(firstName);
    setMiddleName(middleName);
    setLastName(lastName);
    setGender(gender);
    setBirth(birth);
    setDeath(death);
}


const std::string &Person::getFirstName() const
{
    return _firstName;
}


const std::string &Person::getMiddleName() const
{
    return _middleName;
}


const std::string &Person::getLastName() const
{
    return _lastName;
}


std::string Person::getFullName() const
{
    std::ostringstream ssPerson;

    ssPerson << (_firstName.empty() ? "" : (_firstName + " "));
    ssPerson << (_middleName.empty() ? "" : (_middleName + " "));
    ssPerson << (_lastName.empty() ? "" : (_lastName));

    return ssPerson.str();
}


const Date &Person::getBirth() const
{
    return _birth;
}


const Date &Person::getDeath() const
{
    return _death;
}


unsigned int Person::getAge() const
{
    if (_death.isValid())
        return Date::calculateAge(_birth, _death);
    else if (_birth.isValid())
        return Date::calculateAge(_birth);

    return 0;
}


Person::GenderType Person::getGender() const
{
    return _gender;
}


std::string Person::getGenderString() const
{
    switch (_gender)
    {
    case MALE:
        return "male";
    case FEMALE:
        return "female";
    case OTHER:
        return "other";
    default:
        return "unknown";
    }
}


bool Person::isAlive() const
{
    return _isAlive;
}


void Person::setFirstName(const std::string &firstName)
{
    if (validateName(firstName))
        throw std::invalid_argument("Invalid name. Names can only contain letters.");

    _firstName = firstName;
}


void Person::setMiddleName(const std::string &middleName)
{
    if (validateName(middleName))
        throw std::invalid_argument("Invalid name. Names can only contain letters.");

    _middleName = middleName;
}


void Person::setLastName(const std::string &lastName)
{
    if (validateName(lastName))
        throw std::invalid_argument("Invalid name. Names can only contain letters.");

    _lastName = lastName;
}


void Person::setBirth(const Date &birth)
{
    if (birth.isFutureDate())
        throw std::range_error("Not born yet.. Funny guy");

    if (!birth.isValid())
        throw std::invalid_argument("Invalid date passed as argument");

    _birth = birth;
}


void Person::setBirth(const std::string &birth)
{
    setBirth(Date(birth));
}


void Person::setDeath(Date death)
{
    if (death.isFutureDate())
        throw std::range_error("This application is not for murders. How would you know the persons day of death when "
                               "it has not happened...?");
    if (!death.isValid())
        throw std::invalid_argument("Invalid date passed as argument");

    _death = death;
    setAliveFlag(true);
}


void Person::setDeath(const std::string &death)
{
    setDeath(Date(death));
}


void Person::setAliveFlag(bool alive)
{
    _isAlive = alive;
    if (_isAlive)
        _death = {0, 0, 0};
}


void Person::setGender(const std::string &gender)
{
    if (gender == "male")
        _gender = MALE;
    else if (gender == "female")
        _gender = FEMALE;
    else if (gender == "other")
        _gender = OTHER;
    else
        _gender = UNKNOWN;
}


void Person::setGender(Person::GenderType gender)
{
    _gender = gender;
}


bool Person::validateName(const std::string &str)
{
    std::string validLetters = "abcdefghijklmnopqrstuvwxyzæøåABCDEFGHIJKLMNOPQRSTUVWXYZÆØÅ ";

    bool checkAllLetters = std::all_of(
        str.begin(), str.end(), [&validLetters](char c) { return validLetters.find(c) != std::string::npos; });
    return checkAllLetters;
}


// FORFEDREDIAGRAM_PERSON_HPP
