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
    


public:
    
    
    enum GenderType
    {
        male,
        female,
        other,
        unknown
    };
    
    
    Person() = default;


    Person(const std::string &firstName, const std::string &lastName);


    explicit Person(const json &j);


    static Person generate();


    [[nodiscard]] json toJson() const;


    [[nodiscard]] const std::string &getFirstName() const;


    [[nodiscard]] const std::string &getMiddleName() const;


    [[nodiscard]] const std::string &getLastName() const;


    [[nodiscard]] std::string getFullName() const;


    [[nodiscard]] std::string getGenderString() const;


    [[nodiscard]] const Date &getBirth() const;


    [[nodiscard]] int getAge() const;


    [[nodiscard]] GenderType getGender() const;


    [[nodiscard]] bool isAlive() const;


    void isAlive(bool alive);
    
    
    [[nodiscard]] bool contains(const std::string &str) const;
    

    void setFirstName(const std::string &firstName);


    void setLastName(const std::string &lastName);


    void setBirth(const std::string &birth);


    void setDeath(const std::string &death);


    void edit();


    void viewDetails();


    static bool validateName(const std::string& str);


    friend std::ostream &operator<<(std::ostream &os, const Person &p);


    void setMiddleName(const std::string &middleName);

private:
    std::string _firstName;
    std::string _middleName;
    std::string _lastName;
    Date _birth;
    Date _death;
    unsigned int _age = 0;
    GenderType _gender;
    bool _isDead{false};
};


//FORFEDREDIAGRAM_PERSON_HPP
