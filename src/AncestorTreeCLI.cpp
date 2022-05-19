#include <iostream>

#include "atree/AncestorTree.hpp"
#include "AncestorTreeCLI.hpp"
#include "menu/Menu.hpp"
#include "person/Person.hpp"

int main()
{
    ATree::Tree<Person> familyTree;

    // Generate mainMenu
    Menu mainMenu{"MAIN MENU",
                  {{"Show full tree", [&familyTree]() { showTree(familyTree); }},

                   {"Detailed view", [&familyTree]() { showPeople(familyTree); }},

                   {"Add person", [&familyTree]() { addPerson(familyTree); }},

                   {"Remove person", [&familyTree]() { removePerson(familyTree); }},

                   {"Edit person", [&familyTree]() { editPerson(familyTree); }},

                   {"Load tree from .json-file", [&familyTree]() { loadTreeFromJson(familyTree); }},

                   {"Save tree to .json-file", [&familyTree]() { saveTreeToJson(familyTree); }}}};

    // Main title
    std::cout << "\n--------------------------------" << std::endl;
    std::cout << "|   Hello there family tree!   |" << std::endl;
    std::cout << "--------------------------------\n" << std::endl;
    std::cout << "\nToday is " << Date::today().toString() << "," << std::endl;

    mainMenu.show();

    return EXIT_SUCCESS;
}
