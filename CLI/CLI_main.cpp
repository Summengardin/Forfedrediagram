#include <iostream>
#include <memory>


#include "Menu.hpp"
#include "Node.hpp"
#include "Person.hpp"
#include "Tree.hpp"
#include "commonFunctions.hpp"
#include "CLI_functions.h"


int main() {

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

                   {"Rediger person", [&familyTree]() {
                       CLI::editPerson(familyTree);
                    }},

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

    mainMenu.show();

    return EXIT_SUCCESS;
}

