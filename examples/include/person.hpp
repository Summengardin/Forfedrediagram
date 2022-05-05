#pragma once // FORFEDREDIAGRAM_PERSON_HPP

#include <iostream>
#include <optional>
#include <regex>
#include <sstream>
#include <utility>
#include <variant>

#include "globals.hpp"
#include "helpers.hpp"
#include "json.hpp"

using json = nlohmann::json;

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

    Person(std::string firstName, std::string lastName)
        : _firstName(std::move(firstName)), _lastName(std::move(lastName))
    {
    }

    Person(std::string firstName, std::string middleName, std::string lastName)
        : _firstName(std::move(firstName)), _middleName(std::move(middleName)), _lastName(std::move(lastName))
    {
    }

    Person(std::string firstName, std::string middleName, std::string lastName, Date birth)
        : _firstName(std::move(firstName)), _middleName(std::move(middleName)), _lastName(std::move(lastName)),
          _birth(birth), _isAlive(true)
    {
    }

    Person(std::string firstName, std::string middleName, std::string lastName, Date birth, Date death)
        : _firstName(std::move(firstName)), _middleName(std::move(middleName)), _lastName(std::move(lastName)),
          _birth(birth), _death(death), _isAlive(false)
    {
    }

    explicit Person(const json &jsonFile)
    {
        if (jsonFile.contains("firstName") && jsonFile.at("firstName").is_string())
            _firstName = jsonFile.at("firstName");

        if (jsonFile.contains("middleName") && jsonFile.at("middleName").is_string())
            _middleName = jsonFile.at("middleName");

        if (jsonFile.contains("lastName") && jsonFile.at("lastName").is_string())
            _lastName = jsonFile.at("lastName");

        if (jsonFile.contains("gender") && jsonFile.at("gender").is_string())
            setGender(jsonFile.at("lastName"));

        if (jsonFile.contains("birth") && jsonFile.at("birth").is_string())
        {
            std::string birthStr = jsonFile["birth"];
            _birth = Date(birthStr);
        }

        if (jsonFile.contains("death") && jsonFile.at("death").is_string())
        {
            std::string deathStr = jsonFile["death"];
            _death = Date(deathStr);
        }

        if (jsonFile.contains("isAlive") && jsonFile.at("isAlive").is_boolean())
            _isAlive = jsonFile.at("isAlive");
    }

    [[nodiscard]] json toJson() const
    {
        // clang-format off
    json j = json{
                {"firstName", _firstName},
                {"lastName", _lastName},
                {"middleName", _middleName},
                {"birth", _birth.toString()},
                {"death", _death.toString()},
                {"gender", getGenderString()},
                {"isAlive", _isAlive}
            };
        // clang-format on
        return j;
    }

    [[nodiscard]] const std::string &getFirstName() const { return _firstName; }

    [[nodiscard]] const std::string &getMiddleName() const { return _middleName; }

    [[nodiscard]] const std::string &getLastName() const { return _lastName; }

    [[nodiscard]] std::string getFullName() const
    {
        std::ostringstream ssPerson;

        ssPerson << (_firstName.empty() ? "" : (_firstName + " "));
        ssPerson << (_middleName.empty() ? "" : (_middleName + " "));
        ssPerson << (_lastName.empty() ? "" : (_lastName));

        return ssPerson.str();
    }

    [[nodiscard]] const Date &getBirth() const { return _birth; }

    [[nodiscard]] const Date &getDeath() const { return _death; }

    [[nodiscard]] int getAge() const { return Date::yearsBetween(Date::today(), _birth); }

    [[nodiscard]] GenderType getGender() const { return _gender; }

    [[nodiscard]] std::string getGenderString() const
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

    [[nodiscard]] bool isAlive() const { return _isAlive; }

    [[nodiscard]] bool contains(const std::string &str) const { return (getFullName().find(str) != std::string::npos); }

    void setFirstName(const std::string &firstName) { _firstName = firstName; }

    void setMiddleName(const std::string &middleName) { _middleName = middleName; }

    void setLastName(const std::string &lastName) { _lastName = lastName; }

    void setBirth(const std::string &birth) { _birth = Date(birth); }

    void setBirth(Date birth) { _birth = birth; }

    void setDeath(const std::string &death) { _death = Date(death); }

    void setDeath(Date death) { _death = death; }

    void setGender(const std::string &gender)
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

    void setAliveFlag(bool alive) { _isAlive = alive; }

    static bool validateName(const std::string &str)
    {
        std::string validLetters = "abcdefghijklmnopqrstuvwxyzæøåABCDEFGHIJKLMNOPQRSTUVWXYZÆØÅ ";

        bool checkAllLetters = std::all_of(
            str.begin(), str.end(), [&validLetters](char c) { return validLetters.find(c) != std::string::npos; });
        return checkAllLetters;
    }

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
    if (p.getFullName().empty())
        os << "Empty person";
    else
        os << p.getFullName();

    return os;
}

// FORFEDREDIAGRAM_PERSON_HPP
