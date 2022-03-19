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
        _data["firstName"] = firstName;
        _data["lastName"] = lastName;
    };


    // TODO - Person(std::string parsedLine)
    // Gjør det mulig å lage person fra en lang tekststreng med data

    [[nodiscard]] std::string getFirstName () const {
        return _data["firstName"];
    }

    [[nodiscard]] std::string getLastName () const {
        return _data["lastName"];
    }

    [[nodiscard]] int getAge () const {
        return _data["getAge"];
    }

    friend std::ostream& operator <<(std::ostream& os, const Person& p);

private:
    int treeID;
    json _data;
};

 std::ostream& operator<<(std::ostream& os, const Person& p){
    os << "[Person] Name: " << p.getFirstName() << " " << p.getLastName();
    return os;
}

#endif //FORFEDREDIAGRAM_PERSON_HPP
