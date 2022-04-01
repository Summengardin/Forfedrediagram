cmake_minimum_required(VERSION 3.21)
project(forfedrediagram)

set(CMAKE_CXX_STANDARD 17)

add_executable(forfedrediagram
        src/main.cpp
        src/Person.hpp
        src/Node.hpp
        src/Tree.hpp
        src/globals.hpp)


add_executable(TestTree
        test/test_tree.cpp
        #test/test_usefulFunctions.cpp
        )

add_executable(TestPerson
        test/test_person.cpp
        #test/test_usefulFunctions.cpp
        )

add_executable(TestUsefulFunctions
        test/test_usefulFunctions.cpp
        )