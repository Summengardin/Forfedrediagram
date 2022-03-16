//
// Created by Martin on 3/3/2022.
//

#include <iostream>
#include <memory>
#include <vector>

#include "Node.hpp"
#include "Person.hpp"

int main(){
    std::cout << "Hello their family tree!" << std::endl;

    Person Martin = Person("Martin", "Simengard");

    std::cout << Martin << std::endl;



    return EXIT_SUCCESS;
}

