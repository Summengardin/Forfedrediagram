//
// Created by simen on 3/3/2022.
//

#ifndef FORFEDREDIAGRAM_PERSON_HPP
#define FORFEDREDIAGRAM_PERSON_HPP

#include <iostream>
#include <utility>

#include "../nlohmann/json.hpp"

using json = nlohmann::json;

class Person
{
public:
    Person(std::string& firstName, std::string& lastName)
    {
        setFirstName(firstName);
        setLastName(lastName);
    };

    Person(json& j){
        fromJson(j);
    }

    [[nodiscard]] json toJson() const {
       json j = json{
            {"firstName", getFirstName()},
            {"lastName", getLastName()},
            {"age", getAge()}
        };
       return j;
    }

    void fromJson(const json& j) {
        setFirstName(j.at("firstName"));
        setLastName(j.at("lastName"));
        setAge(j.at("age"));
    }

    // TODO - Person(std::string parsedLine)
    // Gjør det mulig å lage person fra en lang JSON-fil

    [[nodiscard]] std::string getFirstName () const {
        return _firstName;
    }

    [[nodiscard]] std::string getLastName () const {
        return _lastName;
    }

    [[nodiscard]] int getAge () const {
        return _age;
    }

    void setFirstName(const std::string& firstName){
        _firstName = firstName;
    }

    void setLastName(const std::string& lastName){
        _lastName = lastName;
    }

    void setAge(int age){
        _age = age;
    }

    friend std::ostream& operator <<(std::ostream& os, const Person& p);

private:
    int _treeID;
    std::string _firstName;
    std::string _lastName;
    int _age;
};

 std::ostream& operator<<(std::ostream& os, const Person& p){
    os << "[Person] Name: " << p.getFirstName() << " " << p.getLastName();
    return os;
}

#endif //FORFEDREDIAGRAM_PERSON_HPP
