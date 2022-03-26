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
#include "newTree.hpp"
#include "../include/UsefulFunctions.hpp"

int main(){

    // Overskrift
    std::cout << "\n--------------------------------" << std::endl;
    std::cout <<   "|   Hello there family tree!   |" << std::endl;
    std::cout <<   "--------------------------------\n" << std::endl;


    // Henter filer å lese fra og skrive til
    std::string fromFile{"../test/FirstTree.json"};
    std::ifstream jsonFile(fromFile);

 //   std::string toFile{"../test/NewTree.json"};
 //   std::string MartinFile{"../test/MartinPerson.json"};

    // Henter ut filen som et JSON-objekt
    json treeData;
    jsonFile >> treeData;

    // Generere tre
//    Tree<Person> tree;
    NewTree betterTree;
    NewTree anotherTree;

    anotherTree.fillFromJson(treeData);
    //anotherTree.listNodes();

    MM::debug("Next Tree");

    Node Martin(treeData["nodes"][0]);
    Node Astrid = Node(treeData["nodes"][1]);

    std::cout << Martin.viewData() << std::endl;
    Martin.getData().setFirstName("Martin");
    Martin.getData().setLastName("Simengard");
    Martin.setIdx(treeData["nodes"][0]["treeIdx"]);

    std::shared_ptr<Node> MartinPtr = std::make_shared<Node>(Martin);
    betterTree.setRoot(MartinPtr);
    betterTree.getDataAt(1).setFirstName("MartinSen");

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
    std::cout << betterTree.getNode(1) << std::endl;
    std::cout << *Martin.getParents().first << ", " << *Martin.getParents().second<< std::endl;
    std::cout << Astrid << std::endl;

    std::cout << Martin.getLeft() << std::endl;

    MM::debug("Get root");
    std::cout << betterTree.viewRoot() << std::endl;

    std::cout << "\n";
    MM::debug("List nodes");
    anotherTree.listNodes();
    betterTree.listNodes();
    MM::debug("Tree show");
    anotherTree.show();
    betterTree.show();



    return EXIT_SUCCESS;
}

