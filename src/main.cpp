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

    //Menu
    Menu mainMenu{"Hovedmeny",
                  {
                {"Vis tre", [&familyTree](){ familyTree.show(); } },

                {"Vis person(er)", [&familyTree](){
                    auto name = COM::getString("Skriv navnet på personen du ønsker å vise");
                    for (auto& node : familyTree.findNodeByString(name)){
                        node->getData().viewDetails();
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

