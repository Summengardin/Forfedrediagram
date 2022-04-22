#include <iostream>
#include <memory>


#include "Menu.hpp"
#include "Node.hpp"
#include "Person.hpp"
#include "Tree.hpp"
#include "commonFunctions.hpp"


int main() {

    Tree<Person> familyTree;

    //Menu
    Menu mainMenu{"HOVEDMENY",
                  {{"Vis tre", [&familyTree]() {
                      familyTree.show();
                  }},

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

                   {"Legg til person", [&familyTree]() {

                       Person newPerson;
                       newPerson.edit();
                       std::unique_ptr<Node<Person>> newNode = std::make_unique<Node<Person>>(newPerson);

                       if (familyTree.isEmpty()) {
                           familyTree.setRoot(std::move(newNode));
                           return;
                       }

                       std::cout << "Velg person dette er forelder til." << std::endl;
                       auto name = COM::getString("Skriv navnet på barnet til personen:");
                       std::vector<Node<Person> *> matchingNodes = familyTree.findNodeByString(name);

                       int faultCounter = 0;

                       while (matchingNodes.empty()) {
                           if(faultCounter >= 2){
                               std::cout << "Trenger du hjelp? Her er personene som finnes i treet:" << std::endl;
                               familyTree.listNodes();
                               faultCounter = 0;
                           } else{
                               std::cout << "\nFant ingen person med navn \"" << name << "\"\n"
                                         << "Prøv igjen:" << std::endl;

                               faultCounter++;
                           }

                           name = COM::getString("Skriv navnet på barnet til personen:");

                           matchingNodes = familyTree.findNodeByString(name);
                       }

                       if (matchingNodes.size() == 1) {
                           matchingNodes[0]->addParent(std::move(newNode));
                       } else {
                           // Creates new menu to choose between all matchingNodes with name
                           Node<Person> *parentNode;
                           Menu matchesMenu;
                           matchesMenu.setTitle("Velg person som skal være forelder");
                           for (auto node: familyTree.findNodeByString(name)) {
                               matchesMenu.append({node->getData()->getFullName() + " " +
                                                   (node->getData()->getBirth().isValid()
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
                                                  (person->getBirth().isValid() ? person->getBirth().toString() : ""),
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
