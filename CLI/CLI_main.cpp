#include <iostream>
#include <memory>


#include "CLI_functions.h"
#include "Menu.hpp"
#include "Node.hpp"
#include "Person.hpp"
#include "Tree.hpp"
#include "commonFunctions.hpp"


int main()
{

    Tree<Person> familyTree;

    // Generate menu with its functions
    Menu mainMenu{"HOVEDMENY",
                  // Show whole family-tree
                  {{"Vis tre", [&familyTree]() {
                        CLI::showTree(familyTree);
                    }},

                   // Show detailed view of desired people
                   {"Vis person(er)", [&familyTree]() {
                        CLI::showPeople(familyTree);
                    }},

                   // Add new peron to fanily-tree
                   {"Legg til person", [&familyTree]() {
                        CLI::addPerson(familyTree);
                    }},


                   // Add new peron to fanily-tree
                   {"Slett person", [&familyTree]() {
                        CLI::removePerson(familyTree);
                    }},

                   {"Rediger person", [&familyTree]() {
                        CLI::editPerson(familyTree);
                    }},

                   /*{"Slett person/gren",

                        {"Velg om du vil slette en enkelt person eller en hel gren",
                            {
                                {"Slett person (Personen vil bli erstattet med en \"dummy\")", []() {

                                 }},
                                {{
                                    "Slett gren (Alle etterefølgende personer vil også bli slettet)",[](){

                                        }
                                }}
                            }
                        }
                    },*/

                   {"Last tre fra fil", [&familyTree]() {
                        CLI::loadTree(familyTree);
                    }},

                   {"Lagre tre til fil", [&familyTree]() {
                        CLI::saveTree(familyTree);
                    }}}};


    // Overskrift
    std::cout << "\n--------------------------------" << std::endl;
    std::cout << "|   Hello there family tree!   |" << std::endl;
    std::cout << "--------------------------------\n"
              << std::endl;
    std::cout << "\nI dag er det " << today().toString() << "," << std::endl;
    std::cout << "gjør det til en flott en!" << std::endl;

    mainMenu.run();

    return EXIT_SUCCESS;
}
