#include <iostream>
#include <memory>

#include "CLI_functions.h"
#include "menu.hpp"
#include "node.hpp"
#include "person.hpp"
#include "tree.hpp"
#include "CLIhelpers.hpp"

int main()
{
    Tree<Person> familyTree;

    // Generate menu with its functions
    Menu mainMenu{"HOVEDMENY",
                  {{"Show full tree", [&familyTree]() { CLI::showTree(familyTree); }},

                   {"Detailed view", [&familyTree]() { CLI::showPeople(familyTree); }},

                   {"Add person", [&familyTree]() { CLI::addPerson(familyTree); }},

                   {"Remove person", [&familyTree]() { CLI::removePerson(familyTree); }},

                   {"Edit person", [&familyTree]() { CLI::editPerson(familyTree); }},

                   {"Load tree from .json-file", [&familyTree]() { CLI::loadTree(familyTree); }},

                   {"Save tree to .json-file", [&familyTree]() { CLI::saveTree(familyTree); }}}};

    // Overskrift
    std::cout << "\n--------------------------------" << std::endl;
    std::cout << "|   Hello there family tree!   |" << std::endl;
    std::cout << "--------------------------------\n" << std::endl;
    std::cout << "\nToday is " << today().toString() << "," << std::endl;
    std::cout << "make it the best!" << std::endl;

    mainMenu.show();

    return EXIT_SUCCESS;
}
