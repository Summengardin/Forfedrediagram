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


    static bool validateName(const std::string& str);


    friend std::ostream &operator<<(std::ostream &os, const Person &p);


    void setMiddleName(const std::string &middleName);


    void setGender(const std::string &gender);

private:
    std::string _firstName;
    std::string _middleName;
    std::string _lastName;
    Date _birth;
    Date _death;
    GenderType _gender{GenderType::unknown};
    bool _isDead{false};

};


//FORFEDREDIAGRAM_PERSON_HPP
