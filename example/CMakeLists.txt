
link_libraries(FamilyTree_LIB)

add_executable(FamilyTree_Example
        exampleMain.cpp)

target_include_directories(FamilyTree_Example
        #      PUBLIC "${CMAKE_SOURCE_DIR}/include"
        PUBLIC "${CMAKE_SOURCE_DIR}/test_files")


target_link_libraries(FamilyTree_Example FamilyTree_LIB)
