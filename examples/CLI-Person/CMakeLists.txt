
add_executable(CLIPersonExample
        CLIExample.cpp
        menu.cpp
        person.cpp)


target_include_directories(CLIPersonExample
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
        )

#target_link_libraries(CLIPersonExample INTERFACE FamilyTree_LIB)

