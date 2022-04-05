add_executable(Forfedrediagram
        main.cpp
        Menu.cpp
        Person.cpp)

target_include_directories(Forfedrediagram
        PUBLIC "${CMAKE_SOURCE_DIR}/include")

# ${CMAKE_SOURCE_DIR} er en variabel for roten til prosjektet