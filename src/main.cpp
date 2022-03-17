//
// Created by Martin on 3/3/2022.
//

#include <iostream>
#include <memory>
#include <vector>
#include <ctime>

#include "Node.hpp"
#include "Person.hpp"

int main(){
    std::cout << "Hello their family tree!" << std::endl;

 //   Person Martin = Person("Martin", "Simengard");

   // std::cout << Martin << std::endl;


    // current date/time based on current system
    time_t now = time(0);

    // convert now to string form
    char* dt = ctime(&now);

    std::cout << "The local date and time is: " << dt << std::endl;

    // convert now to tm struct for UTC
    tm *gmtm = gmtime(&now);
    dt = asctime(gmtm);
    std::cout << "The UTC date and time is:"<< dt << std::endl;

    return EXIT_SUCCESS;
}

