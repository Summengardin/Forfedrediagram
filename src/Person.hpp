//
// Created by simen on 3/3/2022.
//

#ifndef FORFEDREDIAGRAM_PERSON_HPP
#define FORFEDREDIAGRAM_PERSON_HPP

#include <iostream>
#include <utility>

#include "../include/json.hpp"
#include "../include/UsefulFunctions.hpp"

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

    Person(const json &j)
    {
        if(j.at("firstName") != nullptr)
            setFirstName(j.at("firstName"));
        if(j.at("lastName") != nullptr)
            setLastName(j.at("lastName"));
        if(j.at("age") != nullptr)
            setAge(j.at("age"));
    }


    static Person generate()
    {
        std::cout << "Opprett ny person: " << std::endl;
        auto fName = MM::getUserInput<std::string>("Fornavn: ");
        auto lName = MM::getUserInput<std::string>("Fornavn: ");
        auto bday = MM::getUserInput<std::string>("Birthday [dd-mm-yyyy]: ");
        return Person{fName, lName};
    }

    [[nodiscard]] json toJson() const
    {
        json j = json{
                {"firstName", getFirstName()},
                {"lastName",  getLastName()},
                {"age",       getAge()}
        };
        return j;
    }

    static Person fromJson(const json &j)
    {
        Person p;
        if(j.at("firstName") != nullptr)
            p.setFirstName(j.at("firstName"));
        if(j.at("lastName") != nullptr)
            p.setLastName(j.at("lastName"));
        if(j.at("age") != nullptr)
            p.setAge(j.at("age"));

        return p;
    }

    // TODO - Person(std::string parsedLine)
    // Gjør det mulig å lage person fra en lang JSON-fil


    [[nodiscard]] std::string getFirstName() const
    {
        return _firstName;
    }


    [[nodiscard]] std::string getLastName() const
    {
        return _lastName;
    }


    [[nodiscard]] int getAge() const
    {
        return _age;
    }


    void setFirstName(const std::string &firstName)
    {
        _firstName = firstName;
    }


    void setLastName(const std::string &lastName)
    {
        _lastName = lastName;
    }


    void setAge(int age)
    {
        _age = age;
    }


    friend std::ostream &operator<<(std::ostream &os, const Person &p);

private:
    std::string _firstName;
    std::string _lastName;
    int _age = -1;
    //MM::Date _birthday;
};

std::ostream &operator<<(std::ostream &os, const Person &p)
{
    if (p.getFirstName().empty() and p.getLastName().empty())
    {
        os << "Empty person";
    } else
    {
        os << "[Person] Name: " << p.getFirstName() << " " << p.getLastName();
    }
    return os;
}

#endif //FORFEDREDIAGRAM_PERSON_HPP
