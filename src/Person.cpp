#include "Person.hpp"

std::ostream &operator<<(std::ostream &os, const Person &p)
{
    if (p.getFullName().empty())
    {
        os << "Empty person";
    } else
    {
        os << "[Person] Name: " << p.getFullName() << (p._isDead ? " \u2620" : " \u2665");
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
    if (j.contains("firstName") and j.at("firstName").is_string())
        _firstName = j.at("firstName");

    if (j.contains("middleName") and j.at("middleName").is_string())
        _middleName = j.at("middleName");

    if (j.contains("lastName") and j.at("lastName").is_string())
        _lastName = j.at("lastName");

    if (j.contains("birth") and j.at("birth").is_string())
    {
        std::string birthStr = j["birth"];
        _birth = Date(birthStr);
    } else
    {
        _birth = Date();
    }

    if (j.contains("_age") and j.at("_age").is_string())
        _age = j.at("_age");

    if (j.contains("death") and j.at("death").is_string())
    {
        std::string birthStr = j["death"];
        _death = Date(birthStr);
    } else
    {
        _death = Date();
    }

    if (j.contains("isDead") and j.at("isDead").is_boolean())
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
            {"age", _age},
            {"isDeath", _isDead}};
    return j;
}

const std::string &Person::getFirstName() const
{
    return _firstName;
}


Person Person::generate()
{
    Person p;
    std::cout << "Opprett ny person: " << std::endl;
    p.edit();
    return p;
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
    return !_isDead;
}

void Person::setFirstName(const std::string &firstName)
{
    _firstName = firstName;
}


void Person::setLastName(const std::string &lastName)
{
    _lastName = lastName;
}


void Person::setBirth(const std::string &birth)
{
    _birth = Date(birth);
}


void Person::edit()
{
    //TODO - Er det mulig å la brukeren ikke skrive inn igjen den nåværende verdien om den skal beholdes
    //TODO - Implementer sjekk av alle inputs

    _firstName = COM::getString("Fornavn: ");
    while(!Person::validateName(_firstName)){
        _firstName = COM::getString("Bare tillat med bokstaver på navn [a-å], prøv igjen: ");
    }

    _middleName = COM::getString("Mellomnavn: ", true);
    while(!Person::validateName(_middleName)){
        _middleName = COM::getString("Bare tillat med bokstaver på navn [a-å], prøv igjen: ");
    }

    _lastName = COM::getString("Etternavn: ");
    while(!Person::validateName(_lastName)){
        _lastName = COM::getString("Bare tillat med bokstaver på navn [a-å], prøv igjen: ");
    }
    //_age = COM::getNum<unsigned int>("Alder?");

    auto birthAsString = COM::getString("Når ble " + _firstName + " " + _middleName + " født? [DD-MM-YYYY]: ");
    while(!Date::validateStringFormat(birthAsString)){
        birthAsString = COM::getString("Ikke en gyldig dato, må være [DD-MM-YYYY]. Prøv igjen: ");
    }
    _birth = Date(birthAsString);

    auto aliveAnswer = COM::getString("Er personen " + _firstName + " " + _middleName + " i live? (y/n)");
    while(aliveAnswer != "y" and aliveAnswer != "Y" and aliveAnswer != "n" and aliveAnswer != "N"){
        aliveAnswer = COM::getString("Du må nesten svare 'y' eller 'n'. Mer enn det forstår jeg ikke :/\nPrøv igjen: ");
    }
    if (aliveAnswer == "y" or aliveAnswer == "Y")
        _isDead = false;
    else if (aliveAnswer == "n" or aliveAnswer == "N")
        _isDead = true;
    if (_isDead){
        auto deathAsString = COM::getString("Når døde " + _firstName + " " + _middleName + "? [DD-MM-YYYY]: ");
        while(!Date::validateStringFormat(deathAsString)){
            deathAsString = COM::getString("Ikke en gyldig dato, må være [DD-MM-YYYY]. Prøv igjen: ");
        }
        _death = Date(deathAsString);
    }
}


void Person::viewDetails()
{
    std::cout << "[Person]:\n"
              << getFullName() << ",\n"
              << "Alder: " << _age << "år\n"
              << (_birth.validate() ? ("F: " + _birth.toString()) : "Bursdag ligger ikke i systemet.")
              << ((_isDead) ? (_death.validate() ? "  -  D: " + _death.toString() : "\nDødsdato ligger ikke i systemet.") : "")
              << std::endl;
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
