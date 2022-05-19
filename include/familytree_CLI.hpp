#pragma once // FORFEDREDIAGRAM_CLI_FUNCTIONS_H

#include <iostream>
#include <memory>

#include "atree/ancestor_tree.hpp"
#include "menu/menu.hpp"
#include "person/person.hpp"
#include "json/jsonParser.hpp"

namespace
{

void editPerson(Person &personToEdit, bool newPersonFlag = false)
{

    auto firstNamePrompt = "First name: " + (newPersonFlag ? "" : " (" + personToEdit.getFirstName() + ")");
    auto newFirstName = COM::getString(firstNamePrompt);
    while (!Person::validateName(newFirstName) && (newFirstName != "-"))
        newFirstName = COM::getString("Only letters [a-å] are allowed in names, try again: ");
    if (newFirstName != "-")
        personToEdit.setFirstName(newFirstName);


    auto newMiddleName = COM::getString("Middle name: (" + personToEdit.getMiddleName() + ")", true);
    while (!newMiddleName.empty() && !Person::validateName(newMiddleName) && (newMiddleName != "-"))
        newMiddleName = COM::getString("Only letters [a-å] are allowed in names, try again: ");
    if (newMiddleName != "-")
        personToEdit.setMiddleName(newMiddleName);


    auto newLastName = COM::getString("Last name: (" + personToEdit.getLastName() + ")");
    while (!Person::validateName(newLastName) && (newLastName != "-"))
        newLastName = COM::getString("Only letters [a-å] are allowed in names, try again: ");
    if (newLastName != "-")
        personToEdit.setLastName(newLastName);


    auto newGender = COM::getString("Gender (male, female, other): (" + personToEdit.getGenderString() + ")", true);
    if (newGender != "-")
        personToEdit.setGender(newGender);


    auto birthAsString = COM::getString("When was " + personToEdit.getFirstName() + " " + personToEdit.getMiddleName() +
                                            " born? [DD-MM-YYYY]: (" + personToEdit.getBirth().toString() + ")",
                                        true);
    while (!birthAsString.empty() && !Date::validateStringFormat(birthAsString) && (birthAsString != "-"))
        birthAsString = COM::getString("That was not a valid date, format must be [DD-MM-YYYY].\nTry again: ");
    if (birthAsString != "-")
        personToEdit.setBirth(birthAsString);


    auto aliveAnswer =
        COM::getString("Is " + personToEdit.getFirstName() + " " + personToEdit.getMiddleName() + " alive? (y/n)");
    while (aliveAnswer != "y" && aliveAnswer != "Y" && aliveAnswer != "n" && aliveAnswer != "N" && aliveAnswer != "-")
        aliveAnswer = COM::getString("You have to answer 'y', 'n' or '-'\nTry again: ");
    if (aliveAnswer == "y" || aliveAnswer == "Y")
        personToEdit.setAliveFlag(true);
    else if (aliveAnswer == "n" || aliveAnswer == "N")
    {
        personToEdit.setAliveFlag(false);

        auto deathAsString = COM::getString("When did " + personToEdit.getFirstName() + " " +
                                            personToEdit.getMiddleName() + " pass away? [DD-MM-YYYY]: ");
        while (!deathAsString.empty() && !Date::validateStringFormat(deathAsString) && (deathAsString != "-"))
        {
            deathAsString = COM::getString("That was not a valid date [DD-MM-YYYY].\nTry again: ");
        }
        if (deathAsString != "-")
            personToEdit.setDeath(deathAsString);
    }
}

void writeOutNode(ATree::Node<Person> *node)
{
    std::stringstream ssPerson;
    auto person = node->getData();

    // Name [index]
    ssPerson << "\n" << person->getFullName() << " [" << node->getIndex() << "]";
    // B: Birth
    auto birthValid = person->getBirth().isValid();
    if (birthValid)
        ssPerson << "\nB: " << person->getBirth().toString();
    // D: Death
    auto deathValid = person->getDeath().isValid();
    if (!person->isAlive() && deathValid)
        ssPerson << "\nD: " << person->getDeath().toString();
    // Gender:
    ssPerson << "\nGender is " << person->getGenderString();

    // Parents
    if (node->leftChild() || node->rightChild())
    {
        ssPerson << "\nParents are\n";
        if (node->leftChild())
            ssPerson << "   " << node->leftChild()->getData()->getFullName() << " [" << node->leftChild()->getIndex()
                     << "]";
        if (node->rightChild())
            ssPerson << "   " << node->rightChild()->getData()->getFullName() << " [" << node->rightChild()->getIndex()
                     << "]";
    }


    std::cout << ssPerson.str() << "\n";
}

} // namespace


void showTree(ATree::Tree<Person> &tree)
{
    if (tree.isEmpty())
    {
        std::cout << "The tree is empty, start filling it up" << std::endl;
        return;
    }

    int indent = tree.getSettingIndent();
    tree.traverseDFSWithDepth(tree.getRoot(), [indent](ATree::Node<Person> *node, int depth) {
        for (int i = 0; i < depth; ++i)
        {
            for (int space = 0; space < indent; ++space)
            {
                std::cout << " ";
            }
        }
        std::cout << *node->getData() << " [" << std::to_string(node->getIndex()) << "]" << std::endl;
    });

    std::cout << "Tree size : " << tree.getSize() << std::endl;
}


void showPeople(ATree::Tree<Person> &tree)
{
    auto name = COM::getString("Who would you like to get a detailed view of?");
    auto people = tree.findNodeByString(name);

    if (people.empty())
    {
        std::cout << "Could not find any person containing \"" << name << "\"" << std::endl;
        return;
    }
    else if (people.size() == 1)
    {
        writeOutNode(people[0]);
        return;
    }


    Menu sortModeSelection{
        "Found multiple people with your searh-term.\nHow would you sort the list?",
        {{"By index in tree",
          [&people]() {
              std::sort(people.begin(), people.end(), [](ATree::Node<Person> *n1, ATree::Node<Person> *n2) {
                  return n1->getIndex() < n2->getIndex();
              });
          }},
         {"By firstname",
          [&people]() {
              std::sort(people.begin(), people.end(), [](ATree::Node<Person> *n1, ATree::Node<Person> *n2) {
                  return n1->getData()->getFirstName() < n2->getData()->getFirstName();
              });
          }}},
        false};

    sortModeSelection.show();

    for (auto &node : people)
    {
        writeOutNode(node);
    }
}


void addPerson(ATree::Tree<Person> &tree)
{
    std::cout << "\n--- CREATE NEW PERSON ---\n" << std::endl;

    // Generate the new person and create node with this person
    Person newPerson;

    editPerson(newPerson, true);
    std::unique_ptr<ATree::Node<Person>> newNode = std::make_unique<ATree::Node<Person>>(newPerson);

    // Set new node as root if ATree::Tree has no root
    if (tree.isEmpty())
    {
        tree.setRoot(std::move(newNode));
        return;
    }

    // Choose relation of new node
    auto name = COM::getString("Skriv navnet på barnet til " + newPerson.getFirstName());
    std::vector<ATree::Node<Person> *> matchingNodes = tree.findNodeByString(name);

    int attemptCounter = 0;

    while (matchingNodes.empty())
    {
        if (attemptCounter >= 2)
        {
            std::cout << "Do you need help? Here are all people listed in the tree" << std::endl;
            for (const auto &node : tree.listAllNodes())
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
        ATree::Node<Person> *parentNode;
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


void removePerson(ATree::Tree<Person> &tree)
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
        tree.removeNode(matchingPeople[0]->getIndex());
    }
    else
    {
        // Creates new menu to choose between all people matching search-term
        Menu matchesSelection;
        matchesSelection.setTitle("There are multiple people with that name.\nPick the one you want to remove:");
        matchesSelection.setLoop(false);

        for (auto &node : matchingPeople)
        {
            std::cout << node->getIndex();
            Person *currentPerson = node->getData();
            auto personTitle = currentPerson->getFullName() + " " +
                               (currentPerson->getBirth().isValid() ? currentPerson->getBirth().toString() : "");
            matchesSelection.append(
                {personTitle, [&tree, &node]() { std::cout << tree.removeNode(node->getIndex()); }});
        }
        matchesSelection.show();
    }
}


void editPerson(ATree::Tree<Person> &tree)
{
    auto searchTerm = COM::getString("Type in name or tree-index of the person you want to edit");
    std::vector<ATree::Node<Person> *> matches;

    if (COM::isNumber(searchTerm))
        matches.push_back(tree.findNodeByIndex(std::stoi(searchTerm)));
    else
        matches = tree.findNodeByString(searchTerm);


    Person *personToEdit;
    if (matches.empty())
    {
        std::cout << "\nCould not find anyone with search-term \"" << searchTerm << "\"" << std::endl;
        return;
    }
    else if (matches.size() == 1)
    {
        personToEdit = matches[0]->getData();
    }
    else
    {
        // Creates new menu to choose between all people with searchTerm
        Menu matchesSelection;
        matchesSelection.setTitle("Found multiple people containing " + searchTerm + ".\nChoose which one:");

        for (auto &node : tree.findNodeByString(searchTerm))
        {
            Person *currentPerson = node->getData();
            auto personTitle = currentPerson->getFullName() + " " +
                               (currentPerson->getBirth().isValid() ? currentPerson->getBirth().toString() : "");
            matchesSelection.append({personTitle, [&personToEdit, &currentPerson]() { personToEdit = currentPerson; }});
        }
        matchesSelection.show();
    }

    // Edit person
    std::cout << "\n--- EDITING ---\n" << *personToEdit << "\n";
    std::cout << "\nFor every entry, \"-\" will leave value unchanged"
              << "\n";
    std::cout << "Values in parentheses is current value\n" << std::endl;
    editPerson(*personToEdit);
}


void loadTreeFromJson(ATree::Tree<Person> &tree)
{
    std::filesystem::path demoFile;

    Menu fileOptions{
        "For demo purposes we have provided you with an example file,\ndo you want to use that?",
        {{"Use demo file",
          [&demoFile]() { demoFile = std::filesystem::absolute(R"(..\..\test_files\hidden\FirstTree.json)"); }},
         {"Use anonymous file",
          [&demoFile]() { demoFile = std::filesystem::absolute(R"(..\..\test_files\AnonymTestData.json)"); }},
         {"Use other file", [&demoFile]() { demoFile = COM::getString("Type in full filepath (.json): "); }}},
        false};

    fileOptions.show();

    std::cout << demoFile << std::endl;

    while (true)
    {
        if (!exists(demoFile))
        {
            demoFile = COM::getString("Sorry, could not find the file\nCheck spelling: ");
            continue;
        }

        if (!JsonParser::isJson(demoFile))
        {
            demoFile = COM::getString("Filetype must be \".json\", try again:  ");
            continue;
        }

        break;
    }


    try
    {
        json treeData = JsonParser::jsonFromFile(demoFile);
        JsonParser::fromJson(treeData, tree);
        std::cout << "Tree is successfully loaded" << std::endl;
    }
    catch (const std::invalid_argument &error)
    {
        std::cout << "Woops, seems like that file was invalid.\nError message:" << error.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Sorry, unexpected error occurred. Could not build tree from that file" << std::endl;
    }
}


void saveTreeToJson(ATree::Tree<Person> &tree)
{
    std::filesystem::path fileName = COM::getString("Tree will be stored as a .json-file\nName of file:");

    while (fileName.has_extension() && fileName.extension() != ".json")
        fileName = COM::getString("Filename should be without extension or with .json-extension. Try again:");

    if (!fileName.has_extension())
        fileName += ".json";

    std::filesystem::path outputPath = std::filesystem::absolute("..\\Output");

    if (!exists(outputPath))
        std::filesystem::create_directories(outputPath);

    outputPath /= fileName;

    std::ofstream outputFile{outputPath};
    outputFile << JsonParser::toJson(tree).dump(4);

    std::cout << "\n" << fileName << " was saved\n";
    std::cout << "Located at: " << outputPath.string() << std::endl;
}


// FORFEDREDIAGRAM_CLI_FUNCTIONS_H
