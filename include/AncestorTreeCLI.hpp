#pragma once // FORFEDREDIAGRAM_CLI_FUNCTIONS_H

#include <iostream>
#include <memory>

#include "atree/AncestorTree.hpp"
#include "menu/Menu.hpp"
#include "person/Person.hpp"
#include "json/JsonParser.hpp"

namespace
{

void editPerson(Person &personToEdit, bool newPersonFlag = false)
{

    auto firstNamePrompt = "First name: " + (newPersonFlag ? "" : "(" + personToEdit.getFirstName() + ")");
    auto newFirstName = COM::getString(firstNamePrompt);
    while (!Person::nameIsValid(newFirstName) && (newFirstName != "-"))
        newFirstName = COM::getString("Only letters [a-å] are allowed in names, try again: ");
    if (newFirstName != "-")
        personToEdit.setFirstName(newFirstName);

    auto middleNamePrompt = "Middle name: " + (newPersonFlag ? "" : "(" + personToEdit.getMiddleName() + ")");
    auto newMiddleName = COM::getString(middleNamePrompt, true);
    while (!newMiddleName.empty() && !Person::nameIsValid(newMiddleName) && (newMiddleName != "-"))
        newMiddleName = COM::getString("Only letters [a-å] are allowed in names, try again: ");
    if (newMiddleName != "-")
        personToEdit.setMiddleName(newMiddleName);

    auto lastNamePrompt = "Last name: " + (newPersonFlag ? "" : "(" + personToEdit.getLastName() + ")");
    auto newLastName = COM::getString(lastNamePrompt);
    while (!Person::nameIsValid(newLastName) && (newLastName != "-"))
        newLastName = COM::getString("Only letters [a-å] are allowed in names, try again: ");
    if (newLastName != "-")
        personToEdit.setLastName(newLastName);

    auto genderPrompt =
        "Gender(male, female or other): " + (newPersonFlag ? "" : "(" + personToEdit.getGenderString() + ")");
    auto newGender = COM::getString(genderPrompt, true);
    while (newGender != "male" && newGender != "female" && newGender != "other" && !newGender.empty() &&
           !(!newPersonFlag && newGender != "-"))
        newGender = COM::getString("That was not a valid gender. \nTry again:");
    if (newGender != "-")
        personToEdit.setGender(newGender);


    auto birthPrompt = "When was " + personToEdit.getFirstName() +
                       " born? [DD-MM-YYYY]: " + (newPersonFlag ? "" : "(" + personToEdit.getBirth().toString() + ")");
    auto birthAsString = COM::getString(birthPrompt, true);
    while (true)
    {
        if (birthAsString == "-")
            break;

        Date newBirth;
        if (birthAsString.empty())
            break;

        if (Date::validateStringFormat(birthAsString))
            newBirth.setDate(birthAsString);

        if (newBirth.isReal() || newBirth.isFutureDate())
        {
            personToEdit.setBirth(newBirth);
            break;
        }
        birthAsString = COM::getString(
            "That was not a valid date, format must be [DD-MM-YYYY] and not a future date.\nTry again: ", true);
    }


    auto aliveAnswer =
        COM::getString("Is " + personToEdit.getFirstName() + " " + personToEdit.getMiddleName() + " alive? (y/n)");
    while (aliveAnswer != "y" && aliveAnswer != "Y" && aliveAnswer != "n" && aliveAnswer != "N" && aliveAnswer != "-")
        aliveAnswer = COM::getString("You have to answer 'y', 'n' or '-'\nTry again: ");
    if (aliveAnswer == "y" || aliveAnswer == "Y")
        personToEdit.setAliveFlag(true);
    else if (aliveAnswer == "n" || aliveAnswer == "N")
    {
        personToEdit.setAliveFlag(false);

        auto deathPrompt = "When did " + personToEdit.getFirstName() + " die? [DD-MM-YYYY]: " +
                           (newPersonFlag ? "" : "(" + personToEdit.getDeath().toString() + ")");
        auto deathAsString = COM::getString(deathPrompt, true);
        while (true)
        {
            if (deathAsString == "-")
                break;

            Date newDeath;
            if (deathAsString.empty())
                break;

            if (Date::validateStringFormat(deathAsString))
                newDeath.setDate(deathAsString);

            if ((newDeath.isReal() || !newDeath.isFutureDate()) && (personToEdit.getBirth() <= newDeath))
            {
                personToEdit.setDeath(newDeath);
                break;
            }
            deathAsString = COM::getString("That was not a valid date, format must be [DD-MM-YYYY], not a future date, "
                                           "and death can of course not come before birth.\nTry again: ",
                                           true);
        }
    }
}

void writeOutNode(ATree::Node<Person> *node)
{
    std::stringstream ssPerson;
    auto person = node->getData();
    auto birthValid = person->getBirth().isReal();
    auto deathValid = person->getDeath().isReal();

    // Name [index]
    ssPerson << "\n" << person->getFullName() << " [" << node->getIndex() << "]";
    // Age: ##
    if ((birthValid && person->isAlive()) || (birthValid && (!person->isAlive() && deathValid)))
        ssPerson << "\nAge: " << person->getAge();
    // B: Birth
    if (birthValid)
        ssPerson << "\nB: " << person->getBirth().toString();
    // D: Death
    if (!person->isAlive() && deathValid)
        ssPerson << "\nD: " << person->getDeath().toString();
    // Gender:
    if (person->getGender() != Person::UNKNOWN)
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

    if (tree.isEmpty())
    {
        tree.setRoot(std::move(newNode));
        return;
    }

    // Choose relation of new node
    auto name = COM::getString("Name of child to " + newPerson.getFirstName());
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
            std::cout << "\nCould not find anyone with that name \"" << name << "\"\n"
                      << "Try again:" << std::endl;

            attemptCounter++;
        }

        name = COM::getString("Name of child of " + newPerson.getFirstName());
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
        matchesMenu.setLoop(false);
        matchesMenu.setTitle("Choose what person who should be parent");
        for (auto node : tree.findNodeByString(name))
        {
            matchesMenu.append(
                {node->getData()->getFullName() + " " +
                     (!node->getData()->getBirth().isNull() ? node->getData()->getBirth().toString() : ""),
                 [node, &parentNode]() { parentNode = node; }});
        }
        matchesMenu.show();

        try
        {
            parentNode->addChild(std::move(newNode));
        }
        catch (std::range_error &error)
        {
            std::cout << "Failed to add parent.\nError message: " << error.what() << std::endl;
        }
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
                               (!currentPerson->getBirth().isNull() ? currentPerson->getBirth().toString() : "");
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
    {
        auto match = tree.findNodeByIndex(std::stoi(searchTerm));
        if (match)
            matches.emplace_back(match);
    }
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
                               (!currentPerson->getBirth().isNull() ? currentPerson->getBirth().toString() : "");
            matchesSelection.append({personTitle, [&personToEdit, currentPerson]() { personToEdit = currentPerson; }});
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
    std::filesystem::path demoFile = std::filesystem::absolute(R"(..\..\test_files\AnonymTestData.json)");

    std::filesystem::path fileToOpen;

    Menu fileOptions{
        "For demo purposes we have provided you with an example file,\ndo you want to use that?",
        {{"Use demo file", [&demoFile, &fileToOpen]() { fileToOpen = demoFile; }},
         {"Use other file", [&fileToOpen]() { fileToOpen = COM::getString("Type in full filepath (.json): "); }}},
        false};

    fileOptions.show();

    std::cout << fileToOpen << std::endl;

    while (true)
    {
        if (!exists(fileToOpen))
        {
            fileToOpen = COM::getString("Sorry, could not find the file\nCheck spelling: ");
            continue;
        }

        if (!JsonParser::isJson(fileToOpen))
        {
            fileToOpen = COM::getString("Filetype must be \".json\", try again:  ");
            continue;
        }
        break;
    }

    try
    {
        json treeData = JsonParser::jsonFromFile(fileToOpen);
        JsonParser::fromJson(treeData, tree);
        std::cout << "Tree is successfully loaded" << std::endl;
    }
    catch (const std::invalid_argument &error)
    {
        std::cout << "Woops, seems like that file was invalid.\nError message: " << error.what() << std::endl;
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
