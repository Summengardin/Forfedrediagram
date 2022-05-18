include_directories(PUBLIC "${CMAKE_SOURCE_DIR}/include")

add_executable(TestTree test_tree.cpp)
add_test(NAME TestTree COMMAND TestTree)

add_executable(TestPerson test_person.cpp)
add_test(NAME TestPerson COMMAND TestPerson)

add_executable(TestDate test_date.cpp)
add_test(NAME TestDate COMMAND TestDate)

add_executable(TestHelpers test_helpers.cpp)
add_test(NAME TestHelpers COMMAND TestHelpers)

