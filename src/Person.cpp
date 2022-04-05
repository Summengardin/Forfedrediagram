#include "Person.hpp"

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


Person::Person(std::string &firstName, std::string &lastName) {
    setFirstName(firstName);
    setLastName(lastName);
}


Person::Person(const json &j) {
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


json Person::toJson() const {
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

const std::string &Person::getFirstName() const {
    return _firstName;
}


Person Person::generate() {
    Person p;
    std::cout << "Opprett ny person: " << std::endl;
    p.edit();
    return p;
}

const std::string &Person::getMiddleName() const {
    return _middleName;
}

const std::string &Person::getLastName() const {
    return _lastName;
}

std::string Person::getFullName() const {
    return _firstName + " " + (_middleName.empty() ? "" : (_middleName + " ")) + _lastName;
}

bool Person::contains(const std::string &str) const {
    //  std::vector<std::string> nameSplitted = COM::splitString(getFullName(), ' ');
    //  return (std::find( nameSplitted.begin(), nameSplitted.end(), str) != nameSplitted.end());

    return ( getFullName().find(str) != std::string::npos );

}


const Date &Person::getBirth() const {
    return _birth;
}


int Person::getAge() const {
    return Date::yearsBetween(today(), _birth);
}


void Person::setFirstName(const std::string &firstName) {
    _firstName = firstName;
}


void Person::setLastName(const std::string &lastName) {
    _lastName = lastName;
}


void Person::setBirth(const std::string &birth) {
    _birth = Date(birth);
}


void Person::edit() {
    _firstName = COM::getString("Fornavn: ");
    _middleName = COM::getString("Mellomnavn: ");
    _lastName = COM::getString("Etternavn: ");
    _birth = Date(COM::getString("Når ble " + _firstName + " " + _middleName + " født? [DD-MM-YYYY]: "));
    auto aliveAnswer = COM::getString("Er personen " + _firstName + " " + _middleName + " i live? (y/n)");
    if(aliveAnswer == "y" or aliveAnswer == "Y")
        _isDead = false;
    else if (aliveAnswer == "n" or aliveAnswer == "N")
        _isDead = true;
    if(_isDead)
        _birth = Date(COM::getString("Når døde personen? [DD-MM-YYYY]: "));
}


void Person::viewDetails() {
    std::cout << "[Person]:\n"
              <<  getFullName() <<  ",\n"
              << (_birth.isValid() ? ("F: " + _birth.toString()) : "Bursdag ligger ikke i systemet.")
              << ((_isDead) ? ( _death.isValid() ? "  -  D: " + _death.toString() : "\nDødsdato ligger ikke i systemet.") : "")
              << std::endl;
}



