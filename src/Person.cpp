#include "Person.hpp"

std::ostream &operator<<(std::ostream &os, const Person &p)
{
    if (p.getFullName().empty())
    {
        os << "Empty person";
    } else
    {
        os << p.getFullName() << (p._isDead ? " \u2620" : " \u2665");
    }
    return os;
}


Person::Person(const std::string &firstName, const std::string &lastName)
{
    setFirstName(firstName);
    setLastName(lastName);
}


Person::Person(const json &j)
{
    if (j.contains("firstName") && j.at("firstName").is_string())
        _firstName = j.at("firstName");

    if (j.contains("middleName") && j.at("middleName").is_string())
        _middleName = j.at("middleName");

    if (j.contains("lastName") && j.at("lastName").is_string())
        _lastName = j.at("lastName");

    if (j.contains("birth") && j.at("birth").is_string())
    {
        std::string birthStr = j["birth"];
        _birth = Date(birthStr);
    } else
    {
        _birth = Date();
    }

    if (j.contains("gender") && j.at("gender").is_string())
        setGender( j.at("lastName"));

    if (j.contains("death") && j.at("death").is_string())
    {
        std::string birthStr = j["death"];
        _death = Date(birthStr);
    } else
    {
        _death = Date();
    }

    if (j.contains("isDead") && j.at("isDead").is_boolean())
        _isDead = j.at("isDead");
}


json Person::toJson() const
{
    json j = json{
            {"firstName", _firstName},
            {"lastName", _lastName},
            {"middleName", _middleName},
            {"birth", _birth.toString()},
            {"death", _death.toString()},
            {"gender", getGenderString()},
            {"isDeath", _isDead}};
    return j;
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
    return _firstName + " " + (_middleName.empty() ? "" : (_middleName + " ")) + _lastName;
}

bool Person::contains(const std::string &str) const
{
    //  std::vector<std::string> nameSplitted = COM::splitString(getFullName(), ' ');
    //  return (std::find( nameSplitted.begin(), nameSplitted.end(), str) != nameSplitted.end());

    return (getFullName().find(str) != std::string::npos);
}


const Date &Person::getBirth() const
{
    return _birth;
}


int Person::getAge() const
{
    return Date::yearsBetween(today(), _birth);
}

bool Person::isAlive() const
{
    return (!_isDead);
}

void Person::isAlive(bool alive)
{
    _isDead = (!alive);
}

void Person::setFirstName(const std::string &firstName)
{
    _firstName = firstName;
}

void Person::setMiddleName(const std::string &middleName)
{
    _middleName = middleName;
}

void Person::setLastName(const std::string &lastName)
{
    _lastName = lastName;
}


void Person::setBirth(const std::string &birth)
{
    _birth = Date(birth);
}

void Person::setDeath(const std::string &death)
{
    _death = Date(death);
}


bool Person::validateName(const std::string& str)
{
    std::string validLetters = "abcdefghijklmnopqrstuvwxyzæøåABCDEFGHIJKLMNOPQRSTUVWXYZÆØÅ ";

    bool result = std::all_of(str.begin(), str.end(), [&validLetters](char c){
        return validLetters.find(c) != std::string::npos;
    });

    return result;
}


std::string Person::getGenderString() const
{
    switch (_gender)
    {
        case male:
            return "male";
            break;
        case female:
            return "female";
            break;
        case other:
            return "other";
            break;
        case unknown:
            return "unknown";
            break;
    }
}


Person::GenderType Person::getGender() const
{
    return _gender;
}

void Person::setGender(const std::string& gender){
    if(gender == "male")
        _gender = GenderType::male;
    else if(gender == "female")
        _gender = GenderType::female;
    else if(gender == "other")
        _gender = GenderType::other;
    else
        _gender = GenderType::unknown;
}


