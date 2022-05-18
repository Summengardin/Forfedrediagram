#pragma once // FORFEDREDIAGRAM_PERSON_HPP

#include <iostream>
#include <optional>
#include <regex>
#include <sstream>
#include <utility>
#include <variant>

//#include "atree/globals.hpp"
#include "date/date.hpp"
#include "helpers.hpp"
#include "json/json.hpp"

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


    Person(const std::string &firstName, const std::string &lastName)
        : Person(firstName, "", lastName, UNKNOWN, {00, 00, 0000}, {00, 00, 0000})
    {}


    Person(const std::string &firstName, const std::string &lastName, GenderType gender)
        : Person(firstName, "", lastName, gender, {00, 00, 0000}, {00, 00, 0000})
    {}


    Person(const std::string &firstName, const std::string &middleName, const std::string &lastName)
        : Person(firstName, middleName, lastName, UNKNOWN, {00, 00, 0000}, {00, 00, 0000})
    {}


    Person(const std::string &firstName, const std::string &middleName, const std::string &lastName, GenderType gender)
        : Person(firstName, middleName, lastName, gender, {00, 00, 0000}, {00, 00, 0000})
    {}


    Person(const std::string &firstName, const std::string &middleName, const std::string &lastName, Date birth)
        : Person(firstName, middleName, lastName, UNKNOWN, birth, {00, 00, 0000})
    {}


    Person(const std::string &firstName, const std::string &middleName, const std::string &lastName, GenderType gender,
           Date birth)
        : Person(firstName, middleName, lastName, gender, birth, {00, 00, 0000})
    {}


    Person(const std::string &firstName, const std::string &middleName, const std::string &lastName, Date birth,
           Date death)
        : Person(firstName, middleName, lastName, UNKNOWN, birth, death)
    {}


    Person(const std::string &firstName, const std::string &middleName, const std::string &lastName, GenderType gender,
           Date birth, Date death)
    {
        setFirstName(firstName);
        setMiddleName(middleName);
        setLastName(lastName);
        setGender(gender);
        setBirth(birth);
        setDeath(death);
    }


    explicit Person(const json &jsonFile) { this->fromJson(jsonFile); }


    void fromJson(const json &jsonFile)
    {
        if (jsonFile.contains("firstName") && jsonFile.at("firstName").is_string())
            _firstName = jsonFile.at("firstName");

        if (jsonFile.contains("middleName") && jsonFile.at("middleName").is_string())
            _middleName = jsonFile.at("middleName");

        if (jsonFile.contains("lastName") && jsonFile.at("lastName").is_string())
            _lastName = jsonFile.at("lastName");

        if (jsonFile.contains("gender") && jsonFile.at("gender").is_string())
        {
            std::string genderAsString = jsonFile.at("gender");
            setGender(genderAsString);
        }


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


    [[nodiscard]] unsigned int getAge() const
    {
        if (_death.isValid())
            return Date::calculateAge(_birth, _death);
        else if (_birth.isValid())
            return Date::calculateAge(_birth);

        return 0;
    }


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


    void setFirstName(const std::string &firstName)
    {
        if (validateName(firstName))
            _firstName = firstName;
    }


    void setMiddleName(const std::string &middleName)
    {
        if (validateName(middleName))
            _middleName = middleName;
    }


    void setLastName(const std::string &lastName)
    {
        if (validateName(lastName))
            _lastName = lastName;
    }


    void setBirth(const Date &birth)
    {
        if (!birth.isFutureDate() && birth.isValid())
            _birth = birth;
    }


    void setBirth(const std::string &birth) { setBirth(Date(birth)); }


    void setDeath(Date death)
    {
        _death = death;
        if (_death.isValid())
            setAliveFlag(_death.isFutureDate());
    }


    void setDeath(const std::string &death) { setDeath(Date(death)); }


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


    void setGender(GenderType gender) { _gender = gender; }


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
        os << "";
    else
        os << p.getFullName();

    return os;
}

// FORFEDREDIAGRAM_PERSON_HPP
