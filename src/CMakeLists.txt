add_library(FamilyTree_LIB
        main.cpp
        Menu.cpp
        Person.cpp)

target_include_directories(FamilyTree_LIB
        PUBLIC "${CMAKE_SOURCE_DIR}/include")


# ${CMAKE_SOURCE_DIR} er en variabel for roten til prosjektet