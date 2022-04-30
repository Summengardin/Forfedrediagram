#pragma once // FORFEDREDIAGRAM_PERSON_HPP

#include <iostream>
#include <sstream>
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

    explicit Person(const json &jsonFile);

    [[nodiscard]] json toJson() const;

    [[nodiscard]] const std::string &getFirstName() const;

    [[nodiscard]] const std::string &getMiddleName() const;

    [[nodiscard]] const std::string &getLastName() const;

    [[nodiscard]] std::string getFullName() const;

    [[nodiscard]] const Date &getBirth() const;

    [[nodiscard]] const Date &getDeath() const;

    [[nodiscard]] int getAge() const;

    [[nodiscard]] GenderType getGender() const;

    [[nodiscard]] std::string getGenderString() const;

    [[nodiscard]] bool isAlive() const;

    [[nodiscard]] bool contains(const std::string &str) const;

    void setFirstName(const std::string &firstName);

    void setMiddleName(const std::string &middleName);

    void setLastName(const std::string &lastName);

    void setBirth(const std::string &birth);

    void setDeath(const std::string &death);

    void setGender(const std::string &gender);

    void setAliveFlag(bool alive);

    static bool validateName(const std::string &str);

    friend std::ostream &operator<<(std::ostream &os, const Person &p);

  private:
    std::string _firstName;
    std::string _middleName;
    std::string _lastName;
    Date _birth;
    Date _death;
    GenderType _gender{GenderType::unknown};
    bool _isAlive{true};
};

// FORFEDREDIAGRAM_PERSON_HPP
