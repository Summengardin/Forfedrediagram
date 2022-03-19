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
    std::cout << "Hello their family tree!" << std::endl;

 //   Person Martin = Person("Martin", "Simengard");

   // std::cout << Martin << std::endl;
    std::string fromFile{"../test/FirstTree.json"};
    std::string toFile{"../test/NewTree.json"};
    std::string MartinFile{"../test/MartinPerson.json"};

    Tree tree;
    tree.fromJson(fromFile);
    tree.toJson(toFile);

    Person Martin(tree.getAllData()["nodes"][0]);
    std::cout << Martin << std::endl;

    std::ofstream MartinStream(MartinFile);
    MartinStream << Martin.toJson();

    json chacalaca = tree.getAllData() ;
    for(auto& peep : chacalaca["nodes"]){
        std::cout << "ID: " << peep["treeID"] << ", is " << peep["firstName"].get<std::string>() << " " << peep["lastName"].get<std::string>() << std::endl;
    }


    return EXIT_SUCCESS;
}

