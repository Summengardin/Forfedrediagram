add_library(FamilyTree_LIB
        FamilyTree.cpp
        Menu.cpp
        Person.cpp)

target_include_directories(FamilyTree_LIB
        PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
        PUBLIC
        "${CMAKE_SOURCE_DIR}/include")


# ${CMAKE_SOURCE_DIR} er en variabel for roten til prosjektet