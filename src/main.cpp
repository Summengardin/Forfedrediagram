//
// Created by Martin on 3/3/2022.
//

#include <iostream>
#include <memory>
#include <vector>
#include <fstream>


#include "Node.hpp"
#include "Person.hpp"
#include "Tree.hpp"

int main(){
    std::cout << "\n|-------------------------------|" << std::endl;
    std::cout <<   "|   Hello there family tree!    |" << std::endl;
    std::cout <<   "|-------------------------------|\n" << std::endl;

    std::string fromFile{"../test/FirstTree.json"};
    std::string toFile{"../test/NewTree.json"};
    std::string MartinFile{"../test/MartinPerson.json"};

    std::ifstream jsonFile(fromFile);


    Tree<Person> tree;
    json treeData;
    jsonFile >> treeData;
    tree.addNode(treeData["nodes"][0]);
    tree.at(2).

    std::cout << tree.at(1) << std::endl;


    return EXIT_SUCCESS;
}

