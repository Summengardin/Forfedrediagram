#include "include/person.hpp"

Person::Person(const std::string &firstName, const std::string &lastName)
{
    setFirstName(firstName);
    setLastName(lastName);
}

Person::Person(const json &jsonFile)
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

json Person::toJson() const
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

const std::string &Person::getFirstName() const { return _firstName; }

const std::string &Person::getMiddleName() const { return _middleName; }

const std::string &Person::getLastName() const { return _lastName; }

std::string Person::getFullName() const
{
    std::ostringstream ssPerson;

    ssPerson << (_firstName.empty() ? "" : (_firstName + " "));
    ssPerson << (_middleName.empty() ? "" : (_middleName + " "));
    ssPerson << (_lastName.empty() ? "" : (_lastName));

    return ssPerson.str();
}

const Date &Person::getBirth() const { return _birth; }

const Date &Person::getDeath() const { return _death; }

int Person::getAge() const { return Date::yearsBetween(Date::today(), _birth); }

Person::GenderType Person::getGender() const { return _gender; }

std::string Person::getGenderString() const
{
    switch (_gender)
    {
    case male:
        return "male";
    case female:
        return "female";
    case other:
        return "other";
    default:
        return "unknown";
    }
}

bool Person::isAlive() const { return (!_isAlive); }

bool Person::contains(const std::string &str) const { return (getFullName().find(str) != std::string::npos); }

void Person::setFirstName(const std::string &firstName) { _firstName = firstName; }

void Person::setMiddleName(const std::string &middleName) { _middleName = middleName; }

void Person::setLastName(const std::string &lastName) { _lastName = lastName; }

void Person::setBirth(const std::string &birth) { _birth = Date(birth); }

void Person::setDeath(const std::string &death) { _death = Date(death); }

void Person::setGender(const std::string &gender)
{
    if (gender == "male")
        _gender = GenderType::male;
    else if (gender == "female")
        _gender = GenderType::female;
    else if (gender == "other")
        _gender = GenderType::other;
    else
        _gender = GenderType::unknown;
}

void Person::setAliveFlag(bool alive) { _isAlive = alive; }

bool Person::validateName(const std::string &str)
{
    std::string validLetters = "abcdefghijklmnopqrstuvwxyzæøåABCDEFGHIJKLMNOPQRSTUVWXYZÆØÅ ";

    bool checkAllLetters = std::all_of(str.begin(), str.end(),
                                       [&validLetters](char c) { return validLetters.find(c) != std::string::npos; });
    return checkAllLetters;
}

std::ostream &operator<<(std::ostream &os, const Person &p)
{
    if (p.getFullName().empty())
        os << "Empty person";
    else
        os << p.getFullName();

    return os;
}