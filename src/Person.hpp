//
// Created by simen on 3/3/2022.
//

#ifndef FORFEDREDIAGRAM_PERSON_HPP
#define FORFEDREDIAGRAM_PERSON_HPP

#include <iostream>
#include <utility>

class Person
{
public:
    Person(std::string& firstName, std::string& lastName) :
            Person(firstName, lastName, 0)
    {};
    Person(std::string& firstName, std::string& lastName, int age) :
            _firstName(firstName),
            _lastName(lastName),
            _age(age)
    {};

    [[nodiscard]] std::string getFirstName () const {
        return _firstName;
    }

    [[nodiscard]] std::string getLastName () const {
        return _lastName;
    }

    [[nodiscard]] int getAge () const {
        return _age;
    }

    friend std::ostream& operator <<(std::ostream& os, const Person& p);

private:
    std::string _firstName;
    std::string _lastName;
    int _age = -1;
};

 std::ostream& operator<<(std::ostream& os, const Person& p){
    os << "[Person] Name: " << p._firstName << " " << p._lastName;
    return os;
}

#endif //FORFEDREDIAGRAM_PERSON_HPP
