#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <ctime>
#include <chrono>


#include "Node.hpp"
#include "Person.hpp"
#include "Tree.hpp"
#include "../include/date.hpp"
#include "../include/commonFunctions.hpp"

int main(){
    std::cout << "Today it is " << today().to_string() << std::endl;

    // Overskrift
    std::cout << "\n--------------------------------" << std::endl;
    std::cout <<   "|   Hello there family tree!   |" << std::endl;
    std::cout <<   "--------------------------------\n" << std::endl;


    // Henter filer å lese fra og skrive til
    std::string fromFile{"../test/test_files/FirstTree.json"};
    std::ifstream jsonFile(fromFile);


 //   std::string MartinFile{"../test/MartinPerson.json"};

    // Henter ut filen som et JSON-objekt
    json treeData;
    jsonFile >> treeData;

    // Generere tre
//    Tree<Person> tree;
    Tree anotherTree;

    anotherTree.fillFromJson(treeData);
    //anotherTree.listNodes();


    std::cout << "\n";
    COM::debug("List nodes");
    anotherTree.listNodes();
    COM::debug("Tree show");
    anotherTree.show();


    COM::debug("Find by index");
    int indexToFind = 6;
    std::cout << "Finding index: " << indexToFind << "\n";
    std::cout << anotherTree.findNodeByIdx(indexToFind) << std::endl;


    // Genereate new person:
    Person newPerson = Person::generate();
    newPerson.viewDetails();
    std::shared_ptr<Node> newNode = std::make_shared<Node>(newPerson);
    anotherTree.findNodeByIdx(indexToFind).addParent(newNode);

    COM::debug("Find by name");
    std::string nameToFind = "Simengard";
    std::cout << "Finding index: " << nameToFind << "\n";
    for (const auto& node : anotherTree.findNodeByString(nameToFind)){
        std::cout << *node << ". ";
        std::cout << "Age is :" << node->getData().getAge() << std::endl;
    }


    COM::debug("Traverser BFS:");
    anotherTree.traverserBFS();



    COM::debug("Write to file");
    std::string outputFile{"../test/test_files/Tree.json"};
    std::ofstream saveToFile(outputFile);
    saveToFile << anotherTree.toJson().dump(4);

    return EXIT_SUCCESS;
}

