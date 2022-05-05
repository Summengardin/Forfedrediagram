#include <iostream>

#include "atree/ancestor_tree.hpp"
#include "familytree_CLI.hpp"
#include "menu/menu.hpp"
#include "person/person.hpp"

int main()
{
    ATree::Tree<Person> familyTree;

    // Generate menu with its functions
    Menu mainMenu{"HOVEDMENY",
                  {{"Show full tree", [&familyTree]() { showTree(familyTree); }},

                   {"Detailed view", [&familyTree]() { showPeople(familyTree); }},

                   {"Add person", [&familyTree]() { addPerson(familyTree); }},

                   {"Remove person", [&familyTree]() { removePerson(familyTree); }},

                   {"Edit person", [&familyTree]() { editPerson(familyTree); }},

                   {"Load tree from .json-file", [&familyTree]() { loadTreeFromJson(familyTree); }},

                   {"Save tree to .json-file", [&familyTree]() { saveTreeToJson(familyTree); }}}};

    // Overskrift
    std::cout << "\n--------------------------------" << std::endl;
    std::cout << "|   Hello there family tree!   |" << std::endl;
    std::cout << "--------------------------------\n" << std::endl;
    std::cout << "\nToday is " << Date::today().toString() << "," << std::endl;
    std::cout << "make it the best!" << std::endl;

    mainMenu.show();

    return EXIT_SUCCESS;
}
