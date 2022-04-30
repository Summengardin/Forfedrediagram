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
    std::cout << "\n--- EDITING ---\n" << personToEdit << std::endl;

    std::cout << "\nFor every entry, \"-\" will leave value unchanged" << std::endl;

    auto newFirstName = COM::getString("First name: ");
    while (!Person::validateName(newFirstName) && (newFirstName != "-"))
        newFirstName = COM::getString("Bare tillat med bokstaver på navn [a-å], prøv igjen: ");
    if (newFirstName != "-")
        personToEdit.setFirstName(newFirstName);

    auto newMiddleName = COM::getString("Middle name: ", true);
    while (!newMiddleName.empty() && !Person::validateName(newMiddleName) && (newMiddleName != "-"))
        newMiddleName = COM::getString("Bare tillat med bokstaver på navn [a-å], prøv igjen: ");
    if (newMiddleName != "-")
        personToEdit.setMiddleName(newMiddleName);

    auto newLastName = COM::getString("Last name: ");
    while (!Person::validateName(newLastName) && (newLastName != "-"))
        newLastName = COM::getString("Bare tillat med bokstaver på navn [a-å], prøv igjen: ");
    if (newLastName != "-")
        personToEdit.setLastName(newLastName);

    auto newGender = COM::getString("Gender (male, female, other): ", true);
    if (newGender != "-")
        personToEdit.setGender(newGender);

    auto birthAsString =
        COM::getString("When was " + personToEdit.getFirstName() + " " + personToEdit.getMiddleName() + " born? [DD-MM-YYYY]: ", true);
    while (!birthAsString.empty() && !Date::validateStringFormat(birthAsString) && (birthAsString != "-"))
        birthAsString = COM::getString("That was not a valid date, format must be [DD-MM-YYYY].\nTry again: ");
    if (birthAsString != "-")
        personToEdit.setBirth(birthAsString);

    auto aliveAnswer = COM::getString("Is " + personToEdit.getFirstName() + " " + personToEdit.getMiddleName() + " alive? (y/n)");
    while (aliveAnswer != "y" && aliveAnswer != "Y" && aliveAnswer != "n" && aliveAnswer != "N" && aliveAnswer != "-")
        aliveAnswer = COM::getString("You have to answer 'y', 'n' or '-'\nTry again: ");
    if (aliveAnswer == "y" || aliveAnswer == "Y")
        personToEdit.setAliveFlag(true);
    else if (aliveAnswer == "n" && aliveAnswer == "N")
    {
        personToEdit.setAliveFlag(false);

        auto deathAsString =
            COM::getString("When did " + personToEdit.getFirstName() + " " + personToEdit.getMiddleName() + " pass away? [DD-MM-YYYY]: ");
        while (!deathAsString.empty() && !Date::validateStringFormat(deathAsString) && (deathAsString != "-"))
        {
            deathAsString = COM::getString("That was not a valid date [DD-MM-YYYY]. Prøv igjen: ");
        }
        if (deathAsString != "-")
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
            std::cout << "Do you need help? Here are all people listed in the tree" << std::endl;
            for (const auto &node : tree.listOfNodes())
            {
                std::cout << *node->getData() << std::endl;
            }
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
        matchingNodes[0]->addChild(std::move(newNode));
    }
    else
    {
        // Creates new menu to choose between all matching Nodes with their _data as text
        Node<Person> *parentNode;
        Menu matchesMenu;
        matchesMenu.setTitle("Velg person som skal være forelder");
        for (auto node : tree.findNodeByString(name))
        {
            matchesMenu.append(
                {node->getData()->getFullName() + " " +
                     (node->getData()->getBirth().isValid() ? node->getData()->getBirth().toString() : ""),
                 [&node, &parentNode]() { parentNode = node; }});
        }
        matchesMenu.show();

        parentNode->addChild(std::move(newNode));
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
                               (currentPerson->getBirth().isValid() ? currentPerson->getBirth().toString() : "");
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
            ssPerson << "\n" << currentPerson->getFullName() << " [" << node->getIdx() << "]";
            // B: Birth
            auto birthValid = currentPerson->getBirth().isValid();
            if (birthValid)
                ssPerson << "\nB: " << currentPerson->getBirth().toString();
            // D: Death
            auto deathValid = currentPerson->getDeath().isValid();
            if (!currentPerson->isAlive() && deathValid)
                ssPerson << "\nD: " << currentPerson->getDeath().toString();
            // Gender:
            ssPerson << "\nGender is " << currentPerson->getGenderString();

            // Parents
            ssPerson << "\nParents are\n";
            if (node->leftChild() || node->rightChild())
            {
                if (node->leftChild())
                    ssPerson << "   " << node->getLeft().getData()->getFullName() << " [" << node->leftChild()->getIdx()
                             << "]";
                if (node->rightChild())
                    ssPerson << "   " << node->getRight().getData()->getFullName() << " [" << node->rightChild()->getIdx()
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
    auto searchTerm = COM::getString("Type in name of the person you want to edit");
    std::vector<Node<Person> *> people = tree.findNodeByString(searchTerm);

    Person *personToEdit;
    if (people.empty())
    {
        std::cout << "\nCould not find anyone with search-term \"" << searchTerm << "\"" << std::endl;
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
                               (currentPerson->getBirth().isValid() ? currentPerson->getBirth().toString() : "");
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
