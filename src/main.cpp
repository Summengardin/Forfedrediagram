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


    std::ifstream i("../test/FirstTree.json");
    json j;
    i >> j;

    std::cout << j << std::endl;

    std::ofstream o("../test/FirstTree.json");
    o << std::setw(4) << j << std::endl;

    return EXIT_SUCCESS;
}

