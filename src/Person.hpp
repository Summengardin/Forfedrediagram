#ifndef FORFEDREDIAGRAM_PERSON_HPP
#define FORFEDREDIAGRAM_PERSON_HPP

#include <iostream>
#include <utility>
#include <variant>
#include <optional>
#include <regex>

#include "../include/json.hpp"
#include "../include/commonFunctions.hpp"
#include "globals.hpp"

using json = nlohmann::json;

class Person
{
private:
    enum GenderType{
        male,
        female,
        trans
    };


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

        if(j.contains("birth") and j.at("birth").is_string()){
            std::string birthStr = j["birth"];
            _birth = Date(birthStr);
        } else{
            _birth = Date();
        }

        if(j.contains("death") and j.at("death").is_string()){
            std::string birthStr = j["death"];
            _death = Date(birthStr);
        } else{
            _death = Date();
        }

        if(j.contains("isDead") and j.at("isDead").is_boolean())
            _isDead = j.at("isDead");
    }


    static Person generate()
    {
        Person p;
        std::cout << "Opprett ny person: " << std::endl;
        p._firstName = COM::getString("Fornavn: ");
        p._middleName = COM::getString("Mellomnavn: ");
        p._lastName = COM::getString("Etternavn: ");
        p._birth = Date(COM::getString("Bursdag [DD-MM-YYYY]: "));
        return p;
    }


    [[nodiscard]] json toJson() const
    {
        json j = json{
                {"firstName", _firstName},
                {"lastName", _lastName},
                {"middleName", _middleName},
                {"birth", _birth.toString()},
                {"death", _death.toString()},
                {"isDeath", _isDead}
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
      //  std::vector<std::string> nameSplitted = COM::splitString(getFullName(), ' ');
      //  return (std::find( nameSplitted.begin(), nameSplitted.end(), str) != nameSplitted.end());

        return ( getFullName().find(str) != std::string::npos );

    }


    [[nodiscard]] const Date& getBirth() const
    {
        return _birth;
    }


    [[nodiscard]] int getAge() const{
        return Date::yearsBetween(today(), _birth);
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
        _birth = Date(birth);
    }


    void edit(){
        std::cout << "Editing " << getFullName() << std::endl;
    }


    void viewDetails(){
        std::cout << "[Person]:\n"
        <<  getFullName() <<  ",\n"
        << (_birth.isValid() ? ("F: " + _birth.toString()) : "Bursdag ligger ikke i systemet.")
        << ((_isDead) ? ( _death.isValid() ? "  -  D: " + _death.toString() : "\nDødsdato ligger ikke i systemet.") : "")
        << std::endl;
    }


    friend std::ostream &operator<<(std::ostream &os, const Person &p);


private:



    std::string _firstName;
    std::string _middleName;
    std::string _lastName;
    Date _birth;
    Date _death;
    GenderType gender;
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
