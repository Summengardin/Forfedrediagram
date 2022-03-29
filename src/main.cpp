#include <iostream>
#include <memory>



#include "Node.hpp"
#include "Person.hpp"
#include "Tree.hpp"
#include "../include/date.hpp"
#include "../include/commonFunctions.hpp"
#include "../include/menu.hpp"


int main(){

    Tree familyTree;
    Menu editPerson{ "Rediger person",
                     {
        {"Martin Simengard", [](){std::cout << "Rediger han Martin" << std::endl;}},
        {"Ho mor", [](){std::cout << "Rediger ho mor" << std::endl;}}
                     }
    };
    //Menu
    Menu mainMenu{"HOVEDMENY",
                  {
                {"Vis tre", [&familyTree](){ familyTree.show(); } },

                {"Vis person(er)", [&familyTree](){
                    auto name = COM::getString("Skriv navnet på personen du ønsker å vise");
                    for (auto& node : familyTree.findNodeByString(name)){
                        node->getData().viewDetails();
                    }
                }},

                {"Rediger person", [&familyTree](){
                    auto name = COM::getString("Skriv navnet på personen du ønsker å redigere");
                    std::vector<Node*> people = familyTree.findNodeByString(name);

                    if(people.empty()){
                        std::cout << "\nFant ingen person med navn " << name << std::endl;
                    } else if(people.size() == 1){
                        people[0]->getData().edit();
                    } else {
                        // Creates new menu to choose between all people with name
                        Menu editPerson;
                        for (auto &node: familyTree.findNodeByString(name)) {
                            Person& person = node->getData();
                            editPerson.append({
                                person.getFullName() + " " + (person.getBirth().isValid() ? person.getBirth().toString() : "")
                                , [&person]() {
                                person.edit();
                            }});
                        }
                        editPerson.show();
                    }

                }},

                {"Last tre fra fil", [&familyTree](){
                    // Henter fil å lese fra (Kan byttes ut med input fra bruker)
                    std::string fromFile{"../test/test_files/FirstTree.json"};
                    std::ifstream jsonFile(fromFile);

                    // Henter ut filen som et JSON-objekt
                    json treeData;
                    jsonFile >> treeData;

                    familyTree.fillFromJson(treeData);

                    std::cout << "Treet er fylt opp med data" << std::endl;
                }},

                {"Lagre tre til fil", [&familyTree](){
                    auto fileName = COM::getString("Skriv inn navn på fil:");
                    std::ofstream outputFile (fileName);

                    outputFile << familyTree.toJson().dump(4);
                }}
            }
    };


    std::cout << "Today it is " << today().toString() << std::endl;

    // Overskrift
    std::cout << "\n--------------------------------" << std::endl;
    std::cout <<   "|   Hello there family tree!   |" << std::endl;
    std::cout <<   "--------------------------------\n" << std::endl;

    mainMenu.show();

    return EXIT_SUCCESS;
}

