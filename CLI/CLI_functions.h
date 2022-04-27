#pragma once //FORFEDREDIAGRAM_CLI_FUNCTIONS_H

#include <iostream>
#include <memory>

#include "Menu.hpp"
#include "Node.hpp"
#include "Person.hpp"
#include "Tree.hpp"
#include "commonFunctions.hpp"

namespace CLI
{
    template<class T>
    void addPerson(Tree<T> &tree){

        // Generate the new person and create node with this person
        Person newPerson;
        // TODO Get edit function out of Person-class to separate CLI from API
        newPerson.edit();
        std::unique_ptr<Node<Person>> newNode = std::make_unique<Node<Person>>(newPerson);

        // Set new node as root if Tree has no root
        if (tree.isEmpty()) {
            tree.setRoot(std::move(newNode));
            return;
        }

        // Choose relation of new node
        std::cout << "Velg person dette er forelder til." << std::endl;
        auto name = COM::getString("Skriv navnet på barnet til personen:");
        std::vector<Node<Person> *> matchingNodes = tree.findNodeByString(name);

        int attemptCounter = 0;

        while (matchingNodes.empty()) {
            if(attemptCounter >= 2){
                std::cout << "Trenger du hjelp? Her er alle personene som finnes i treet:" << std::endl;
                tree.listOfNodes();
                attemptCounter = 0;
            } else{
                std::cout << "\nFant ingen person med navn \"" << name << "\"\n"
                          << "Prøv igjen:" << std::endl;

                attemptCounter++;
            }

            name = COM::getString("Skriv navnet på barnet til personen:");
            matchingNodes = tree.findNodeByString(name);
        }


        if (matchingNodes.size() == 1) {
            matchingNodes[0]->addParent(std::move(newNode));
        } else {
            // Creates new menu to choose between all matching Nodes with their data as text
            Node<Person> *parentNode;
            Menu matchesMenu;
            matchesMenu.setTitle("Velg person som skal være forelder");
            for (auto node: tree.findNodeByString(name)) {
                matchesMenu.append({node->getData()->getFullName() + " " +
                                            (node->getData()->getBirth().validate()
                                                     ? node->getData()->getBirth().toString() : ""),
                                    [&node, &parentNode]() {
                                        parentNode = node;
                                    }});
            }
            matchesMenu.show();

            parentNode->addParent(std::move(newNode));
        }

    }


    template<class T>
    void showPeople(Tree<T> &tree)
    {
        auto name = COM::getString("Skriv navnet på personen du ønsker å vise");
        std::vector<Node<Person> *> people = tree.findNodeByString(name);
        if (people.empty()) {
            std::cout << "Fant ingen personer med navn \"" << name << "\"" << std::endl;
        } else {
            for (auto &node: tree.findNodeByString(name)) {
                std::stringstream ssPerson;
                auto currentPerson = node->getData();

                // Name [index]
                ssPerson << "\n" << currentPerson->getFullName() << "[" << node->getIdx() << "]";
                // F: Birth - D: Death
                ssPerson << "\nF: " << currentPerson->getBirth().toString();
                ssPerson << (currentPerson->isAlive() ? "" : (" - D: " + currentPerson->getBirth().toString()));
                // Kjønn:
                ssPerson << "\nKjønn er ";
                switch (currentPerson->getGender())
                {
                    case Person::male:
                        ssPerson << "mann";
                        break;
                    case Person::female:
                        ssPerson << "kvinne";
                        break;
                    case Person::other:
                        ssPerson << "annet";
                        break;
                    case Person::unknown:
                        ssPerson << "ukjent";
                        break;
                }
                //Foreldre
                ssPerson << "\nForeldrene er\n";
                if(node->leftPtr() || node->rightPtr())
                {
                    if (node->leftPtr())
                        ssPerson << "   " << node->getLeft().getData()->getFullName() << "[" << node->leftPtr()->getIdx() << "]";
                    if (node->rightPtr())
                        ssPerson << "   " << node->getRight().getData()->getFullName() << "[" << node->rightPtr()->getIdx() << "]";
                } else
                    ssPerson << "... ikke lagret i vår database";

                std::cout << ssPerson.str() << "\n";
            }
        }
    }

    template<class T>
    void editPerson(Tree<T> &tree){

        // Choose person to edit
        auto name = COM::getString("Skriv navnet på personen du ønsker å redigere");
        std::vector<Node<Person> *> people = tree.findNodeByString(name);

        Person* personToEdit;
        if (people.empty()) {
            std::cout << "\nFant ingen person med navn \"" << name << "\"" << std::endl;
            return;
        } else if (people.size() == 1) {
            personToEdit = people[0]->getData();
        } else
        {
            // Creates new menu to choose between all people with name
            Menu peopleMenu;
            peopleMenu.setTitle("Velg person du ønsker å redigere");

            for (auto &node: tree.findNodeByString(name))
            {
                Person *currentPerson = node->getData();
                peopleMenu.append({currentPerson->getFullName() + " " +
                                           (currentPerson->getBirth().validate() ? currentPerson->getBirth().toString() : ""),
                                   [&personToEdit, &currentPerson]() {
                                       personToEdit = currentPerson;
                                   }});
            }
            peopleMenu.show();
        }
        // Edit person

        //TODO - Er det mulig å la brukeren ikke skrive inn igjen den nåværende verdien om den skal beholdes
        //TODO - Implementer sjekk av alle inputs

        auto firstName = COM::getString("Fornavn: ");
        while(!Person::validateName(firstName)){
            firstName = COM::getString("Bare tillat med bokstaver på navn [a-å], prøv igjen: ");
        }
        personToEdit->setFirstName(firstName);

        auto middleName = COM::getString("Mellomnavn: ", true);
        while(!Person::validateName(middleName)){
            middleName = COM::getString("Bare tillat med bokstaver på navn [a-å], prøv igjen: ");
        }
        personToEdit->setMiddleName(middleName);

        auto lastName = COM::getString("Etternavn: ");
        while(!Person::validateName(lastName)){
            lastName = COM::getString("Bare tillat med bokstaver på navn [a-å], prøv igjen: ");
        }
        personToEdit->setMiddleName(middleName);
        //_age = COM::getNum<unsigned int>("Alder?");

        auto birthAsString = COM::getString("Når ble " + firstName + " " + middleName + " født? [DD-MM-YYYY]: ");
        while(!Date::validateStringFormat(birthAsString)){
            birthAsString = COM::getString("Ikke en gyldig dato, må være [DD-MM-YYYY]. Prøv igjen: ");
        }
        personToEdit->setBirth(birthAsString);

        auto aliveAnswer = COM::getString("Er personen " + firstName + " " + middleName + " i live? (y/n)");
        while(aliveAnswer != "y" && aliveAnswer != "Y" && aliveAnswer != "n" && aliveAnswer != "N"){
            aliveAnswer = COM::getString("Du må nesten svare 'y' eller 'n'. Mer enn det forstår jeg ikke :/\nPrøv igjen: ");
        }
        if (aliveAnswer == "y" || aliveAnswer == "Y")
            personToEdit->isAlive(true);
        else if (aliveAnswer == "n" || aliveAnswer == "N")
            personToEdit->isAlive(false);

        if (personToEdit->isAlive()){
            auto deathAsString = COM::getString("Når døde " + firstName + " " + middleName + "? [DD-MM-YYYY]: ");
            while(!Date::validateStringFormat(deathAsString)){
                deathAsString = COM::getString("Ikke en gyldig dato, må være [DD-MM-YYYY]. Prøv igjen: ");
            }
            personToEdit->setDeath(deathAsString);
        }


    }

    template<class T>
    void loadTree(Tree<T> &tree){
        // Henter fil å lese fra (Kan byttes ut med input fra bruker)
        std::string fromFile = COM::getString("Skriv inn banen til filen (.json): ");
        std::optional<json> treeData;
        while (true) {

            if (!COM::fileExists(fromFile)) {
                fromFile = COM::getString(
                        "Beklager, kunne ikke finne filen.\nSkriv inn banen til filen (.json): ");
                continue;
            }

            treeData = COM::openFileAsJson(fromFile);

            if (!treeData) {
                fromFile = COM::getString("Filen må være av typen \".json\", prøv igjen:  ");
                continue;
            }
            break;
        }

        tree.fillFromJson(treeData.value());
        std::cout << "Treet er fylt opp med data" << std::endl;
    }


    template<class T>
    void saveTree(Tree<T> &tree){
        auto fileName = COM::getString("Skriv inn navn på fil:");
        std::ofstream outputFile(fileName);

        outputFile << tree.toJson().dump(4);
    }


    template<class T>
    void showTree(Tree<T> &tree){
        if (tree.isEmpty())
        {
            std::cout << "Treet er tomt :/" << std::endl;
            return;
        }

        int indent = 4;
        tree.getRoot().traverseDFSWithDepth([indent](Node<T> *node, int depth) {
            for (int i = 0; i < depth; ++i)
            {
                for (int space = 0; space < indent; ++space)
                {
                    std::cout << " ";
                }
            }
            /*            if (depth != 0)
            {
                for (int space = 0; space < indent; ++space)
                {
                    std::cout << " ";
                }
                std::cout << "";
            }*/
            std::cout << *node->viewData() << std::endl;
            //depth++;
        });
    }
}

//FORFEDREDIAGRAM_CLI_FUNCTIONS_H
