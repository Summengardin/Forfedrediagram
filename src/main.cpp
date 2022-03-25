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
    Tree<Person> tree;
    NewTree betterTree;
    NewTree anotherTree;

    anotherTree.fillFromJson(treeData);
    //anotherTree.listNodes();

    MM::debug("Next Tree");

    Node Martin(treeData["nodes"][0]);
    Node Astrid = Node(treeData["nodes"][1]);

    std::cout << Martin.getData() << std::endl;
    Martin.getData().setFirstName("Martin");
    Martin.getData().setLastName("Simengard");
    Martin.setIdx(treeData["nodes"][0]["treeIdx"]);

    std::unique_ptr<Node> MartinPtr = std::make_unique<Node>(Martin);
    betterTree.setRoot(MartinPtr);
    betterTree.getDataAt(1).setFirstName("MartinSen");

    Martin.addParent(&Astrid);

    {
        Node PK(treeData["nodes"][2]);
        Martin.addParent(&PK);

    }

    {
        Node Sigurd(treeData["nodes"][3]);
        Astrid.addParent(&Sigurd);
    }

    Node ElseMarie = Node(treeData["nodes"][4]);
    Astrid.addParent(&ElseMarie);


    std::cout << Martin << std::endl;
    std::cout << betterTree.getNode(1) << std::endl;
    std::cout << *Martin.getParents().first << ", " << *Martin.getParents().second<< std::endl;
    std::cout << Astrid << std::endl;

    std::cout << Martin.getLeft() << std::endl;
    std::cout << betterTree.getRoot().getRight() << std::endl;

    std::cout << "\n";
    betterTree.listNodes();
    betterTree.show();



    return EXIT_SUCCESS;
}

