#pragma once// FORFEDREDIAGRAM_PERSON_HPP


#include <iostream>
#include <optional>
#include <regex>
#include <utility>
#include <variant>

#include "commonFunctions.hpp"
#include "globals.hpp"
#include "json.hpp"


using json = nlohmann::json;

class Person
{
private:
    //TODO Genders
    enum GenderType
    {
        male,
        female,
    };


public:
    Person() = default;


    Person(std::string &firstName, std::string &lastName);


    explicit Person(const json &j);


    static Person generate();


    [[nodiscard]] json toJson() const;


    [[nodiscard]] const std::string &getFirstName() const;


    [[nodiscard]] const std::string &getMiddleName() const;


    [[nodiscard]] const std::string &getLastName() const;


    [[nodiscard]] std::string getFullName() const;


    [[nodiscard]] bool contains(const std::string &str) const;


    [[nodiscard]] const Date &getBirth() const;


    [[nodiscard]] int getAge() const;


    void setFirstName(const std::string &firstName);


    void setLastName(const std::string &lastName);


    void setBirth(const std::string &birth);


    void edit();


    void viewDetails();


    friend std::ostream &operator<<(std::ostream &os, const Person &p);


private:
    std::string _firstName;
    std::string _middleName;
    std::string _lastName;
    Date _birth;
    Date _death;
    unsigned int _age = 0;
    GenderType gender;
    bool _isDead{false};
    //COM::Date _birthday;
};


//FORFEDREDIAGRAM_PERSON_HPP
