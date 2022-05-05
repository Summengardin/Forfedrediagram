
include_directories(PUBLIC "${CMAKE_SOURCE_DIR}/include")

link_libraries(FamilyTree_LIB)

add_executable(TestTree test_tree.cpp)
add_test(NAME TestTree COMMAND TestTree)

add_executable(TestPerson test_person.cpp)
add_test(NAME TestPerson COMMAND TestPerson)
target_include_directories(TestPerson
        PUBLIC "${CMAKE_SOURCE_DIR}/examples/include")

add_executable(TestUsefulFunctions test_helpers.cpp)
add_test(NAME TestUsefulFunctions COMMAND TestUsefulFunctions)
