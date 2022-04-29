#pragma once // FORFEDREDIAGRAM_CLI_FUNCTIONS_H

#include <iostream>
#include <memory>

#include "Menu.hpp"
#include "Node.hpp"
#include "Person.hpp"
#include "Tree.hpp"
#include "commonFunctions.hpp"

namespace CLI
{
namespace
{
void editPerson(Person &personToEdit)
{

    // TODO - Er det mulig å la brukeren ikke skrive inn igjen den nåværende verdien om den skal beholdes
    // TODO - Implementer sjekk av alle inputs

    auto firstName = COM::getString("Fornavn: ");
    while (!Person::validateName(firstName))
    {
        firstName = COM::getString("Bare tillat med bokstaver på navn [a-å], prøv igjen: ");
    }
    personToEdit.setFirstName(firstName);

    auto middleName = COM::getString("Mellomnavn: ", true);
    while (!Person::validateName(middleName))
    {
        middleName = COM::getString("Bare tillat med bokstaver på navn [a-å], prøv igjen: ");
    }
    personToEdit.setMiddleName(middleName);

    auto lastName = COM::getString("Etternavn: ");
    while (!Person::validateName(lastName))
    {
        lastName = COM::getString("Bare tillat med bokstaver på navn [a-å], prøv igjen: ");
    }
    personToEdit.setLastName(lastName);

    auto gender = COM::getString("Kjønn: ", true);
    personToEdit.setGender(gender);

    auto birthAsString = COM::getString("Når ble " + firstName + " " + middleName + " født? [DD-MM-YYYY]: ", true);
    if (!birthAsString.empty())
    {
        while (!Date::validateStringFormat(birthAsString))
        {
            birthAsString = COM::getString("Ikke en gyldig dato, må være [DD-MM-YYYY]. Prøv igjen: ");
        }
        personToEdit.setBirth(birthAsString);
    }

    auto aliveAnswer = COM::getString("Er personen " + firstName + " " + middleName + " i live? (y/n)");
    while (aliveAnswer != "y" && aliveAnswer != "Y" && aliveAnswer != "n" && aliveAnswer != "N")
    {
        aliveAnswer = COM::getString("Du må nesten svare 'y' eller 'n'. Mer enn det forstår jeg ikke :/\nPrøv igjen: ");
    }
    if (aliveAnswer == "y" || aliveAnswer == "Y")
        personToEdit.setAliveness(true);
    else
    {
        personToEdit.setAliveness(false);

        auto deathAsString = COM::getString("Når døde " + firstName + " " + middleName + "? [DD-MM-YYYY]: ");
        while (!Date::validateStringFormat(deathAsString))
        {
            deathAsString = COM::getString("Ikke en gyldig dato, må være [DD-MM-YYYY]. Prøv igjen: ");
        }
        personToEdit.setDeath(deathAsString);
    }
}

} // namespace

void addPerson(Tree<Person> &tree)
{

    // Generate the new person and create node with this person
    Person newPerson;

    editPerson(newPerson);
    std::unique_ptr<Node<Person>> newNode = std::make_unique<Node<Person>>(newPerson);

    // Set new node as root if Tree has no root
    if (tree.isEmpty())
    {
        tree.setRoot(std::move(newNode));
        return;
    }

    // Choose relation of new node
    auto name = COM::getString("Skriv navnet på barnet til " + newPerson.getFirstName());
    std::vector<Node<Person> *> matchingNodes = tree.findNodeByString(name);

    int attemptCounter = 0;

    while (matchingNodes.empty())
    {
        if (attemptCounter >= 2)
        {
            std::cout << "Trenger du hjelp? Her er alle personene som finnes i treet:" << std::endl;
            tree.listOfNodes();
            attemptCounter = 0;
        }
        else
        {
            std::cout << "\nFant ingen person med navn \"" << name << "\"\n"
                      << "Prøv igjen:" << std::endl;

            attemptCounter++;
        }

        name = COM::getString("Skriv navnet på barnet til " + newPerson.getFirstName());
        matchingNodes = tree.findNodeByString(name);
    }

    if (matchingNodes.size() == 1)
    {
        matchingNodes[0]->addParent(std::move(newNode));
    }
    else
    {
        // Creates new menu to choose between all matching Nodes with their data as text
        Node<Person> *parentNode;
        Menu matchesMenu;
        matchesMenu.setTitle("Velg person som skal være forelder");
        for (auto node : tree.findNodeByString(name))
        {
            matchesMenu.append(
                {node->getData()->getFullName() + " " +
                     (node->getData()->getBirth().validate() ? node->getData()->getBirth().toString() : ""),
                 [&node, &parentNode]() { parentNode = node; }});
        }
        matchesMenu.show();

        parentNode->addParent(std::move(newNode));
    }
}

void removePerson(Tree<Person> &tree)
{
    // Choose person to remove
    auto searchTerm = COM::getString("Who would you like to remove from the tree?");
    auto matchingPeople = tree.findNodeByString(searchTerm);

    if (matchingPeople.empty())
    {
        std::cout << "\nCould not find any person containing \"" << searchTerm << "\"" << std::endl;
    }
    else if (matchingPeople.size() == 1)
    {
        tree.removeNode(matchingPeople[0]->getIdx());
    }
    else
    {
        // Creates new menu to choose between all people matching search-term
        Menu peopleMenu;
        peopleMenu.setTitle("There are multiple people with that name.\nPick the one you want to remove:");
        peopleMenu.setLoop(false);

        for (auto &node : matchingPeople)
        {
            std::cout << node->getIdx();
            Person *currentPerson = node->getData();
            auto personTitle = currentPerson->getFullName() + " " +
                               (currentPerson->getBirth().validate() ? currentPerson->getBirth().toString() : "");
            peopleMenu.append({personTitle, [&tree, &node]() { std::cout << tree.removeNode(node->getIdx()); }});
        }
        peopleMenu.show();
    }
}

void showPeople(Tree<Person> &tree)
{
    auto name = COM::getString("Who would you like to get a detailed view of?");
    auto people = tree.findNodeByString(name);

    if (people.empty())
    {
        std::cout << "Could not find any person containing \"" << name << "\"" << std::endl;
    }
    else
    {
        for (auto &node : people)
        {
            std::stringstream ssPerson;
            auto currentPerson = node->getData();

            // Name [index]
            ssPerson << "\n" << currentPerson->getFullName() << "[" << node->getIdx() << "]";
            // B: Birth - D: Death
            ssPerson << "\nB: " << currentPerson->getBirth().toString();
            ssPerson << (currentPerson->isAlive() ? "" : (" - D: " + currentPerson->getBirth().toString()));
            // Gender:
            ssPerson << "\nGender is " << currentPerson->getGenderString();

            // Parents
            ssPerson << "\nParents are\n";
            if (node->leftPtr() || node->rightPtr())
            {
                if (node->leftPtr())
                    ssPerson << "   " << node->getLeft().getData()->getFullName() << "[" << node->leftPtr()->getIdx()
                             << "]";
                if (node->rightPtr())
                    ssPerson << "   " << node->getRight().getData()->getFullName() << "[" << node->rightPtr()->getIdx()
                             << "]";
            }
            else
                ssPerson << "... not stored in this tree";

            std::cout << ssPerson.str() << "\n";
        }
    }
}

void editPerson(Tree<Person> &tree)
{

    // Choose person to edit
    auto searchTerm = COM::getString("Type in the searchTerm in of the person");
    std::vector<Node<Person> *> people = tree.findNodeByString(searchTerm);

    Person *personToEdit;
    if (people.empty())
    {
        std::cout << "\nCould not find anyone searchTerm \"" << searchTerm << "\"" << std::endl;
        return;
    }
    else if (people.size() == 1)
    {
        personToEdit = people[0]->getData();
    }
    else
    {
        // Creates new menu to choose between all people with searchTerm
        Menu peopleMenu;
        peopleMenu.setTitle("Found multiple people containing " + searchTerm + ".\nChoose which one:");

        for (auto &node : tree.findNodeByString(searchTerm))
        {
            Person *currentPerson = node->getData();
            auto personTitle = currentPerson->getFullName() + " " +
                               (currentPerson->getBirth().validate() ? currentPerson->getBirth().toString() : "");
            peopleMenu.append({personTitle, [&personToEdit, &currentPerson]() { personToEdit = currentPerson; }});
        }
        peopleMenu.show();
    }

    // Edit person
    editPerson(*personToEdit);
}

void loadTree(Tree<Person> &tree)
{
    // Henter fil å lese fra (Kan byttes ut med input fra bruker)
    std::string fromFile = COM::getString("Type in full filepath (.json): ");
    std::optional<json> treeData;
    while (true)
    {
        if (!COM::fileExists(fromFile))
        {
            fromFile = COM::getString("Sorry, could not find the file\nCheck spelling: ");
            continue;
        }

        treeData = COM::openFileAsJson(fromFile);

        if (!treeData)
        {
            fromFile = COM::getString("Filetype must be \".json\", try again:  ");
            continue;
        }
        break;
    }

    tree.fillFromJson(treeData.value());
    std::cout << "Tree is loaded" << std::endl;
}

void saveTree(Tree<Person> &tree)
{
    auto fileName = COM::getString("Name of file:");
    std::ofstream outputFile(fileName);

    outputFile << tree.toJson().dump(4);
}

void showTree(Tree<Person> &tree)
{
    if (tree.isEmpty())
    {
        std::cout << "The tree is empty, start filling it up" << std::endl;
        return;
    }

    int indent = 4;
    tree.getRoot().traverseDFSWithDepth([indent](Node<Person> *node, int depth) {
        for (int i = 0; i < depth; ++i)
        {
            for (int space = 0; space < indent; ++space)
            {
                std::cout << " ";
            }
        }
        std::cout << *node->viewData() << std::endl;
    });
}
} // namespace CLI

// FORFEDREDIAGRAM_CLI_FUNCTIONS_H
