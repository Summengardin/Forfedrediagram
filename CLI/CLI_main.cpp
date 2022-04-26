#include <iostream>
#include <memory>


#include "Menu.hpp"
#include "Node.hpp"
#include "Person.hpp"
#include "Tree.hpp"
#include "commonFunctions.hpp"


int main() {

    Tree<Person> familyTree;

    // Generate menu with its functions
    Menu mainMenu{"HOVEDMENY",
                  // Show whole family-tree
                  {{"Vis tre", [&familyTree]() {
                        familyTree.show();
                    }},

                   // Show detailed view of desired people
                   {"Vis person(er)", [&familyTree]() {
                        auto name = COM::getString("Skriv navnet på personen du ønsker å vise");
                        std::vector<Node<Person> *> people = familyTree.findNodeByString(name);
                        if (people.empty()) {
                            std::cout << "Fant ingen personer med navn \"" << name << "\"" << std::endl;
                        } else {
                            for (auto &node: familyTree.findNodeByString(name)) {
                                node->getData()->viewDetails();
                            }
                        }
                    }},

                   // Add new peron to fanily-tree
                   {"Legg til person", [&familyTree]() {

                        // Generate the new person and create node with this person
                        Person newPerson;
                        // TODO Get edit function out of Person-class to separate CLI from API
                        newPerson.edit();
                        std::unique_ptr<Node<Person>> newNode = std::make_unique<Node<Person>>(newPerson);

                        // Set new node as root if Tree has no root
                        if (familyTree.isEmpty()) {
                            familyTree.setRoot(std::move(newNode));
                            return;
                        }

                        // Choose relation of new node
                        std::cout << "Velg person dette er forelder til." << std::endl;
                        auto name = COM::getString("Skriv navnet på barnet til personen:");
                        std::vector<Node<Person> *> matchingNodes = familyTree.findNodeByString(name);

                        int attemptCounter = 0;

                        while (matchingNodes.empty()) {
                            if(attemptCounter >= 2){
                                std::cout << "Trenger du hjelp? Her er alle personene som finnes i treet:" << std::endl;
                                familyTree.listOfNodes();
                                attemptCounter = 0;
                            } else{
                                std::cout << "\nFant ingen person med navn \"" << name << "\"\n"
                                          << "Prøv igjen:" << std::endl;

                                attemptCounter++;
                            }

                            name = COM::getString("Skriv navnet på barnet til personen:");
                            matchingNodes = familyTree.findNodeByString(name);
                        }


                        if (matchingNodes.size() == 1) {
                            matchingNodes[0]->addParent(std::move(newNode));
                        } else {
                            // Creates new menu to choose between all matching Nodes with their data as text
                            Node<Person> *parentNode;
                            Menu matchesMenu;
                            matchesMenu.setTitle("Velg person som skal være forelder");
                            for (auto node: familyTree.findNodeByString(name)) {
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

                    }},

                   {"Rediger person", [&familyTree]() {
                        auto name = COM::getString("Skriv navnet på personen du ønsker å redigere");
                        std::vector<Node<Person> *> people = familyTree.findNodeByString(name);

                        if (people.empty()) {
                            std::cout << "\nFant ingen person med navn \"" << name << "\"" << std::endl;
                        } else if (people.size() == 1) {
                            people[0]->getData()->edit();
                        } else {
                            // Creates new menu to choose between all people with name
                            Menu editPerson;
                            editPerson.setTitle("Velg person du ønsker å redigere");
                            for (auto &node: familyTree.findNodeByString(name)) {
                                Person *person = node->getData();
                                editPerson.append({person->getFullName() + " " +
                                                           (person->getBirth().validate() ? person->getBirth().toString() : ""),
                                                   [&person]() {
                                                       person->edit();
                                                   }});
                            }
                            editPerson.show();
                        }
                    }},

                   {"Last tre fra fil", [&familyTree]() {
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

                        familyTree.fillFromJson(treeData.value());
                        std::cout << "Treet er fylt opp med data" << std::endl;
                    }},

                   {"Lagre tre til fil", [&familyTree]() {
                        auto fileName = COM::getString("Skriv inn navn på fil:");
                        std::ofstream outputFile(fileName);

                        outputFile << familyTree.toJson().dump(4);
                    }}}};


    // Overskrift
    std::cout << "\n--------------------------------" << std::endl;
    std::cout << "|   Hello there family tree!   |" << std::endl;
    std::cout << "--------------------------------\n"
              << std::endl;
    std::cout << "\nI dag er det " << today().toString() << "," << std::endl;
    std::cout << "gjør det til en flott en!" << std::endl;

    mainMenu.show();

    return EXIT_SUCCESS;
}

