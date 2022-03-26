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
    Today today;
    std::cout << "Today it is " << today() << std::endl;

    // Overskrift
    std::cout << "\n--------------------------------" << std::endl;
    std::cout <<   "|   Hello there family tree!   |" << std::endl;
    std::cout <<   "--------------------------------\n" << std::endl;


    // Henter filer å lese fra og skrive til
    std::string fromFile{"../test/AnonymTestData.json"};
    std::ifstream jsonFile(fromFile);

 //   std::string toFile{"../test/NewTree.json"};
 //   std::string MartinFile{"../test/MartinPerson.json"};

    // Henter ut filen som et JSON-objekt
    json treeData;
    jsonFile >> treeData;

    // Generere tre
//    Tree<Person> tree;
    NewTree anotherTree;

    anotherTree.fillFromJson(treeData);
    //anotherTree.listNodes();

    COM::debug("Next Tree");

    Node Martin(treeData["nodes"][0]);
    Node Astrid = Node(treeData["nodes"][1]);

    std::cout << Martin.viewData() << std::endl;
    Martin.getData().setFirstName("Martin");
    Martin.getData().setLastName("Simengard");
    Martin.setIdx(treeData["nodes"][0]["treeIdx"]);

    std::shared_ptr<Node> MartinPtr = std::make_shared<Node>(Martin);

    Martin.addParent(std::make_shared<Node>(Astrid));

    {
        Node PK(treeData["nodes"][2]);
        Martin.addParent(std::make_shared<Node>(PK));

    }

    {
        Node Sigurd(treeData["nodes"][3]);
        Astrid.addParent(std::make_shared<Node>(Sigurd));
    }

    Node ElseMarie = Node(treeData["nodes"][4]);
    Astrid.addParent(std::make_shared<Node>(ElseMarie));


    std::cout << Martin << std::endl;
    std::cout << *Martin.getParents().first << ", " << *Martin.getParents().second<< std::endl;
    std::cout << Astrid << std::endl;

    std::cout << Martin.getLeft() << std::endl;

    COM::debug("Get root");

    std::cout << "\n";
    COM::debug("List nodes");
    anotherTree.listNodes();
    COM::debug("Tree show");
    anotherTree.show();


    COM::debug("Find by index");
    int indexToFind = 6;
    std::cout << "Finding index: " << indexToFind << "\n";
    std::cout << anotherTree.findNodeByIdx(indexToFind) << std::endl;

    COM::debug("Find by name");
    std::string nameToFind = "Tollersrud";
    std::cout << "Finding index: " << nameToFind << "\n";
    for (const auto& node : anotherTree.findNodeByString(nameToFind))

        std::cout << *node << std::endl;

    return EXIT_SUCCESS;
}

