

#link_libraries(FamilyTree_LIB)


add_executable(FamilyTree_CLI
        CLI_main.cpp CLI_functions.h)


target_include_directories(FamilyTree_CLI
        PUBLIC "${CMAKE_SOURCE_DIR}/include"
        PUBLIC "${CMAKE_SOURCE_DIR}/test_files"
        PUBLIC "${CMAKE_SOURCE_DIR}/CLI/include"
        )

target_link_libraries(FamilyTree_CLI PUBLIC FamilyTree_LIB)








#target_link_libraries(Forfedrediagram_CLI include src)