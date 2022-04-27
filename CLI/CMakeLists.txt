

#link_libraries(FamilyTree_LIB)


add_executable(FamilyTree_CLI
        CLI_main.cpp)


target_include_directories(FamilyTree_CLI
        PUBLIC "${CMAKE_SOURCE_DIR}/include"
        PUBLIC "${CMAKE_SOURCE_DIR}/test_files"
        )

target_link_libraries(FamilyTree_CLI PUBLIC FamilyTree_LIB)








#target_link_libraries(Forfedrediagram_CLI include src)