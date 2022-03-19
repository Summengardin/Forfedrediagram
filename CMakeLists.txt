cmake_minimum_required(VERSION 3.21)
project(forfedrediagram)

set(CMAKE_CXX_STANDARD 17)

add_executable(forfedrediagram
        src/main.cpp
        src/Person.hpp
        src/Node.hpp src/Tree.hpp)

add_executable(test
        test/test_main.cpp
        test/test_person.cpp test/test_tree.cpp)
