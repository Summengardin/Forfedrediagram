#ifndef FORFEDREDIAGRAM_PERSON_HPP
#define FORFEDREDIAGRAM_PERSON_HPP

#include <iostream>
#include <utility>
#include <variant>
#include <optional>

#include "../include/json.hpp"
#include "../include/commonFunctions.hpp"

using json = nlohmann::json;

class Person
{
public:
    Person() = default;

    Person(std::string &firstName, std::string &lastName)
    {
        setFirstName(firstName);
        setLastName(lastName);
    }

    explicit Person(const json &j)
    {
        if(j.contains("firstName") and j.at("firstName").is_string())
            _firstName = j.at("firstName");
        if(j.contains("middleName") and j.at("middleName").is_string())
            _middleName = j.at("middleName");
        if(j.contains("lastName") and j.at("lastName").is_string())
            _lastName = j.at("lastName");
        if(j.contains("birth") and j.at("birth").is_string())
            _birth = j.at("birth");
        if(j.contains("death") and j.at("death").is_string())
            _death = j.at("death");
        if(j.contains("isDead") and j.at("isDead").is_boolean())
            _isDead = j.at("isDead");
    }


    static Person generate()
    {
        std::cout << "Opprett ny person: " << std::endl;
        auto fName = COM::getUserInput<std::string>("Fornavn: ");
        auto lName = COM::getUserInput<std::string>("Fornavn: ");
        auto bday = COM::getUserInput<std::string>("Birthday [DD-MM-YYYY]: ");
        return Person{fName, lName};
    }

    [[nodiscard]] json toJson() const
    {
        json j = json{
                {"firstName", _firstName},
                {"lastName",  _lastName},
                {"birth",     _birth},
                {"death",     nullptr},
                {"isDeath",   _isDead}

        };
        return j;
    }


    [[nodiscard]] const std::string& getFirstName() const
    {
        return _firstName;
    }


    [[nodiscard]] const std::string& getMiddleName() const
    {
        return _middleName;
    }


    [[nodiscard]] const std::string& getLastName() const
    {
        return _lastName;
    }

    [[nodiscard]] std::string getFullName() const
    {
        return _firstName + " " + (_middleName.empty() ? "" : (_middleName + " ")) + _lastName;
    }


    [[nodiscard]] bool contains (const std::string& str) const{
        std::vector<std::string> nameSplitted = COM::splitString(getFullName(), ' ');
        return (std::find( nameSplitted.begin(), nameSplitted.end(), str) != nameSplitted.end());
    }


    [[nodiscard]] const std::string& getBirth() const
    {
        return _birth;
    }


    void setFirstName(const std::string &firstName)
    {
        _firstName = firstName;
    }


    void setLastName(const std::string &lastName)
    {
        _lastName = lastName;
    }


    void setBirth(const std::string& birth)
    {
        _birth = birth;
    }

    void viewDetails(){
        std::cout << "[Person]:\n"
        << "Full name: " << getFullName() <<  "\n"
        << "Was born on " << _birth << std::endl;
    }


    friend std::ostream &operator<<(std::ostream &os, const Person &p);

private:
    std::string _firstName;
    std::string _middleName;
    std::string _lastName;
    std::string _birth;
    std::string _death;
    bool _isDead{false};
    //COM::Date _birthday;
};

std::ostream &operator<<(std::ostream &os, const Person &p)
{
    if (p.getFullName().empty())
    {
        os << "Empty person";
    } else
    {
        os << "[Person] Name: " << p.getFullName() << (p._isDead ?  " \u2620" : " \u2665");
    }
    return os;
}

#endif //FORFEDREDIAGRAM_PERSON_HPP
